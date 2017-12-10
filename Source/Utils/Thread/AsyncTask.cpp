//
// Created by snaiperskaya on 10/12/17.
//

#include "AsyncTask.h"

std::map<TaskThread, std::mutex> AsyncTask::QueueLockMap;
std::map<TaskThread, std::vector<std::function<void()>>> AsyncTask::TaskMap;
