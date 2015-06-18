/* 
 * File:   HTTPRequestErrorsQueue.h
 * Author: s
 *
 * Created on June 17, 2015, 8:26 PM
 */

#ifndef HTTPREQUESTERRORSQUEUE_H
#define	HTTPREQUESTERRORSQUEUE_H
#include <queue>
#include <memory>
#include "HTTPRequest.h"
#include <list>

namespace LobKo {

    class HTTPRequestErrorsQueue {
    public:

        enum {
            HOLDER_MAX_SIZE = 1000
        };
        HTTPRequestErrorsQueue(int holderSize = HOLDER_MAX_SIZE);
        virtual ~HTTPRequestErrorsQueue();

        void add(shared_ptr<HTTPRequest> sp);
        std::queue<shared_ptr<HTTPRequest> >& getQueue();

        uint32_t size() const {
            return queue_.size();
        }
    private:
        HTTPRequestErrorsQueue(const HTTPRequestErrorsQueue& orig);

        std::queue<shared_ptr<HTTPRequest> > queue_;
        const int maxSize_;
    };
}
#endif	/* HTTPREQUESTERRORSQUEUE_H */

