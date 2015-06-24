/* 
 * File:   RecvBysocketQueue.cpp
 * Author: s
 * 
 * Created on June 19, 2015, 7:56 PM
 */

#include "RecvBysocketQueue.h"
#include "JumboBuff.h"
#include "HTTPResponse.h"
#include <vector>
#include <unistd.h> //close()

//#include <algorithm>

LobKo::RecvBySocketQueue::RecvBySocketQueue(QueuesMaster* qMaster) : qMaster_(*qMaster) {
    assert(qMaster && "SendBySocketQueue(): QueuesMaster is zero");

}
//RecvBysocketQueue::RecvBysocketQueue(const RecvBysocketQueue& orig) {
//}

LobKo::RecvBySocketQueue::~RecvBySocketQueue() {
}

void LobKo::RecvBySocketQueue::add(int socketFD, shared_ptr<HTTPResponse> HTTPResponse) {
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::RecvBySocketQueue" << std::endl;
#endif

    map_[socketFD].push(HTTPResponse);

#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::RecvBySocketQueue End" << std::endl;
#endif
};

void LobKo::RecvBySocketQueue::process() {
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
    std::cout << "RecvBySocketQueue size:" << map_.size() << std::endl;
#endif
    if ( map_.empty() ) {
        return;
    } else {
        //std::cerr << "void LobKo::RecvBySocketQueue::process()" << std::endl;

        using std::vector;
        typedef map<int, queue<shared_ptr<HTTPResponse> > >::iterator MapIterator;
        MapIterator iterMap = map_.begin();
        MapIterator iterMapEnd = map_.end();
        vector<MapIterator> vecEraseItersAtEnd;

        for (; iterMap != iterMapEnd; ++iterMap ) {
            queue<shared_ptr<HTTPResponse> >& q = iterMap->second;

            if ( q.empty() ) {
                vecEraseItersAtEnd.push_back(iterMap);
            } else {
                int socketFD = iterMap->first;
                shared_ptr<HTTPResponse> spHTTPResp = q.front();

                if ( spHTTPResp->getJumboBuff().use_count() == 0 ) {
                    int buffSize = getSystemRCVBUF_Size(socketFD);
                    shared_ptr<JumboBuff> spJumboBuff(new JumboBuff(buffSize));

                    spHTTPResp->setJumboBuff(spJumboBuff);
                }

                int readBytesfromSock;
                const char* const buff = spHTTPResp->getJumboBuff()->watermark_;

                int canBytesRead = spHTTPResp->getJumboBuff()->start_ + spHTTPResp->getJumboBuff()->buffSize_ - buff;
                if ( canBytesRead == 0 ) {
                    //Buffer is full. It is necessary to process it or reinit. **
                };

                readBytesfromSock = this->readFromSocket(socketFD, buff, canBytesRead);

                if ( readBytesfromSock < 0 ) {
                    //Reading error from sock occurs. ***
                } else if ( readBytesfromSock == 0 ) {
                    // Connection was closed by remote side. **** 
                } else { // reading successful
                    spHTTPResp->getJumboBuff()->watermark_ += readBytesfromSock;
                    //chose state
                    if ( spHTTPResp->get_parse_state() == HTTPResponse::parse_states::state_response_line ) {
                        HTTPResponse::parseStatus status;

                        status = spHTTPResp->parseResponseLine();
                        //PARSE_SUCCESS, PARSE_BUFFER_END_REACHED, PARSE_WATERMARK_REACHED,
                        //PARSE_PROTO_ERROR, PARSE_CODE_ERROR, PARSE_REASON_STR_ERROR,
                        //PARSE_NOT_CORRESPOND_STATE, PARSE_HEADER_ERROR, PARSE_ALL_HEADERS_SUCCESS

                        if ( status == HTTPResponse::PARSE_SUCCESS ) {
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
                            std::cout << "Proto:" << spHTTPResp->get_proto() << ":"
                                    << "Status Code:" << spHTTPResp->get_status_code() << ":"
                                    << "Reason Phrase:" << spHTTPResp->get_reason_phrase() << ":"
                                    << std::endl;
#endif
                        } else if ( status == HTTPResponse::PARSE_WATERMARK_REACHED ) {
                            continue;
                        } else if ( status == HTTPResponse::PARSE_BUFFER_END_REACHED ) {
                            spHTTPResp->getJumboBuff()->reInit();
                            continue;
                        }
                        if ( status == HTTPResponse::PARSE_PROTO_ERROR ||
                                status == HTTPResponse::PARSE_CODE_ERROR ||
                                status == HTTPResponse::PARSE_REASON_STR_ERROR ||
                                status == HTTPResponse::PARSE_NOT_CORRESPOND_STATE ) {
                            // error while parsing occured  *
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
                            std::cout << "Error while parsing occured" << std::endl;
#endif                          
                        }
                    } // end if ( spHTTPResp->get_parse_state() == HTTPResponse::parse_states::state_response_line ) {
                    if ( spHTTPResp->get_parse_state() == HTTPResponse::state_response_line_finished ||
                            spHTTPResp->get_parse_state() == HTTPResponse::state_headers ) {

                        HTTPResponse::parseStatus status;
                        bool parseHeadersExit_Flag = true;

                        while (parseHeadersExit_Flag) {
                            status = spHTTPResp->parseHeaderLine();

                            if ( status == HTTPResponse::PARSE_ALL_HEADERS_SUCCESS ) {
                                break;
                            } else if ( status == HTTPResponse::PARSE_SUCCESS ) {
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
                                std::cout << "" << spHTTPResp->get_curr_name() << ":"
                                        << "" << spHTTPResp->get_curr_value() << "" << std::endl;
#endif
                            } else if ( status == HTTPResponse::PARSE_WATERMARK_REACHED ) {
                                parseHeadersExit_Flag = false;
                            } else if ( status == HTTPResponse::PARSE_BUFFER_END_REACHED ) {
                                spHTTPResp->getJumboBuff()->reInit();
                                parseHeadersExit_Flag = false;
                            } else if ( status == HTTPResponse::PARSE_HEADER_ERROR ) {
                                // error while parsing occured  *
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
                                // error while parsing occured  *
                                std::cout << "Error while header parsing occured" << std::endl;
#endif     
                            }
                        }
                        /////////////////!!!
                        if ( parseHeadersExit_Flag == false ) {
                            continue;
                            //main for (; iterMap != iterMapEnd; ++iterMap )
                        }
                        /////////////////!!!


                    }
                    if ( spHTTPResp->get_parse_state() == HTTPResponse::state_headers_finished ) {
#ifdef RECVBYSOCKETQUEUE_H_DEBUG
                        // error while parsing occured  *
                        std::cout << "Headers parsing finished" << std::endl;
#endif                         
                    }
                } // end else { // reading successful




                //if Response fully processed
                q.pop();
                if ( q.empty() ) {
                    vecEraseItersAtEnd.push_back(iterMap);
                }
            } // end else. Current q is not empty
        }; // end  for (; iterMap != iterMapEnd; ++iterMap )

        for ( vector<MapIterator>::iterator i = vecEraseItersAtEnd.begin(); i != vecEraseItersAtEnd.end(); ++i ) {

            close((*i)->first);
            map_.erase(*i);
        };
        //std::for_each(vecEraseItersAtEnd.begin(), vecEraseItersAtEnd.end()), map_.erase());
    }
}
//}

int LobKo::RecvBySocketQueue::readFromSocket(int socketFD, const char* buff, int buffSize) {
    assert((buff != NULL) && " SendBySocketQueue::write, Zero pointer\n ");
    ssize_t readBytes = 0;

    std::cerr << "Read before" << std::endl;
    readBytes = read(socketFD, const_cast<char*> (buff), buffSize);
    std::cerr << "Read after" << std::endl;

    return readBytes;
}