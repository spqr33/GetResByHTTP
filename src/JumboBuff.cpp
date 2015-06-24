/* 
 * File:   JumboBuff.cpp
 * Author: s
 * 
 * Created on June 20, 2015, 1:59 PM
 */

#include "JumboBuff.h"

LobKo::JumboBuff::JumboBuff(unsigned int buffSize) :
buffSize_(buffSize),
start_(new char[buffSize]),
currentPos_(start_),
watermark_(start_) {
}

//JumboBuff::JumboBuff(const JumboBuff& orig) {
//}

LobKo::JumboBuff::~JumboBuff() {
    delete [] start_;
}

void LobKo::JumboBuff::reInit() {
    currentPos_ = start_;
    watermark_ = start_;
}