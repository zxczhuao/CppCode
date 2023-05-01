#include "ThreadPool.h"
#include <unistd.h>
#include <assert.h>

namespace z1{
    ThreadPool::ThreadPool(int threadsNum){
        threadsNum_ = threadsNum;
        isRunning_ = true;
        //初始化线程
        threads_ = new pthread_t[threadsNum_];
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&condition_, NULL);
        for(int i = 0; i < threadsNum_; ++i)
            pthread_create(&threads_[i], NULL, threadFunc, this);
    }

    ThreadPool::~ThreadPool(){
        stop();
        for(auto it = Taskdeque_.begin(); it != Taskdeque_.end(); ++it)
            delete *it;
        Taskdeque_.clear();
    }

    size_t ThreadPool::AddTask(Task* task){
        pthread_mutex_lock(&mutex_);
        Taskdeque_.push_back(task);
        int size = Taskdeque_.size();
        pthread_mutex_unlock(&mutex_);
        pthread_cond_signal(&condition_);
        return size;
    }

    void ThreadPool::stop(){
        if(!isRunning_)
            return;
        isRunning_ = false;
        pthread_cond_broadcast(&condition_);

        for(int i = 0; i < threadsNum_; ++i){
            pthread_join(threads_[i], NULL);
        }

        delete threads_;
        threads_ = NULL;
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&condition_);
    }

    size_t ThreadPool::size(){
        pthread_mutex_lock(&mutex_);
        size_t size = Taskdeque_.size();
        pthread_mutex_unlock(&mutex_);
        return size;
    }

    Task* ThreadPool::take(){
        Task* task = NULL;
        while(!task){
            pthread_mutex_lock(&mutex_);
            while(Taskdeque_.empty() && isRunning_)
                pthread_cond_wait(&condition_, &mutex_);
            if(!isRunning_){
                pthread_mutex_unlock(&mutex_);
                break;
            }
            else if(Taskdeque_.empty()){
                pthread_mutex_unlock(&mutex_);
                continue;
            }
            assert(!Taskdeque_.empty());
            task = Taskdeque_.front();
            Taskdeque_.pop_front();
            pthread_mutex_unlock(&mutex_);
        }
        return task;
    }

    void* ThreadPool::threadFunc(void* threadData){
        pthread_t tid = pthread_self();
        ThreadPool* pool = static_cast<ThreadPool*>(threadData);
        while(pool->isRunning_){
            Task* task = pool->take();
            if(!task){
                printf("thread %lu will exit\n", tid);
                break;
            }
            assert(task);
            task->run();
        }
        return 0;
    }
}