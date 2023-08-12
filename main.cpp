#include<iostream>
#include"first.hpp"
using namespace std;
int main(int agrc , char* argv[])
{
    if(agrc != 2)
    {
        cout<<"Too much arguments in command"<<endl;
        return 0;
    }


   x obj(argv[1]);
   obj.print();
}