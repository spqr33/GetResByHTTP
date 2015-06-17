/* 
 * File:   IPPortToScoketMap.h
 * Author: s
 *
 * Created on June 17, 2015, 4:37 PM
 */

#ifndef IPPORTTOSOCKETMAP_H
#define	IPPORTTOSOCKETMAP_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <utility>

namespace LobKo {

    class IPPortToSocketMap {
    public:
        IPPortToSocketMap();
        ~IPPortToSocketMap();
        int add(in_addr_t s_addr, uint16_t port, int socket);
        //int erase(int socket);
        int erase(in_addr_t s_addr, uint16_t port);
        unsigned int size() const;
        bool empty() const;
    private:
        IPPortToSocketMap(const IPPortToSocketMap& orig);

        std::map <std::pair< in_addr_t, uint16_t>, int > map_;
    };
};
#endif	/* IPPORTTOSOCKETMAP_H */

