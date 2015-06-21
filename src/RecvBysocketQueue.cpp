/* 
 * File:   RecvBysocketQueue.cpp
 * Author: s
 * 
 * Created on June 19, 2015, 7:56 PM
 */

#include "RecvBysocketQueue.h"
#include "JumboBuff.h"

LobKo::RecvBySocketQueue::RecvBySocketQueue(QueuesMaster* qMaster) : qMaster_(*qMaster) {
    assert(qMaster && "SendBySocketQueue(): QueuesMaster is zero");

}
//RecvBysocketQueue::RecvBysocketQueue(const RecvBysocketQueue& orig) {
//}

LobKo::RecvBySocketQueue::~RecvBySocketQueue() {
}

void LobKo::RecvBySocketQueue::add(int socketFD, shared_ptr<HTTPResponse> HTTPResponse) {
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::SendBySocketQueue:" << std::endl;
#endif

    map_[socketFD].push(HTTPResponse);
};

void LobKo::RecvBySocketQueue::process() {
    if ( qMaster_.openSocketSet()->empty() ) {
        return;
    } else {
        std::set<int>::iterator iterSet = qMaster_.openSocketSet()->sockets_.begin();
        std::set<int>::iterator iterEndSet = qMaster_.openSocketSet()->sockets_.end();

        for (; iterSet != iterEndSet; ++iterSet ) {
            int socketFD = *iterSet;
            std::map<int, std::queue<shared_ptr<HTTPResponse> > >::iterator iterMap;

            iterMap = map_.find(socketFD);
            if ( iterMap == map_.end() ) { // socketfd as key didn't find in map_
                //TODO! //delete? from openSocketSet, close socket?
            } else {
                // there is socket in OpenedSocketHolder and as key in map
                std::queue<shared_ptr<HTTPResponse> >& q = iterMap->second;

                if ( !q.empty() ) { // and queue as map value isn't empty.
                    shared_ptr<HTTPResponse> spResponse = q.front();
                    //
                    // ГДЕ ПОП будет????
                    //
                    if ( spResponse->getJumboBuff().use_count() == 0 ) {
                        //there is not sp JumboBuff in HTTPResponse
                        //It is necessary to read data into Buff

                        shared_ptr<JumboBuff> spJumboBuff(new JumboBuff(getSystemRCVBUF_Size(socketFD)));
                        spResponse->setJumboBuff(spJumboBuff);

                        ssize_t readBytes;
                        readBytes = read(socketFD, spJumboBuff->start_, spJumboBuff->buffSize_);
                        //                        if ( readBytes < 0 ) {
                        //                            //TODO check errno and react
                        //
                        //                            continue;
                        //                        }
                        //                        spJumboBuff->watermark_ = readBytes;
                        //
                        //                        if ( !spResponse->parseResponseLine() ) {
                        //                            //Not enough data was read to parse Line
                        //
                        //                            continue;
                        //                        } else { //Response Line already parsed check Proto and STATUS 100!
                        //                            if ( status 100 ) {
                        //                                // move this to parseResponseLine()
                        //
                        //                            }
                        //                            if ( proto != 1.1 ) {
                        //
                        //                            }
                        //                            if ( !spResponse->parseHeaders() )
                        //                                //Not enough data was read to parse Headers
                        //                            } else {
                        //                            //Headers already parsed check Content-Length
                        //                            //retrieve pointer to body
                        //
                        //                            // Продумать сохранение боди неумещающегося в один ДжамбоБуфф
                        //                            // Передачу Джамбобуфера следующему респонсу

                    }
                } else { //HTTP Response has Jumbo Buff
                    // at first - process JumboBuff
                }

            }
        }
    }
}
//}

int LobKo::RecvBySocketQueue::read(int socketFD, const char* buff, int buffSize) {
    assert((buff != NULL) && " SendBySocketQueue::write, Zero pointer\n ");
    ssize_t readBytes = 0;

    readBytes = read(socketFD, buff, buffSize);

    return readBytes;
}