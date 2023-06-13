#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 观察者
class ObserverInterface{
public:
    virtual void work()=0;
    virtual ~ObserverInterface(){}
};

// 被观察者
class SubjetInterface{
public:
    virtual void Add(ObserverInterface*) = 0;
    virtual void Remove(ObserverInterface*) = 0;
    virtual void Notify() = 0;
    
    virtual ~SubjetInterface(){}
};

// 通知者
class Subject: public SubjetInterface{
public:
    void Add(ObserverInterface* obr) override{
        observers.push_back(obr);
    }
    void Remove(ObserverInterface* obr) override{
        auto pos = std::find(observers.begin(), observers.end(), obr);
        if(pos != observers.end())
            observers.erase(pos);
    }
    void Notify() override{
        for(const auto& obs:observers)
            obs->work();
    }
private:
    vector<ObserverInterface*> observers;
};

// 被通知者
class Observer1: public ObserverInterface{
public:
    void work() override{
        std::cout<<"状态更新-1"<<std::endl;
    }
};

class Observer2: public ObserverInterface{
public:
    void work() override{
        std::cout<<"状态更新-2"<<std::endl;
    }
};

int main(){
    Subject s1;
    ObserverInterface* o1 = new Observer1;
    ObserverInterface* o2 = new Observer2;
    s1.Add(o1);
    s1.Add(o2);

    s1.Notify();

    s1.Remove(o1);
    s1.Notify();
    delete o1;
    delete o2;
    return 0;   
}