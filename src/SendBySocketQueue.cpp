/* 
 * File:   SendBySocketQueue.cpp
 * Author: s
 * 
 * Created on June 18, 2015, 3:21 PM
 */

#include "SendBySocketQueue.h"
#include <cassert>

LobKo::SendBySocketQueue::SendBySocketQueue(QueuesMaster* qMaster) :
qMaster_(*qMaster) {
    assert(qMaster && "SendBySocketQueue(): QueuesMaster is zero");

}

//SendBySocketQueue::SendBySocketQueue(const SendBySocketQueue& orig) {
//}

LobKo::SendBySocketQueue::~SendBySocketQueue() {
}

void LobKo::SendBySocketQueue::add(int socketFD, shared_ptr<HTTPRequest>) {
#ifdef SENDBYSOCKETQUEUE_H_DEBUG
    std::cout << "In add() function of LobKo::SendBySocketQueue:" << std::endl;
#endif


};