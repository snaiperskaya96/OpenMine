//
// Created by snaiperskaya on 10/12/17.
//

#ifndef OPENMINE_ASYNCTASK_H
#define OPENMINE_ASYNCTASK_H

#include <functional>
#include <vector>
#include <map>
#include <mutex>

enum class TaskThread
{
    GAME_THREAD
};

class AsyncTask
{
public:
    inline static void ExecuteOnThread(TaskThread Thread, const std::function<void()> &Predicate)
    {
        QueueLockMap[Thread].lock();
        TaskMap[Thread].push_back(Predicate);
        QueueLockMap[Thread].unlock();
    }

    inline static bool IsTaskAvailable(TaskThread Thread)
    {
        QueueLockMap[Thread].lock();
        bool Available = TaskMap[Thread].size() > 0;
        QueueLockMap[Thread].unlock();
        return Available;
    }

    inline static std::function<void()> GetTaskFromQueue(TaskThread Thread)
    {
        QueueLockMap[Thread].lock();
        std::function<void()> Delegate = TaskMap[Thread][0];
        TaskMap[Thread].erase(TaskMap[Thread].begin());
        QueueLockMap[Thread].unlock();
        return Delegate;
    }
protected:
    static std::map<TaskThread, std::mutex> QueueLockMap;
    static std::map<TaskThread, std::vector<std::function<void()>>> TaskMap;
};

#endif //OPENMINE_ASYNCTASK_H
