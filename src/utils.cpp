#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include 

std::pair<LobKo::DNSResult, std::shared_ptr<LobKo::IPAdress> >
LobKo::DomainNameResolver::operator ()(const string& host) {
    struct hostent* pHostEnt;
    using namespace std;

    pHostEnt = gethostbyname(host.c_str());
    if ( pHostEnt == NULL ) {
        IPAdress* pIPAdress = new IPAdress();
        std::shared_ptr<IPAdress> spIPADress(pIPAdress);

        return std::make_pair(DNSResult::DNS_RESOLVE_ERROR, spIPADress);
    } else {
        cout << "OK!" << endl;
        IPAdress* pIPAdress = new IPAdress();
        shared_ptr<IPAdress> spIPADress(pIPAdress);

        struct in_addr** pp_in_addr_list;
        pp_in_addr_list = (struct in_addr**) pHostEnt->h_addr_list;
        struct in_addr* p_in_addr = *pp_in_addr_list;

        cout << "OK!" << std::endl;
        cerr << pp_in_addr_list << endl;
        cerr << pHostEnt->h_name << endl;
        //        if ( *(pHostEnt->h_aliases) == NULL ) {
        //            cerr << "Host haven't any aliases" << endl;
        //        } else {
        //            std::cerr << *(pHostEnt->h_aliases) << std::endl;
        //        }

        //        if ( *(pHostEnt->h_addr_list) == NULL ) {
        //            cerr << "Host haven't any IP entry" << endl;
        //        } else {
        cerr << "*struct in_addr*  p_in_addr == " << hex << p_in_addr << endl;
        cerr << "*(pHostEnt->h_addr_list) == " << hex << *(pHostEnt->h_addr_list) << endl;
        cerr << "*pp_in_addr_list == " << hex << *pp_in_addr_list << endl;

        //std::cerr << "p_in_addr->s_addr == " << p_in_addr->s_addr<< std::endl;
        //std::cerr << "ntohl(p_in_addr->s_addr) == " << ntohl(p_in_addr->s_addr)<< std::endl;
        //std::cerr << "________" <<inet_
        //std::cerr << "inet_ntoa() == " << inet_ntoa(*p_in_addr) << std::endl;
        //std::cerr << "*(pHostEnt->h_addr_list) == " << std::hex<< *(pHostEnt->h_addr_list) << std::endl;
        while (*pp_in_addr_list != NULL) {
            char buff[INET_ADDRSTRLEN + 1];
            const char *c = inet_ntop(AF_INET, *(pp_in_addr_list), buff, INET_ADDRSTRLEN + 1);
            if ( c == NULL ) {
                cerr << "Error occured\n";
            }
            cerr << buff << "::" << dec<< (**pp_in_addr_list).s_addr << endl;
            pp_in_addr_list++;
        }
        //        }
        spIPADress.get()->addMultiple((struct in_addr**) pHostEnt->h_addr_list);
                //        std::cerr << **(pHostEnt->h_addr_list) << std::endl;
                //spIPADress.get()->addMultiple(pp_in_addr_list);

        return std::make_pair(DNSResult::DNS_RESOLVE_SUCCESS, spIPADress);
    }

}
