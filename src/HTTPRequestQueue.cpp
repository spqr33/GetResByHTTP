/* 
 * File:   HTTPRequestQueue.cpp
 * Author: s
 * 
 * Created on June 17, 2015, 8:09 PM
 */

#include "HTTPRequestQueue.h"
#include <utility>
#include "utils.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <strings.h> // bzero

LobKo::HTTPRequestQueue::HTTPRequestQueue(QueuesMaster* qmaster) :
qMaster_(*qmaster) {
    assert(qmaster && "HTTPRequestQueue(): QueuesMaster is zero");
}

//HTTPRequestQueue::HTTPRequestQueue(const HTTPRequestQueue& orig) {
//}

LobKo::HTTPRequestQueue::~HTTPRequestQueue() {
}

void LobKo::HTTPRequestQueue::add(shared_ptr<HTTPRequest> sp) {
    queue_.push(sp);
}

void LobKo::HTTPRequestQueue::process(int requestsNumber) {
#ifdef HTTPREQUESTQUEUE_H_DEBUG
    std::cout << "HTTPRequestQueue size:" << queue_.size() << std::endl;
#endif

    shared_ptr<HTTPRequest> spHTTPRequest = queue_.front();
    const std::string& hostname = spHTTPRequest->getURL()->getHost();

    DomainNameResolver resolver;
    std::pair<DNSResult, shared_ptr<IPAdress> > pair;
    pair = resolver(hostname);

    if ( pair.first == DNSResult::DNS_RESOLVE_ERROR ) {
        //std::cout << "DNS Error occured" << std::endl;
        spHTTPRequest->setLastUsedIp(0);
        this->qMaster_.reqErrorsQ()->add(spHTTPRequest);
        this->queue_.pop();
    } else {
        in_addr_t ip = (pair.second).get()->getIP();

        if ( ip == 0 ) {
            spHTTPRequest->setLastUsedIp(0);
            qMaster_.reqErrorsQ()->add(spHTTPRequest);
            queue_.pop();
        } else { // a successfull resolv
            uint16_t port = spHTTPRequest->getURL()->getPort();
            ipport_socket_map_.find(ip, port);
            IPPortToSocketMap::mapIter iter;

            iter = ipport_socket_map_.findIter(ip, port);
            if ( iter != ipport_socket_map_.end() ) { // We used [ip,port] early
                int socketfd = (*iter).second;

                if ( qMaster_.openSocketSet().get()->find(socketfd) == false ) {
                    // there is not socketfd in OpenedSocketHolder
                    // it is necessary to delete pair(ip,port) from IPPortToSocketMap
                    // and to initiate creation of a socket
                    ipport_socket_map_.erase(iter);

                    int socketFD;
                    if ( (socketFD = getConnectedSocket(ip, port)) < 0 ) { //Error while connecting
                        this->qMaster_.reqErrorsQ()->add(spHTTPRequest);
                        this->queue_.pop();
                    } else {
#ifdef HTTPREQUESTQUEUE_H_DEBUG
                        std::cout << "Socket was REcreated successfully." << std::endl;
#endif
                        ipport_socket_map_.add(ip, port, socketFD);
                        qMaster_.openSocketSet().get()->add(socketFD);

                        qMaster_.sendQ()->add(socketFD, spHTTPRequest);
                    }
                } else { // We used [ip,port] early and socket exists in OpenedSocketHolder
                    // we can use opened socket to send again
                    //pass socket and spHTTPRequest to SendQueue
                    qMaster_.sendQ()->add(socketfd, spHTTPRequest);
                }
            } else { // we didn't use [ip,port] before now
                // to initiate creation of a socket
                int socketFD;

                if ( (socketFD = getConnectedSocket(ip, port)) < 0 ) { //Error while connecting
                    this->qMaster_.reqErrorsQ()->add(spHTTPRequest);
                    this->queue_.pop();
                } else {
#ifdef HTTPREQUESTQUEUE_H_DEBUG
                    std::cout << "Socket was created successfully" << std::endl;
#endif
                    ipport_socket_map_.add(ip, port, socketFD);
                    qMaster_.openSocketSet()->add(socketFD);

                    qMaster_.sendQ()->add(socketFD, spHTTPRequest);

                }
            }
        }



        //uint16_t port = spHTTPRequest->spURL_->
    }
}

int LobKo::HTTPRequestQueue::getConnectedSocket(in_addr_t remoteIP, uint16_t remotePort) const {
    int socketfd;

    if ( (socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        return -1;
    }

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof (serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = remotePort;
    serverAddr.sin_addr.s_addr = remoteIP;

#ifdef HTTPREQUESTQUEUE_H_DEBUG
    std::cout << "getConnectedSocket() connect to: " << remoteIP << std::endl;
#endif
    if ( connect(socketfd, (struct sockaddr*) &serverAddr, sizeof (serverAddr)) < 0 ) {
        close(socketfd);
        return -1;
    }
#ifdef HTTPREQUESTQUEUE_H_DEBUG
    std::cout << "getConnectedSocket() is connected to: " << remoteIP << std::endl;
#endif
    return socketfd;
}

//std::cout << "!!!!" << hex << *(pair.second).get() << std::endl << dec;


//queue_.pop();
////!!!!!!!!!!!!!!!!!!!!
//};