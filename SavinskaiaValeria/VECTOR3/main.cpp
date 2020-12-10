#include <iostream>
#include <string>
#include "std_lib_facilities.h"
#include "aaaaaaaaa.h"

using namespace std;

int main()
{
    vectop<int> vec = {1,2,3,4,5,6,7,8,9,10};
    vectop<string> vec_ = {"a", "aa", "aaa"};
    
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << '\n';

    for(int i = 0; i < vec_.size(); i++)
        cout << vec_[i] << ' ';
    cout << '\n';
    
        vec.push_back(2);

    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << '\n';
    
    return 0;
}
