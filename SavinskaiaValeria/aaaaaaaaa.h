#pragma once

#include <iostream>
#include <string>
#include "std_lib_facilities.h"

using namespace std;

template <typename T, typename A>
class VAR
{
public:
    int sz;
    T *elem;
    int space;
    A alloc;
    VAR()
    {
        sz = 0;
        space = 0;
        elem = nullptr;
    }
    VAR(A &a, int n)
    {
        alloc = a;
        elem = a.allocate(n);
        sz = n;
        space = n;
    }
    ~VAR()
    {
        alloc.deallocate(elem, space);
    }
};

template <typename T, typename A = allocator<T>>
class vectop: private VAR<T,A>
{
public:
    vectop()
    {
        this->sz = 0;
        this->elem = nullptr;
        this->space = 0;
    }

    vectop(initializer_list<T> lst)
    {
        this->sz = lst.size();
        this->elem = new T[this->sz];
        copy(lst.begin(), lst.end (), this->elem) ;
    }

    explicit vectop(int s)
    {
        this->sz =  s;
        this->space = s;
        this->elem = new T[s];
    }

    int size()
    {
        return this->sz;
    }

    ~vectop()
    {
        delete[] this->elem;
    }

    vectop(const vectop&);
    vectop& operator= (const vectop&);
    vectop (vectop&& );
    vectop& operator= (vectop&&);
    T& operator [] (int n)
    {
        return this->elem[n];
    }
    const T& operator [] (int n) const
    {
        return this->elem[n];
    }

    void reserve(int newalloc);
    int capacity () const
    {
        return this->space;
    }
    void resize(int newsize , T val = T());
    void push_back (const T& val);

    T& at (int n);
    const T& at (int n) const;
};
