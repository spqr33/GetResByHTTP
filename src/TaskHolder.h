/* 
 * File:   TaskHolder.h
 * Author: s
 *
 * Created on June 20, 2015, 10:07 PM
 */

#ifndef TASKHOLDER_H
#define	TASKHOLDER_H
#include <vector>
#include "Task.h"
#include <memory>

using std::vector;
using std::shared_ptr;

namespace LobKo {

    class TaskHolder {
    public:
        TaskHolder();
        virtual ~TaskHolder();
        
        void addTask(const Task&);
        vector<Task>& getTasks();
    private:
        TaskHolder(const TaskHolder& orig);
        vector<Task> tasksVec_;
    };

    
    class TaskHolderBuilder {
    public:
        TaskHolderBuilder();
        ~TaskHolderBuilder();
        
        static shared_ptr<TaskHolder> build();
        
    };
}
#endif	/* TASKHOLDER_H */

