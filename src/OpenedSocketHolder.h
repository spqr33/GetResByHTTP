/* 
 * File:   OpenedSocketHolder.h
 * Author: s
 *
 * Created on June 17, 2015, 3:39 PM
 */

#ifndef OPENEDSOCKETHOLDER_H
#define	OPENEDSOCKETHOLDER_H
#include <set>

namespace LobKo {

    class OpenedSocketHolder {
    public:
        OpenedSocketHolder();
        ~OpenedSocketHolder();
        void add(int socket);
        int erase(int socket);
        unsigned int size() const;
        bool empty() const;
        
        bool find(int socket) const;
    private:
        OpenedSocketHolder(const OpenedSocketHolder& orig);

        std::set<int> sockets_;

    };
}
#endif	/* OPENEDSOCKETHOLDER_H */

