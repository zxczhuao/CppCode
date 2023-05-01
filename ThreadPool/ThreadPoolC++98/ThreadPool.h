/*
 * @Author: zxczhuao
 * @Date: 2023-04-30 10:07:34
 * @LastEditTime: 2023-05-01 14:32:29
 * @FilePath: /CppCode/ThreadPool/ThreadPoolC++98/ThreadPool.h
 * @Description: 
 * 
 */
#pragma once
#include <pthread.h>
#include <deque>
#include <stdlib.h>
#include <string.h>
#include <string>

namespace z1
{
    
class Task
{
public:
    Task(void* arg = NULL, std::string taskName = "")
        :arg_(arg),  taskName_(taskName)
    {
    }

    virtual ~Task(){};

    void setArg(void* arg){
        arg_ = arg;
    }

    virtual int run() = 0;

protected:
    void* arg_;
    std::string taskName_;
};


class ThreadPool
{
public:
    ThreadPool(int threadsNum);
    ~ThreadPool();

    size_t size();
    size_t AddTask(Task* task);
    void stop();
    Task* take();
    static void* threadFunc(void*);
private:
    ThreadPool(const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);

private:    
    volatile bool isRunning_;
    int threadsNum_;
    std::deque<Task*> Taskdeque_;
    pthread_t* threads_;
    pthread_mutex_t mutex_;
    pthread_cond_t condition_;
};
}