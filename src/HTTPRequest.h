/* 
 * File:   HTTPRequest.h
 * Author: s
 *
 * Created on June 16, 2015, 2:27 PM
 */

#ifndef HTTPREQUEST_H
#define	HTTPREQUEST_H

#include <string>
#include <stdexcept>
#include <memory>
#include "URL.h"
#include "headers/HeadersHolder.h"

using std::shared_ptr;

namespace LobKo {

    class HTTPRequestType {
    public:

        enum Type {
            GET
        };
        HTTPRequestType(HTTPRequestType::Type); //throw std::invalid_argument
        ~HTTPRequestType();
        const std::string& getRequestType() const;
    private:
        std::string requestType_;
    };

    class HTTPRequestProto {
    public:

        enum Type {
            HTTP0_9, HTTP1_0, HTTP1_1
        };
        HTTPRequestProto(HTTPRequestProto::Type); //throw std::invalid_argument
        ~HTTPRequestProto();
        const std::string& getRequestProto() const;
        static const std::string& getRequestProtoByType(HTTPRequestProto::Type);
        //bool operator==()
    private:
        std::string protoType_;
    };

    class HTTPRequest {
    public:
        HTTPRequest(const HTTPRequestType& reqType, shared_ptr<URL> spURL, const HTTPRequestProto& reqProto);
        //HTTPRequest(const HTTPRequest& orig);
        ~HTTPRequest();

        void addHeader(shared_ptr<AHeader>);

        const string& getResultString() const;
        const shared_ptr<URL>& getURL() const;

        inline in_addr_t getLastUsedIp() const;
        inline void setLastUsedIp(in_addr_t);

    private:
        HTTPRequestType requestType_;
        HTTPRequestProto requestProto_;
        shared_ptr<URL> spURL_;
        shared_ptr<HeadersHolder> headerHolder_;

        mutable string resultString_;
        mutable bool isResultStringActual_;

        in_addr_t lastUsedIP_NetOrder_;
    };
}

in_addr_t LobKo::HTTPRequest::getLastUsedIp() const {
    return lastUsedIP_NetOrder_;
}
void LobKo::HTTPRequest::setLastUsedIp(in_addr_t ip){
    lastUsedIP_NetOrder_ = ip;
}
#endif	/* HTTPREQUEST_H */

