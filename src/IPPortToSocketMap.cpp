/* 
 * File:   IPPortToScoketMap.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 4:37 PM
 */

#include "IPPortToSocketMap.h"
#include <map>

LobKo::IPPortToSocketMap::IPPortToSocketMap() {
}

LobKo::IPPortToSocketMap::~IPPortToSocketMap() {
}

int LobKo::IPPortToSocketMap::add(in_addr_t s_addr, uint16_t port, int socket) {
    std::pair< in_addr_t, uint16_t> p(s_addr, port);
    std::map <std::pair< in_addr_t, uint16_t>, int >::iterator iter;

    iter = map_.find(p);
    if ( iter != map_.end() ) {
        int oldSocket = iter->second;
        iter->second = socket; //Replaced socked. Whether need to call OpenedSocketHolder::erase?

        return oldSocket;
    } else {
        map[p] = socket;
    }
    
    return 0;
}

int LobKo::IPPortToSocketMap::erase(in_addr_t s_addr, uint16_t port) {
    std::pair< in_addr_t, uint16_t> p(s_addr, port);

    return map_.erase(p);
}

unsigned int LobKo::IPPortToSocketMap::size() const {
    return map_.size();
}

bool LobKo::IPPortToSocketMap::empty() const {
    return map_.empty();
}