/* 
 * File:   JumboBuff.h
 * Author: s
 *
 * Created on June 20, 2015, 1:59 PM
 */

#ifndef JUMBOBUFF_H
#define	JUMBOBUFF_H

namespace LobKo {

    struct JumboBuff {
        explicit   JumboBuff(unsigned int buffSize);
        ~JumboBuff();
    //private:
        void reInit();
        JumboBuff(const JumboBuff& orig);
        
        const unsigned int buffSize_;
        const char* const start_;
        const char* currentPos_;
        const char* watermark_;
        
    };
}

#endif	/* JUMBOBUFF_H */

