#include<iostream>
#include"compression.hpp"
using namespace std;
int main(int agrc , char* argv[])
{
    if(agrc != 3)
    {
        cout<<"Too much arguments in command"<<endl;
        return 0;
    }

    Compression obj(argv[1], argv[2]);
    obj.Compress();

}
