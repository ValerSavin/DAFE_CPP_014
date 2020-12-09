#include <iostream>

using namespace std;

class vector
{
    int sz;
    double* elem;

    public:

    vector(int s) :sz(s), elem(new double [s])
    {
        for(int i = 0; i<s; ++i) elem[i] = 0;
    }

    void set(int n, double v)
    {
        elem[n] = v;
    }

    int size() const
    {
        return sz;
    }

    double get(int n)
    {
        return elem[n];
    }

    ~vector()
    {
        delete [] elem;
    }
};

int main()
{
    vector vec (7);

    vec.set(0,3.2);
    vec.set(1,5.3);
    vec.set(2,3.);
    vec.set(3,5.6);
    vec.set(4,4.3);
    vec.set(5,11.67);
    vec.set(7,4.5);

    cout << "size = " << vec.size() << endl;

    for (int i = 0; i < vec.size(); i++)
        cout << i << " elem = " << vec.get(i) << endl;
}
