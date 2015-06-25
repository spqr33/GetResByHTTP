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
#include <queue>
#include <map>

namespace LobKo {
    class QueuesMaster;

    class SendBySocketQueue {
    public:
        SendBySocketQueue(QueuesMaster*);
        ~SendBySocketQueue();

        void add(int socketFD, shared_ptr<HTTPRequest>);
        void process();
        inline int getQueueSize() const;
    private:
        SendBySocketQueue(const SendBySocketQueue& orig);
        QueuesMaster& qMaster_;
        int writeToSocket(int socketFD, const char* begin, size_t n) const;

        //std::queue<int> socketQueue_;
        std::map<int, std::queue<shared_ptr<HTTPRequest> > > map_;

    };

};

int LobKo::SendBySocketQueue::getQueueSize() const {
    return map_.size();
};
#endif	/* SENDBYSOCKETQUEUE_H */

