#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    virtual ~Product(){}
    // 纯虚函数
    virtual string Operation() const = 0;
};

class ConcreteProductA: public Product{
public:
    string Operation() const override{
        return "ConcreteProductA"; 
    }
};

class ConcreteProductB: public Product{
public:
    string Operation() const override{
        return "ConcreteProductB";
    }
};

class Creator{
public:
    virtual ~Creator(){}
    virtual Product* FactoryMethod() const = 0;
    string SomeOperation() const {
        Product* product = this->FactoryMethod();
        string result = product->Operation();
        delete product;
        return result;
    }
};
class ConcreteCreatorA:public Creator{
public:
    Product* FactoryMethod() const override{
        return new ConcreteProductA();
    }
};

class ConcreteCreatorB:public Creator{
public:
    Product* FactoryMethod() const override{
        return new ConcreteProductB();
    }
};

void ClientCode(const Creator& creator){
    cout<<creator.SomeOperation()<<endl;
}

int main(){
    Creator* creator = new ConcreteCreatorA();
    ClientCode(*creator);
    cout<<endl;
    creator = new ConcreteCreatorB();
    ClientCode(*creator);
    delete creator;
    return  0;
}