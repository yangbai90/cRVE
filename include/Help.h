#ifndef CRVE_HELP_H
#define CRVE_HELP_H

#include <iostream>

using namespace std;

void PrintHelp()
{
    cout<<"*************************************************************************"<<endl;
    cout<<"*** Welcome to use cRVE (a simple cpp script to modify msh file)!     ***"<<endl;
    cout<<"*** Options:                                                          ***"<<endl;
    cout<<"***  -help            ---> print this message                         ***"<<endl;
    cout<<"***  -i test.msh      ---> i for input, msh file should follow it!    ***"<<endl;
    cout<<"***  -tol tolerance   ---> set tolerance for mesh splitting           ***"<<endl;
    cout<<"***  -print[enable]   ---> print out the results information          ***"<<endl;
    cout<<"*** Author: Yang Bai@CopyRight   2020                                 ***"<<endl;
    cout<<"*** Contact: walkandthinker@gmail.com                                 ***"<<endl;
    cout<<"*************************************************************************"<<endl;
}

#endif 
