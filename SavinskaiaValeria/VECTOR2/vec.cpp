#include "vec.h"

vector::vector(const vector& args): sz{args.sz}, elem{new double[args.sz]}
{
    copy(args.elem, args.elem+args.sz, elem);
}


vector& vector::operator = (const vector& vec)
{
    double *ss = new double [vec.sz];
    copy (vec.elem, vec.elem+vec.sz ,ss);
    delete [] elem;
    elem = ss;
    sz = vec.sz;
    return *this;      // Ссылка на тек. объект
}


vector::vector (vector&& vec)
: sz{vec.sz}, elem{vec.elem}
{
    vec.sz = 0;
    vec.elem = nullptr;
}


vector& vector::operator = (vector&& vec)
{
    delete[] elem;
    elem = vec.elem;
    sz = vec.sz;
    vec.elem = nullptr;
    vec.sz = 0;
    return *this;
}
