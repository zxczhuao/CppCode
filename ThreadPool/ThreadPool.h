/*
 * @Author: zxczhuao
 * @Date: 2023-03-24 21:51:26
 * @LastEditTime: 2023-03-25 00:43:56
 * @FilePath: /CppCode/ThreadPool/ThreadPool.h
 * @Description: 
 * 
 */
#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <functional>
#include <vector>

class ThreadPool{
public:
    ThreadPool(size_t threadCount = 8): isClosed(false) {
        for(size_t i = 0; i < threadCount; ++i){
            threads.emplace_back(std::thread([this](){
                while(true){
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cond.wait(lock, [this](){
                            return isClosed || !tasks.empty();
                        });
                        if(isClosed && tasks.empty()) return;
                        task = tasks.front();
                        tasks.pop();
                    }
                    task();
                }
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