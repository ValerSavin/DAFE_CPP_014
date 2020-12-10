#include "aaaaaaaaa.h"

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
    uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&this->elem[i]);
    swap<VAR<T, A>>(*this, b) ;
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
