/* 
 * File:   SaveFile.h
 * Author: s
 *
 * Created on June 25, 2015, 2:18 PM
 */

#ifndef SAVEFILE_H
#define	SAVEFILE_H

#include "Action.h"
#include <string>
#include <fstream>


namespace LobKo {

    class SaveFile : public Action {
    public:
        explicit SaveFile(const std::string& saveTo_FileName); //throw std::runtime_error
        virtual ~SaveFile();

        virtual result takeData(const char* const startBuf, const char* const endBuf, uint64_t totaDataSize);
    private:
        SaveFile(const SaveFile& orig);
        
        uint64_t alreadyBytesSaved;
        std::ofstream fout;
        
        
    };

}
#endif	/* SAVEFILE_H */

