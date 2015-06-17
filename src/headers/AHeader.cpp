/* 
 * File:   AHeader.cpp
 * Author: s
 * 
 * Created on June 16, 2015, 4:08 PM
 */

#include "AHeader.h"
#include "HostHeader.h"

LobKo::AHeader::AHeader(const string& name, const string& value) :
name_(name),
value_(value) {
}

LobKo::AHeader::~AHeader() {
}

shared_ptr<LobKo::AHeader> LobKo::AHeader::makeHeader(const string& name, const string& value) {
    if ( name == "Host" ) {
        return shared_ptr<AHeader>(new HostHeader(name, value));
    }
}

const string& LobKo::AHeader::getName() const {
    return name_;
}
const string& LobKo::AHeader::getValue() const {
    return value_;
}