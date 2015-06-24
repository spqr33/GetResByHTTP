/* 
 * File:   Content_Length.cpp
 * Author: s
 * 
 * Created on June 22, 2015, 9:06 PM
 */

#include "Content_Length.h"

LobKo::Content_Length::Content_Length(const string& name, const string& value) :
AHeader(name, value) {
}

LobKo::Content_Length::~Content_Length() {

}

const string& LobKo::Content_Length::name() {
    static const string name = "Content-Length";

    return name;
}