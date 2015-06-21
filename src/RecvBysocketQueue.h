/* 
 * File:   RecvBysocketQueue.h
 * Author: s
 *
 * Created on June 19, 2015, 7:56 PM
 */

#ifndef RECVBYSOCKETQUEUE_H
#define	RECVBYSOCKETQUEUE_H


#include <memory>
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "QueuesMaster.h"
#include <queue>
#include <map>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>         //getsockopt


namespace LobKo {
    class QueuesMaster;

    class RecvBySocketQueue {
    public:
        explicit RecvBySocketQueue(QueuesMaster*);
        ~RecvBySocketQueue();

        void add(int socketFD, shared_ptr<HTTPResponse>);
        void process();
        inline unsigned int getSystemRCVBUF_Size(int socketFd) const;
    private:
        RecvBySocketQueue(const RecvBySocketQueue& orig);
        int read(int socketFD, const char* buff, int buffSize);
        QueuesMaster& qMaster_;

        std::map<int, std::queue<shared_ptr<HTTPResponse> > > map_;

    };
};

unsigned int LobKo::RecvBySocketQueue::getSystemRCVBUF_Size(int socketFd) const {
    static bool sizeAlreadyCalculated = false;
    static int size = 0;
    static unsigned int defaultSize = 87380;

    if (!sizeAlreadyCalculated) {
        static socklen_t len = sizeof(size);
        if (getsockopt(socketFd, SOL_SOCKET, SO_RCVBUF, &size, &len) < 0) {
            size = defaultSize;
        }
        sizeAlreadyCalculated = true;
    }

    return size;
};

#endif	/* RECVBYSOCKETQUEUE_H */

