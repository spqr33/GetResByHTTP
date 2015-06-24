/* 
 * File:   SendBySocketQueue.cpp
 * Author: s
 * 
 * Created on June 18, 2015, 3:21 PM
 */

#include "SendBySocketQueue.h"
#include "RecvBysocketQueue.h"
#include <cassert>
#include <unistd.h> //write()

LobKo::SendBySocketQueue::SendBySocketQueue(QueuesMaster* qMaster) :
qMaster_(*qMaster) {
    assert(qMaster && "SendBySocketQueue(): QueuesMaster is zero");

}

//SendBySocketQueue::SendBySocketQueue(const SendBySocketQueue& orig) {
//}

LobKo::SendBySocketQueue::~SendBySocketQueue() {
}

void LobKo::SendBySocketQueue::add(int socketFD, shared_ptr<HTTPRequest> spHTTPRequest) {
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::SendBySocketQueue:" << std::endl;
#endif

    map_[socketFD].push(spHTTPRequest);
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::SendBySocketQueue: End" << std::endl;
#endif
};

void LobKo::SendBySocketQueue::process() {
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "SendBySocketQueue size:" << map_.size() << std::endl;
#endif

    if ( qMaster_.openSocketSet()->empty() ) {
        return;
    } else {
        std::set<int>::iterator iterSet = qMaster_.openSocketSet()->sockets_.begin();
        std::set<int>::iterator iterEndSet = qMaster_.openSocketSet()->sockets_.end();

        for (; iterSet != iterEndSet; ++iterSet ) {
            int socketFD = *iterSet;
            std::map<int, std::queue<shared_ptr<HTTPRequest> > >::iterator iterMap;

            iterMap = map_.find(socketFD);
            if ( iterMap == map_.end() ) { // clean up?
                //TODO! //delete from openSocketSet, close socket?
            } else {
                std::queue<shared_ptr<HTTPRequest> >& q = iterMap->second;

                //                while (!q.empty()) { //pipelining
                if ( !q.empty() ) {
                    shared_ptr<HTTPRequest> spRequest = q.front();
                    int writedBytes = 0;
                    int needToWriteBytes = spRequest->getResultString().size() - spRequest->bytesSent();

                    writedBytes = writeToSocket(socketFD, spRequest->getResultString().c_str(), needToWriteBytes);
                    if ( writedBytes < 0 ) {
                        //error occures
                        //cleanup break
                        continue;
                    } else if ( writedBytes < needToWriteBytes ) {
                        spRequest->setBytesSent(spRequest->bytesSent() + writedBytes);
                        //cleanup? - no.
                        continue;
                    } else { //sent all of the data
                        spRequest->setBytesSent(spRequest->getResultString().size());


                        shared_ptr<HTTPResponse> spResponse(new HTTPResponse(spRequest));
                        spRequest->setHTTPResponse(spResponse);

                        qMaster_.recvQ()->add(socketFD, spResponse);
                        q.pop();
                    }


                } else {
                    // it is necessary to remove key(socketFD) from map
                }

            }

        }
    }
    //std::set<int>::iterator;
    //std::queue<shared_ptr<HTTPRequest> >& requestQ;

}

int LobKo::SendBySocketQueue::writeToSocket(int socketFD, const char* begin, size_t n) const {
    //assert((begin != NULL) && " SendBySocketQueue::write, Zero pointer\n ");
    ssize_t writedBytes = 0;


    //std::cout << "!!!" << std::endl;
    writedBytes = write(socketFD, begin, n);
    std::cout << "Wrote" << std::endl;

    return writedBytes;
}