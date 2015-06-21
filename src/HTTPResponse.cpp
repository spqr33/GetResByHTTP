/* 
 * File:   HTTPResponse.cpp
 * Author: s
 * 
 * Created on June 19, 2015, 4:26 PM
 */

#include "HTTPResponse.h"

LobKo::HTTPResponse::HTTPResponse(shared_ptr<HTTPRequest>& sp) :
wpHTTPRequest_(sp) {

}

//HTTPResponse::HTTPResponse(const HTTPResponse& orig) {
//}

LobKo::HTTPResponse::~HTTPResponse() {
    ;
}

const shared_ptr<LobKo::JumboBuff> LobKo::HTTPResponse::getJumboBuff() const {
    return spJumboBuff_;
}

void LobKo::HTTPResponse::setJumboBuff(shared_ptr<LobKo::JumboBuff> newBuff) {
    spJumboBuff_ = newBuff;
}
