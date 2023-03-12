#include <cassert>
#include <iostream>
#include <cstring>

class String{
public:
    typedef char* iterator;
    typedef const char* const_iterator;
    String(const char* str = ""){
        _size = strlen(str);
        _capacity = _size;
        _str = new char[_capacity + 1];
        strcpy(_str, str);
    }
    String(const String& str){
        _str = new char[str.capacity()+1];
        strcpy(_str, str._str);
        _size = str._size;
        _capacity = str._capacity;
    }
    ~String(){
        delete[] _str;
        _str = nullptr;
        _size = _capacity = 0;
    }
    // 重载
    char& operator[](size_t pos) {
        assert(pos >= 0 && pos < _size);
        return _str[pos];
    }
    const char& operator[] (size_t pos) const {
        assert(pos >= 0 && pos < _size);
        return _str[pos];
    }
    String& operator=(const String& str){
        if(this != &str){
            char* temp = new char[str.capacity() + 1];
            strcpy(temp, str._str);
            delete[] _str;
            _str = temp;
            _size = str._size;
            _capacity = str._capacity;
        }
        return *this;
    }
    String& operator+=(const char c){
        push_back(c);
        return *this;
    }
    String& operator+=(const char* str){
        append(str);
        return *this;
    }
    // 迭代器
    iterator begin(){
        return _str;
    }
    iterator end(){
        return _str + _size;
    }
    const_iterator begin() const{
        return _str;
    }
    const_iterator end() const{
        return _str + _size;
    }
    size_t size() const{
        return _size;
    }
    size_t capacity() const{
        return _capacity;
    }
    // 操作
    String& insert(size_t pos, char c){
        assert(pos >= 0 && pos <= _size);
        if(_size == _capacity){
            size_t newcapacity = _capacity == 0?4:_capacity*2;
            reserve(newcapacity);
        }
        _str[_size + 1] = '\0';
        for(int i = _size; i >= pos; i--){
            _str[i] = _str[i-1];
        }
        _size++;
        _str[pos] = c;
        return *this;
    }

    void push_back(char c){
        if(_size == _capacity){
            size_t newcapacity = _capacity == 0?4:_capacity*2;
            reserve(newcapacity);
            _capacity = newcapacity;
        }
        _str[_size] = c;
        _size++;
        _str[_size] = '\0';
    }
    void pop_back(){
        assert(_size > 0);
        _str[_size - 1] = '\0';
        _size--;
    }
    void append(char c){
        push_back(c);
    }
    void append(const char* str){
        size_t len = strlen(str);
        if(_size + len > _capacity){
            reserve(_size + len);
        }
        strcpy(_str + _size, str);
        _size += len;
    }
    String& erase(size_t pos, size_t len = npos){
        assert(pos >= 0 && pos < _size);
        size_t end = _size;
        if(len == npos || len >= _size - pos){
            _str[pos] = '\0';
            _size = pos;
        }else{
            strcpy(_str + pos, _str + pos + len);
        }
        return *this;
    }
    void reserve(size_t n){
        //n > capacity;
        char* temp = new char[n+1];
        strcpy(temp, _str);
        delete[] _str;
        _str = temp;
        _capacity = n;
    }
    void resize(size_t n, char ch = '\0'){
        assert(n >= 0);
        if(n <= _size){
            _size = n;
            _str[n] = '\0';
        } else if(n > _size && n <= _capacity){
            while(_size < n){
                _str[_size++] = ch;
            }
            _str[_size] = '\0';
        } else{
            reserve(n);
            while(_size < n){
                _str[_size++] = ch;
            }
            _str[_size] = '\0';
        }
    }
    size_t find(char ch, size_t pos = 0){
        assert(pos < _size);
        for(int i = pos; i < _size; i++){
            if(_str[i] == ch)
                return i;
        }
        return npos;
    }
    void clear(){
        _str[0] = '\0';
        _size = 0;
    }
    char* c_str() const{
        return _str;
    }
private:
    char* _str;
    size_t _size;
    size_t _capacity;
    const static size_t npos = -1;
};

std::ostream& operator<<(std::ostream& out, const String& str){
    for(size_t i = 0; i < str.size(); i++){
        out<<str[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& str){
    str.clear();
    char ch;
    ch = in.get();
    while(ch != '\0' && ch != '\0'){
        str += ch;
        ch = in.get();
    }
    return in;
}