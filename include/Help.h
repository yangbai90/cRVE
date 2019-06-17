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
    cout<<"***  -partall id      ---> lable all the particles to id              ***"<<endl;
    cout<<"***  -bounall[enable] ---> assign x[y,z]min/max to cubic's boundary   ***"<<endl;
    cout<<"***  -bounsep[disable]---> assign x[y,z]min/max to matrix's boundary  ***"<<endl;
    cout<<"***                        assign px[y,z]min/max to particle' surface ***"<<endl;
    cout<<"***  -print[enable]   ---> print out the results information          ***"<<endl;
    cout<<"*** Author: walkandthinker@CopyRight                                  ***"<<endl;
    cout<<"*** Contact: walkandthinker@gmail.com                                 ***"<<endl;
    cout<<"*************************************************************************"<<endl;
}

#endif 
