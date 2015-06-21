/* 
 * File:   QueuesMaster.h
 * Author: s
 *
 * Created on June 17, 2015, 9:57 PM
 */

#ifndef QUEUESMASTER_H
#define	QUEUESMASTER_H
#include "HTTPRequestQueue.h"
#include "HTTPRequestErrorsQueue.h"
#include "OpenedSocketHolder.h"
#include "SendBySocketQueue.h"
#include "RecvBysocketQueue.h"
#include "HTTPRequest.h"
#include "TaskHolder.h"
#include "Task.h"
#include <memory>

namespace LobKo {
    class HTTPRequestQueue;
    class HTTPRequestErrorsQueue;
    class SendBySocketQueue;
    class OpenedSocketHolder;
    class RecvBySocketQueue;

    class QueuesMaster {
    public:
        QueuesMaster(shared_ptr<HTTPRequest> initialisationHTTPRequest);
        QueuesMaster(shared_ptr<TaskHolder> spTaskHolder);
        ~QueuesMaster();
        
        void loadTasks(shared_ptr<TaskHolder> sp);

        void process();

        inline shared_ptr<HTTPRequestQueue> requestQ();
        inline shared_ptr<HTTPRequestErrorsQueue> reqErrorsQ();
        inline shared_ptr<OpenedSocketHolder> openSocketSet();
        inline shared_ptr<SendBySocketQueue> sendQ();
        inline shared_ptr<RecvBySocketQueue> recvQ();

    private:
        QueuesMaster(const QueuesMaster& orig);

        shared_ptr<HTTPRequestQueue> reqQueue_;
        shared_ptr<HTTPRequestErrorsQueue> errQueue_;
        shared_ptr<OpenedSocketHolder> openSockSet_;
        shared_ptr<SendBySocketQueue> sendQueue_;
        shared_ptr<RecvBySocketQueue> recvQueue_;

        shared_ptr<HTTPRequest> initialisationHTTPRequest_;
    };

};

shared_ptr<LobKo::HTTPRequestQueue> LobKo::QueuesMaster::requestQ() {
    return reqQueue_;
}

shared_ptr<LobKo::HTTPRequestErrorsQueue> LobKo::QueuesMaster::reqErrorsQ() {
    return errQueue_;
}

shared_ptr<LobKo::OpenedSocketHolder> LobKo::QueuesMaster::openSocketSet() {
    return openSockSet_;
}

shared_ptr<LobKo::SendBySocketQueue> LobKo::QueuesMaster::sendQ() {
    return sendQueue_;
}

shared_ptr<LobKo::RecvBySocketQueue> LobKo::QueuesMaster::recvQ() {
    return recvQueue_;
}

#endif	/* QUEUESMASTER_H */

