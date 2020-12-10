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
    VAR(const A &a, int n)
    {
        alloc = a;
        elem = alloc.allocate(n);
        sz = n;
        space = n;
    }

    ~VAR()
    {
        cout << "VAR1\n";
        if (elem != nullptr)
            alloc.deallocate(elem, space);
        cout << "VAR2\n";
    }
};

template <typename T, typename A = allocator<T>>
class vectop: protected VAR<T,A>
{
public:
    vectop() : VAR <T, A> ()
    {
        this->sz = 0;
        this->elem = nullptr;
        this->space = 0;
    }

    vectop(initializer_list<T> lst) : VAR <T, A> (A(), lst.size())
    {
        this->sz = lst.size();
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

template <typename T, typename A>
vectop<T, A>::vectop(const vectop& arg)
{
    this->sz = arg.sz;
    this->elem = new T[arg.sz];
    copy(arg.elem, arg.elem+arg.sz, this->elem);
}

template <typename T, typename A>
vectop<T,A>&  vectop<T,A>::operator = (const vectop& a)
{
    if (this == &a)
        return *this ;
    if (a.sz <= this->space)
    {
        for (int i = 0; i<a.sz; ++i)
            this->elem[i] = a.elem[i];
        this->sz = a.sz;
        return *this ;
    }
    T *p = new T [a.sz];
    for (int i = 0; i < a.sz; i++)
        p[i] = a.elem[i];
    delete[] this->elem;
    this->space = a.sz;
    this->elem = p;
    return *this;
}

template <typename T, typename A>
vectop<T,A>::vectop (vectop&& a)
{
    this->sz = a.sz;
    this->elem = a.elem;
    a.sz = 0;
    a.elem = nullptr;
}

template <typename T, typename A>
vectop<T,A>&  vectop<T,A>::operator = (vectop&& a)
{
    delete[] this->elem;
    this->elem = a.elem;
    this->sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

template <typename T, typename A>
void vectop<T,A>::reserve (int newalloc)
{
    if (newalloc <= this->space)
        return;

    VAR<T,A> b(this->alloc, newalloc);

//    uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);

    for (int i = 0; i < this->sz; i++)
        b.elem[i] = this->elem[i];

    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&this->elem[i]);

    swap<VAR<T, A>>(*this, b);



}

template <typename T, typename A>
void vectop<T,A>::resize (int newsize, T val)
{
    this->reserve(newsize) ;
    for (int i = this->sz ; i < newsize ; ++i)
        this->alloc.construct(&this->elem[i], val);
    for (int i = this->sz ; i < newsize ; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->sz = newsize;
}

template <typename T, typename A>
void vectop<T,A>::push_back (const T& val)
{
    if (this->space == 0)
        reserve(8);
    else if (this->sz == this->space)
        reserve(2 * this->space);
    this->alloc.construct(&this->elem[this->sz], val);
    ++this->sz;
}

template <typename T, typename A>
T& vectop<T,A>:: at (int n)
{
    if (n < 0 || this->sz <= n)
        throw out_of_range("Выход за диапазон значений");
    return this->elem[n];
}
