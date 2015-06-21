/* 
 * File:   HTTPResponse.h
 * Author: s
 *
 * Created on June 19, 2015, 4:26 PM
 */

#ifndef HTTPRESPONSE_H
#define	HTTPRESPONSE_H
#include <memory>
#include "HTTPRequest.h"
#include "JumboBuff.h"


using std::weak_ptr;

namespace LobKo {
    class HTTPRequest;
    
class HTTPResponse {
public:
    HTTPResponse(shared_ptr<HTTPRequest>& sp);
    virtual ~HTTPResponse();
    
    const shared_ptr<JumboBuff> getJumboBuff() const;
    void setJumboBuff(shared_ptr<JumboBuff>);
private:
    HTTPResponse(const HTTPResponse& orig);

    weak_ptr<HTTPRequest> wpHTTPRequest_;
    shared_ptr<JumboBuff> spJumboBuff_;
};

}
#endif	/* HTTPRESPONSE_H */

