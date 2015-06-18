/* 
 * File:   QueuesMaster.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 9:57 PM
 */

#include "QueuesMaster.h"

LobKo::QueuesMaster::QueuesMaster(shared_ptr<HTTPRequest> initialisationHTTPRequest) :
reqQueue_(new HTTPRequestQueue(this)),
errQueue_(new HTTPRequestErrorsQueue),
openSockMap_(new OpenedSocketHolder),
sendQueue_(new SendBySocketQueue(this)),
initialisationHTTPRequest_(initialisationHTTPRequest) {
    reqQueue_->add(initialisationHTTPRequest_);

    ;
}

//QueuesMaster::QueuesMaster(const QueuesMaster& orig) {
//}

LobKo::QueuesMaster::~QueuesMaster() {
    ;
}

void LobKo::QueuesMaster::process() {
    reqQueue_->process();


    //std::queue<shared_ptr<HTTPRequest> > queue_ =  errQueue_->getQueue();

    std::cout << "Error Queue size: " << errQueue_->size() << std::endl;
}