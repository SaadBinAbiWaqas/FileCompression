#include"first.hpp"
#include<iostream>
using namespace std;
x::x(){}
x::x(string s)
{
    this->s = s;
}
void x::print()
{
   cout<<"Hello World"<<endl;
   cout<<"Termial Entered string is : "<<s<<endl;
}
