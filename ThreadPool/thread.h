#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool{
public:
    // 构造函数
    ThreadPool(size_t threadCount = 8): isClosed(false){
        for(size_t i = 0; i < threadCount; ++i){
            threads.emplace_back(std::thread([this](){
                std::function<void()> task;
                {
                    //从任务队列中获取任务，如果没有任务则阻塞
                    std::unique_lock<std::mutex> lock(mtx);
                    cond.wait(lock, [this](){
                        return isClosed || !tasks.empty();
                    });
                    if(isClosed && tasks.empty()) return;
                    task = tasks.front();
                    tasks.pop();
                }
                task();
            }));
        }
    }

    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lock(mtx);
            isClosed = true;
        }
        cond.notify_all();
        for(std::thread &th: threads){
            if(th.joinable())
                th.join();
        }
    }

    template<class F>
    void add(F&& task){
        {
            std::unique_lock<std::mutex> locker(mtx);
            tasks.emplace(std::forward<F>(task));
        }
        cond.notify_one();
    }
private:
    std::mutex mtx;
    std::condition_variable cond;
    bool isClosed;
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
};