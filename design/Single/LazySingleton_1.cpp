/*
 * @Author: zxczhuao
 * @Date: 2023-03-24 21:50:16
 * @LastEditTime: 2023-03-25 13:16:20
 * @FilePath: /CppCode/design/Single/LazySingleton_1.cpp
 * @Description: 
 * 
 */
#include <mutex>

// 存在内存泄漏的问题
class Singleton_1{
public:
    static Singleton_1* getInstance(){
        if(instance == nullptr)
            instance = new Singleton_1();
        return instance; 
    }
private:
    Singleton_1() {};
    ~Singleton_1() {};
    Singleton_1(const Singleton_1&) = delete;
    Singleton_1& operator=(const Singleton_1&) = delete;
    static Singleton_1* instance;
};

Singleton_1* instance = nullptr;

/*
使用嵌套类Deletor来释放资源
为什么需要嵌套类？
    生成的唯一实例在堆上，由类内的静态指针所持有，静态成员在程序结束后才会被释放；
    静态变量是指向该唯一实例的指针，释放的资源是指针变量，不会调用析构函数
    因此，需要一个嵌套类或者一个静态函数来释放这个堆的空间
    嵌套类是一个静态对象，不是指针，当生命周期结束的时候，会释放这个嵌套类，调用它析构函数
    可以在这个析构函数里面释放懒汉类分配的资源
*/
class Singleton_2{
public:
    static Singleton_2* getInstance(){
        if(instance == nullptr)
            instance = new Singleton_2;
        return instance;
    }
private:
    class Deletor{
    public:
        ~Deletor(){
            if(Singleton_2::instance != nullptr)
                delete Singleton_2::instance;
        }
    };
    static Deletor deletor;
    Singleton_2(){};
    ~Singleton_2(){};
    Singleton_2(const Singleton_2&) = delete;
    Singleton_2* operator=(const Singleton_2&) = delete;
    static Singleton_2* instance;
};

Singleton_2* Singleton_2::instance = nullptr;
Singleton_2::Deletor Singleton_2::deletor;

/*
线程安全

*/
class Singleton_3
{
public:
    static Singleton_3* getInstance(){
        // 双检锁
        if(instance == nullptr){
            std::unique_lock<std::mutex> lock(m_Mutex);
            if(instance == nullptr)
                instance = new Singleton_3;
        }
        return instance;
    }
private:
    Singleton_3(){};
    ~Singleton_3(){};
    Singleton_3(const Singleton_3&) = delete;
    Singleton_3& operator=(const Singleton_3&) = delete;
    static std::mutex m_Mutex;
    static Singleton_3* instance;
};
std::mutex Singleton_3::m_Mutex;
Singleton_3 *Singleton_3::instance = nullptr;


/*Meyers Singleton*/
class Singleton_4
{
public:
    static Singleton_4* getInstance(){
        static Singleton_4 instance;
        return &instance;
    }
private:
    Singleton_4(){};
    ~Singleton_4(){};
    Singleton_4(const Singleton_4&) = delete;
    Singleton_4& operator=(const Singleton_4&) = delete;
};