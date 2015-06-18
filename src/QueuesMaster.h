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
#include "HTTPRequest.h"
#include <memory>

namespace LobKo {
    class HTTPRequestQueue;
    class HTTPRequestErrorsQueue;
    class SendBySocketQueue;

    class QueuesMaster {
    public:
        QueuesMaster(shared_ptr<HTTPRequest> initialisationHTTPRequest);
        ~QueuesMaster();

        void process();
        
        inline shared_ptr<HTTPRequestQueue> requestQ();
        inline shared_ptr<HTTPRequestErrorsQueue> reqErrorsQ();
        inline shared_ptr<OpenedSocketHolder> openSocketSet();
        inline shared_ptr<SendBySocketQueue> sendQ();

    private:
        QueuesMaster(const QueuesMaster& orig);

        shared_ptr<HTTPRequestQueue> reqQueue_;
        shared_ptr<HTTPRequestErrorsQueue> errQueue_;
        shared_ptr<OpenedSocketHolder> openSockMap_;
        shared_ptr<SendBySocketQueue> sendQueue_;

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
    return openSockMap_;
}

shared_ptr<LobKo::SendBySocketQueue> LobKo::QueuesMaster::sendQ() {
    return sendQueue_;
}

#endif	/* QUEUESMASTER_H */

