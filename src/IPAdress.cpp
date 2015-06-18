/* 
 * File:   IPAdress.cpp
 * Author: s
 * 
 * Created on June 12, 2015, 10:45 PM
 */

#include "IPAdress.h"
#include <typeinfo>

LobKo::IPAdress::IPAdress() {
}

LobKo::IPAdress::IPAdress(const IPAdress& orig) {
}

LobKo::IPAdress::~IPAdress() {
}

void LobKo::IPAdress::add(struct in_addr* p) {
    lAddr_.push_front(*p);
}

void LobKo::IPAdress::addMultiple(struct in_addr** pp) {
    for (; *pp != NULL; ++pp ) {
        lAddr_.push_front(**pp);
    }
}

in_addr_t LobKo::IPAdress::getIP() const {
    if ( lAddr_.empty() ) {
        return 0;
    } else {
         return (*lAddr_.begin()).s_addr;
    }
}

std::ostream& LobKo::operator<<(std::ostream& out, IPAdress& ipAdress) {
    std::list<struct in_addr>::iterator Iter = ipAdress.lAddr_.begin();
    std::list<struct in_addr>::iterator IterEND = ipAdress.lAddr_.end();

    out << "___________________We are here" << std::endl;
    out << "Recors count: " << ipAdress.lAddr_.size() << std::endl;
    for (; Iter != ipAdress.lAddr_.end(); ) {
        in_addr_t i = (*Iter).s_addr;
        out << i << std::endl;
        ++Iter;
    }
    //out << "___________________We are here!" << std::endl;

    return out;
};