/* 
 * File:   HTTPRequestErrorsQueue.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 8:26 PM
 */

#include "HTTPRequestErrorsQueue.h"

LobKo::HTTPRequestErrorsQueue::HTTPRequestErrorsQueue(int holderSize) :
maxSize_(holderSize) {
    ;
}

//LobKo::HTTPRequestErrorsQueue::HTTPRequestErrorsQueue(const HTTPRequestErrorsQueue& orig) {
//}

LobKo::HTTPRequestErrorsQueue::~HTTPRequestErrorsQueue() {

}

void LobKo::HTTPRequestErrorsQueue::add(shared_ptr<HTTPRequest> sp) {
    int size = queue_.size();

    if ( size == maxSize_ ) {
        queue_.pop();
    }
    queue_.push(sp);
}