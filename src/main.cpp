/* 
 * File:   main.cpp
 * Author: s
 *
 * Created on June 12, 2015, 3:56 PM
 */

#include <cstdlib>
#include "utils.h"
#include "IPAdress.h"
#include <string>
#include <utility> //pair
#include <memory>
#include <iostream>
#include <bits/shared_ptr_base.h>

using namespace std;
using namespace LobKo;

using std::string;

/*
 * 
 */
int main(int argc, char** argv) {
    DomainNameResolver resolver;
    string hostname("cnn.com");
    //string hostname("s-R40-R41");
    std::pair<DNSResult, shared_ptr<IPAdress> > pair;
    pair = resolver(hostname);

    if ( pair.first == LobKo::DNSResult::DNS_RESOLVE_ERROR ) {
        std::cout << "DNS Error occured" << std::endl;

        return EXIT_FAILURE;
    }
    std::cout << "!!!!" << hex<< *(pair.second).get() << std::endl;
    
    
    std::cout << "main exit" << endl;
    return 0;
}

