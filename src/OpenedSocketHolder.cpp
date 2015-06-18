/* 
 * File:   OpenedSocketHolder.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 3:39 PM
 */

#include "OpenedSocketHolder.h"

LobKo::OpenedSocketHolder::OpenedSocketHolder() {
}

//LobKo::OpenedSocketHolder::OpenedSocketHolder(const OpenedSocketHolder& orig) {
//}

LobKo::OpenedSocketHolder::~OpenedSocketHolder() {
}

void LobKo::OpenedSocketHolder::add(int socket) {
    sockets_.insert(socket);
}

int LobKo::OpenedSocketHolder::erase(int socket) {
    return sockets_.erase(socket);
}

unsigned int LobKo::OpenedSocketHolder::size() const {
    return sockets_.size();
}

bool LobKo::OpenedSocketHolder::empty() const {
    return sockets_.empty();
}

bool LobKo::OpenedSocketHolder::find(int socket) const {
    if ( empty() ) {
        return false;
    } else {
        if ( sockets_.find(socket) == sockets_.end() ) {
            return false;
        } else {
            return true;
        }
    }
}


