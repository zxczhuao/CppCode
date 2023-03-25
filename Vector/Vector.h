/*
 * @Author: zxczhuao 1906748395@qq.com
 * @Date: 2023-03-11 21:16:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-24 21:50:38
 * @FilePath: /CppCode/Vector/Vector.h
 * @Description: `
 * 
 */        
#pragma once
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
class Vector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    // 默认构造
    Vector()
        : _start(nullptr) 
        , _finish(nullptr) 
        , _endOfstorage(nullptr)
    {}
    // 拷贝构造
    Vector(const Vector<T>& v)
        : _start(nullptr)
        , _finish(nullptr)
        , _endOfstorage(nullptr)
    {
        _start = new T[v.Capacity()];
        for(int i = 0; i < v.Size(); i++)
        {
            _start[i] = v[i];
        }
        _finish = _start + v.Size();
        _endOfstorage = _start + v.Capacity();
    }

    size_t Capacity() const 
    {
        return _endOfstorage - _start;
    }

    size_t Size() const
    {
        return _finish - _start;
    }

    bool Empty()
    {
        return _start == _finish;
    }

    iterator begin()
    {
        return _start;
    }

    const_iterator begin() const
    {
        return _start;
    }

    iterator end()
    {
        return _finish;
    }

    const_iterator end() const
    {
        return _finish;
    }
    //析构函数
    ~Vector()
    {
        if(_start)
        {
            delete[] _start;
            _start = _finish = _endOfstorage = nullptr;
        }
    }

    Vector<T>& operator=(const Vector<T>& v)
    {
        if(this != &v)
        {
            T* temp = new T[v.Capacity()];
            for(int i = 0; i < v.Size(); i++)
            {
                temp[i] = v[i];
            }
            if(_start)
                delete[] _start;
            _start = temp;
            _finish = _start + v.Size();
            _endOfstorage = _start + v.Capacity();
        }
        return *this;
    }

    T& operator[](size_t pos){
        assert(pos < Size());
        return _start[pos];
    }
    
    const T& operator[](size_t pos) const{
        assert(pos < Size());
        return _start[pos];
    }

    void Reserve(size_t n){
        if(n > Capacity()){
            int len = Size();
            T* temp = new T[n];
            if(_start){
                // 注意这里的拷贝方式，不能直接使用memcpy，拷贝内存，而是应该调用赋值运算符重载进行拷贝
                for(int i = 0; i < len; i++){
                    temp[i] = _start[i];
                }
                delete[] _start;
            }
            _start = temp;
            _finish = _start + len;
            _endOfstorage = _start + n;
        }
    }

    iterator Earse(iterator pos){
        assert(pos < _finish && pos >= _start);
        iterator begin = pos + 1;
        while(begin < _finish)
        {
            *(begin - 1) = *begin;
            ++begin;
        }
        --_finish;
        return pos;
    }

    void push_back(const T& val){
        if(_finish == _endOfstorage)
        {
            size_t newCapacity = _start == nullptr?1:2*Capacity();
            Reserve(newCapacity);
        }
        *_finish++ = val;
    }

    void pop_back(){
        Earse(_finish - 1);
    }

    void Resize(size_t n, const T&val = T()){
        if(n <= Size()){
            _finish = _start + n;
        }
        else{
            if(n > Capacity())
                Reserve(n);
            while(_finish != _start + n){
                *_finish = val;
                ++_finish;
            }
        }
    }

    void Insert(iterator pos, const T& val){
        assert(pos <= _finish && pos >= _start);
        size_t len = pos - _start;
        if(_finish == _endOfstorage){
            size_t newCapacity = _start == nullptr?1:2*Capacity();
            Reserve(newCapacity);
        }
        // 如果发生了增容，pos的位置发生了改变，但是相对位置没变
        pos = _start + len;
        iterator end = _finish;
        while(end > pos){
            *end = *(end -1);
            end--;
        }
        *pos = val;
        _finish++;
    }
    
private:
    T* _start;
    T* _finish;
    T* _endOfstorage;
};

template<class T>
void PrintVector(const Vector<T>& v)
{
	for (int i = 0; i < (int)v.Size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

template<class T>
void PrintVectorIterator(const Vector<T>& v)
{
	//Vector<T>::const_iterator-->vit;
	//Vector<T>::const_iterator vit = v.begin();
	auto vit = v.begin();
	while (vit != v.end())
	{
		cout << *vit << " ";
		++vit;
		//前置++不会产生临时变量，后置++会产生
	}
	cout << endl;
}

template<class T>
void PrintVectorIterator2(const Vector<T>& v)
{
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}