/* 
 * File:   main.cpp
 * Author: s
 *
 * Created on June 12, 2015, 3:56 PM
 */

#include <cstdlib>
#include "utils.h"
#include "IPAdress.h"
#include "URL.h"
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
    //string hostname("ukr.net");
    string hostname("cnn.com");
    //string hostname("s-R40-R41");
    std::pair<DNSResult, shared_ptr<IPAdress> > pair;
    pair = resolver(hostname);

    if ( pair.first == LobKo::DNSResult::DNS_RESOLVE_ERROR ) {
        std::cout << "DNS Error occured" << std::endl;

        return EXIT_FAILURE;
    }
    std::cout << "!!!!" << hex << *(pair.second).get() << std::endl << dec;

    string s1("http:");
    string s2("http://");
    string s3("http://ab");
    string s4("http://ab/");
    string s5("http://ab:81");
    string s6("http://ab:81/");
    string s7("http://u@ab:81/");
    //    string s8("http://_@ab:11108/");
    string s8("http://_1@ab:23408/");
    string s9("hxttp://_1@ab:23408/sdsd");
    string s10("hxttp://_1:ya.ru@ya.ru:23408/ss");
    //string s11("hxttp://_1:ya.ru@ebay.com:2a3408/ss");
    URL url5(s5);
    URL url6(s6);
    URL url7(s7);
    URL url8(s8);
    URL url9(s9);
    URL url10(s10);
    //URL url11(s11);

    cerr << url5 << endl;
    cerr << url6 << endl;
    cerr << url7 << endl;
    cerr << url8 << endl;
    cerr << url9 << endl;
    cerr << url10 << endl;

    pair = resolver(url10.getHost());

    if ( pair.first == LobKo::DNSResult::DNS_RESOLVE_ERROR ) {
        std::cout << "DNS Error occured" << std::endl;

        return EXIT_FAILURE;
    }
    std::cout << "!!!!" << hex << *(pair.second).get() << std::endl << dec;




    std::cout << "main exit" << endl;
    return 0;
}

