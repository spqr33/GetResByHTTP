/* 
 * File:   SaveFile.cpp
 * Author: s
 * 
 * Created on June 25, 2015, 2:18 PM
 */

#include "SaveFile.h"
#include <iostream>
#include <stdexcept>
#include <iostream>

LobKo::SaveFile::SaveFile(const std::string& saveTo_FileName) :
alreadyBytesSaved(0) {
    using std::ios_base;
    fout.open(saveTo_FileName, ios_base::out /*| ios_base::app */ | ios_base::binary);

    if ( !fout.is_open() ) {
        throw std::runtime_error("Can't open the file: " + saveTo_FileName);
    }
}

//SaveFile::SaveFile(const SaveFile& orig) {
//}

LobKo::SaveFile::~SaveFile() {
    fout.clear();
    fout.close();
}

LobKo::Action::result
LobKo::SaveFile::takeData(const char* const startBuf, const char* const endBuf, uint64_t totaDataSize) {
    uint64_t delta = endBuf - startBuf;

    totaDataSize -= alreadyBytesSaved;


    std::cout << "-----delta: " << delta << "totaDataSize: " << totaDataSize << std::endl;
    std::cout << "-----startBuf: " << std::hex << (void *) startBuf << "endBuf: " << (void *) endBuf << std::dec << std::endl;

    if ( delta < totaDataSize ) {
        fout.write(startBuf, delta);
        alreadyBytesSaved += delta;

        if ( !fout.good() ) {
            fout.close();
            return Action::ERROR_OCCURED;
        } else {
            return Action::NOT_ALL_DATA_RCVD;
        }
    } else {
        fout.write(startBuf, totaDataSize);
        alreadyBytesSaved += delta;

        if ( !fout.good() ) {
            fout.close();
            return Action::ERROR_OCCURED;
        } else {
            //Action::ALL_DATA_RCVD;
            return Action::ALL_DATA_RCVD;
        }
    }
}