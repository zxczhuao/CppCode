#include <iostream>
#include <mutex>

// 内存泄漏、线程不安全
class SingleT{
public:
    static SingleT* getInstance(){
        if(instance == nullptr){
            return new SingleT;
        }
        return instance;
    } 
private:
    SingleT() {};
    ~SingleT() {};
    SingleT(const SingleT&) = delete;
    SingleT* operator=(const SingleT&) = delete;
    static SingleT* instance;
};

SingleT* SingleT::instance = nullptr;

// 解决了内存泄漏，但是线程不安全
class SingleT2{
public:
    static SingleT2* getInstance(){
        if(instance == nullptr)
            return new SingleT2;
        return instance;
    }
private:
    SingleT2(){};
    ~SingleT2(){};
    SingleT2(const SingleT2&) = delete;
    SingleT2* operator=(const SingleT2&) = delete;
    static SingleT2* instance;
    class Deletor{
        ~Deletor(){
            if(instance != nullptr)
                delete instance;
        }
    };
    static Deletor deletor;
};

SingleT2::Deletor SingleT2::deletor;
SingleT2* SingleT2::instance = nullptr;


class SingleT3{
public:
    static SingleT3* getInstance(){
        if(instance == nullptr){
            std::unique_lock<std::mutex> lock(mtx);
            if(instance == nullptr)
                instance = new SingleT3;
        }
        return instance;
    }
private:
    SingleT3(){};
    ~SingleT3(){};
    SingleT3(const SingleT3&) = delete;
    SingleT3* operator=(const SingleT3&) = delete;
    static std::mutex mtx;
    static SingleT3* instance;
    class Deletor{
        ~Deletor(){
            if(instance != nullptr)
                delete instance;
        }
    }; 
    static Deletor deletor;
};

SingleT3::Deletor SingleT3::deletor;
SingleT3* SingleT3::instance = nullptr;


// static版本
class SingleT4{
public:
    static SingleT4& getInstance(){
        static SingleT4 instance;
        return instance;
    }
private:
    SingleT4(){};
    ~SingleT4(){};
    SingleT4(const SingleT4&) = delete;
    SingleT4& operator=(const SingleT4&) = delete;
};