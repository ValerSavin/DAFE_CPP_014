#pragma once


#include <iostream>
using namespace std;


class vector
{
    int sz;
    double* elem;

public:
    vector(int s) :sz{s}, elem {new double [sz]}
    {
        for(int i = 0; i<sz; ++i) elem[i] = 0.0;
    }

    int size() const
    {
        return sz;
    }

    ~vector()
    {
        delete [] elem;
    }

    vector (initializer_list<double> lst)
    : sz (lst.size()), elem {new double [sz]}
    {
        copy (lst.begin (), lst.end () , elem) ;  // Инициализация с помощью copy (), копирует диапазон lst.begin (), lst.end () в диапазон elem
    }

    vector (const vector&) ; // Копирование

    vector& operator = (const vector&);         // Копирующее присвоение

    vector (vector&& a) ; // Перемещающий конструктор

    vector& operator = (vector&&) ; // Перемещающее присваивание

    double& operator [] (int n)  { return elem [n] ; }      // Обращение по индексу

    const double& operator [] (int n) const  { return elem[n] ;}
};
