#include <iostream>
#include "vec.h"

using namespace std;


int main()
{
    vector vec (20);

    cout << "vec = {";

    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] = i;
        cout << vec[i] << "; ";
    }

    cout << "}" << endl;

    vector vec_ = {2.,4.5,31.4,56.7};

    cout << "size of vec_ = " << vec_.size() << endl;

    vec[4] = vec_[1];

    cout << "vec[4]" << " = " << "vec_[1]" << " = " << vec[4] << endl;

    vec = vec_;

    cout << "New size vec = " << vec.size() << endl;

    vec_[3] = 10;

    cout << "new vec_[3] = " << vec_[3] << endl;

    const vector vec__ = {1.2,2.3,3.4,4.5,5.};

    cout << vec__[2] << endl;

    // vec__[2] = 7; нельзя, так как вектор константа


    return 0;
}
