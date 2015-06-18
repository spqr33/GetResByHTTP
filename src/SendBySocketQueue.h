/* 
 * File:   SendBySocketQueue.h
 * Author: s
 *
 * Created on June 18, 2015, 3:21 PM
 */

#ifndef SENDBYSOCKETQUEUE_H
#define	SENDBYSOCKETQUEUE_H
#define SENDBYSOCKETQUEUE_H_DEBUG


#include <memory>
#include "HTTPRequest.h"
#include "QueuesMaster.h"

namespace LobKo {
    class QueuesMaster;

    class SendBySocketQueue {
    public:
        SendBySocketQueue(QueuesMaster*);
        ~SendBySocketQueue();

        void add(int socketFD, shared_ptr<HTTPRequest>);
    private:
        SendBySocketQueue(const SendBySocketQueue& orig);
        QueuesMaster& qMaster_;

    };

}
#endif	/* SENDBYSOCKETQUEUE_H */

