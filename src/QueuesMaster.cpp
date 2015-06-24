/* 
 * File:   QueuesMaster.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 9:57 PM
 */

#include "QueuesMaster.h"
#include <stdexcept>

LobKo::QueuesMaster::QueuesMaster(shared_ptr<HTTPRequest> initialisationHTTPRequest) :
reqQueue_(new HTTPRequestQueue(this)),
errQueue_(new HTTPRequestErrorsQueue),
openSockSet_(new OpenedSocketHolder),
sendQueue_(new SendBySocketQueue(this)),
recvQueue_(new RecvBySocketQueue(this)),
initialisationHTTPRequest_(initialisationHTTPRequest) {
    reqQueue_->add(initialisationHTTPRequest_);

    ;
}

LobKo::QueuesMaster::QueuesMaster(shared_ptr<TaskHolder> spTaskHolder) : reqQueue_(new HTTPRequestQueue(this)),
errQueue_(new HTTPRequestErrorsQueue),
openSockSet_(new OpenedSocketHolder),
sendQueue_(new SendBySocketQueue(this)),
recvQueue_(new RecvBySocketQueue(this)) {
    loadTasks(spTaskHolder);
}



//QueuesMaster::QueuesMaster(const QueuesMaster& orig) {
//}

LobKo::QueuesMaster::~QueuesMaster() {
    ;
}

void LobKo::QueuesMaster::loadTasks(shared_ptr<TaskHolder> spTaskHolder) {
    vector<Task>::iterator iterVec = spTaskHolder->getTasks().begin();
    vector<Task>::iterator iterVecEnd = spTaskHolder->getTasks().end();

    //shared_ptr<HTTPRequest> spHTTPRequest;

    for (; iterVec != iterVecEnd; ++iterVec ) {
        try {
            shared_ptr<URL> spURL(new URL(iterVec->remoteResource()));
            HTTPRequestType type(LobKo::HTTPRequestType::Type::GET);
            HTTPProto proto(LobKo::HTTPProto::Type::HTTP1_1);

            shared_ptr<HTTPRequest> spHTTPRequest(new HTTPRequest(type, spURL, proto));

            reqQueue_->add(spHTTPRequest);

        } catch (const std::invalid_argument& ia) {
            iterVec->setTaskResult(LobKo::Task::taskResult::TASK_ERROR);
        }
    }
}

void LobKo::QueuesMaster::process() {
    reqQueue_->process();
    sendQueue_->process();
    recvQueue_->process();
    


    //std::queue<shared_ptr<HTTPRequest> > queue_ =  errQueue_->getQueue();

    std::cout << "Error Queue size: " << errQueue_->size() << std::endl;
}