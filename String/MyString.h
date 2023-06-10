#include <cstring>
#include <iostream>
using namespace std;

class MyString{
public:
    MyString(const char*);
    MyString(const MyString&);
    ~MyString();
    MyString& operator=(const MyString&);
    MyString& operator=(const char*);
    size_t Size() const;
    const char* getString() const;
    char& operator[](const int index);
    friend ostream& operator<<(ostream&, const MyString&);
    //friend istream& operator>>(istream&, MyString&);
private:
    char* str;
    size_t size;
};

MyString::MyString(const char* _str = ""){
    size = strlen(str);
    str = new char[size + 1];
    strcpy(str, _str);  
}

MyString::MyString(const MyString& other){
    size = other.size;
    str = new char[size + 1];
    strcpy(str, other.str);
}

MyString::~MyString(){
    if(str)
        delete[] str;
    str = nullptr;
    size = 0; 
}

MyString& MyString::operator=(const MyString& other){
    if(this == &other)
        return *this;
    size = other.size;
    delete[] str;
    str = new char[size + 1];
    strcpy(str, other.str);
    return *this;
}

MyString& MyString::operator=(const char* _str){
    size = strlen(_str);
    delete[] str;
    str = new char[size + 1];
    strcpy(str, _str);
    return *this;
}

size_t MyString::Size() const{
    return size;
}

const char* MyString::getString() const{
    return str;
}

char& MyString::operator[](const int index){
    if(index >= size || index < 0)   return str[size - 1];
    return str[index - 1];
}

ostream& operator<<(ostream& output, const MyString& str){
    output<<str.getString();
    return output;
}