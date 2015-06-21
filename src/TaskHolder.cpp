/* 
 * File:   TaskHolder.cpp
 * Author: s
 * 
 * Created on June 20, 2015, 10:07 PM
 */

#include "TaskHolder.h"

LobKo::TaskHolder::TaskHolder() {
    tasksVec_.reserve(16);
}

//TaskHolder::TaskHolder(const TaskHolder& orig) {
//}

LobKo::TaskHolder::~TaskHolder() {

}

void LobKo::TaskHolder::addTask(const Task& newTask) {
    tasksVec_.push_back(newTask);
}

vector<LobKo::Task>& LobKo::TaskHolder::getTasks() {
    return tasksVec_;
}

shared_ptr<LobKo::TaskHolder> LobKo::TaskHolderBuilder::build() {
    shared_ptr<TaskHolder> spBuildThis(new TaskHolder);

    spBuildThis->addTask(Task("http://www.cplusplus.com/img/bg_info.gif", "www.cplusplus.com.bg_info.gif"));
    spBuildThis->addTask(Task("http://www.cplusplus.com/v321/bg.png", "www.cplusplus.com.bg.png"));
    spBuildThis->addTask(Task("http://www.cplusplus.com/v321/bg.png", "www.cplusplus.com.bg.png2"));
    spBuildThis->addTask(Task("http://www.cplusplus.com/v321/bg.png", "www.cplusplus.com.bg.png3"));
    spBuildThis->addTask(Task("http://www.cplusplus.com/v321/bg.png", "www.cplusplus.com.bg.png4"));
    spBuildThis->addTask(Task("http://www.cplusplus.com/v321/__bg.png", "www.cplusplus.com.bg.png4")); //!!!
    spBuildThis->addTask(Task("http://tn.new.fishki.net/35/preview/1568470.jpg", "fishki.net.1568470.jpg"));
    spBuildThis->addTask(Task("http://fishki.net/", "fishki.net.html"));
    spBuildThis->addTask(Task("http://tn.new.fishki.net/2/upload/avatar/433219.jpg", "fishki.net.433219.jpg"));
    spBuildThis->addTask(Task("http://s.fishki.net/upload/post/201506/19/1571043/pirat1.jpg", "fishki.net.pirat1.jpg"));
    spBuildThis->addTask(Task("http://tn.new.fishki.net/2/upload/avatar/____63208.jpg", "fishki.net.63208.jpg")); //!!!!
    spBuildThis->addTask(Task("http://www.boost.org/gfx/space.png", "boost.org.space.png"));
    spBuildThis->addTask(Task("http://www.boost.org", "boost.org.html"));
    
    return spBuildThis;
}
