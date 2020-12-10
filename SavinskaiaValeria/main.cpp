#include <iostream>
#include <string>
#include "std_lib_facilities.h"
#include "aaaaaaaaa.h"

using namespace std;

int main()
{
    vectop<int> v1 = {1,2,3,4,5,6,7,8,9,10};
    vectop<string> v2 = {"help", "me", "please", "I", "want", "to", "die"};
    v1.resize(13, 100);
    for (int i = 0; i < v1.size(); i++)
        cout<<v1[i]<<' ';
    cout<<'\n';

    for(int i = 0; i < v2.size(); i++)
        cout<<v2[i]<<' ';
    cout<<'\n';
}
