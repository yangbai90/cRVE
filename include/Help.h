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
    //cout<<"***  -partall id      ---> lable all the particles to id              ***"<<endl;
    cout<<"***  -bounall[enable] ---> assign mx[y,z]min/max to cubic's boundary  ***"<<endl;
    cout<<"***                        assign px[y,z]min/max to cubic's boundary  ***"<<endl;
    cout<<"***  -bounmat[disable]---> assign mx[y,z]min/max to matrix's boundary ***"<<endl;
    cout<<"***                        only matrix is splitted in this case!!!    ***"<<endl;
    cout<<"***  -bounpar[disable]---> assign px[y,z]min/max to particle boundary ***"<<endl;
    cout<<"***                        only particle is splitted in this case!!!  ***"<<endl;
    cout<<"***  -print[enable]   ---> print out the results information          ***"<<endl;
    cout<<"*** Author: walkandthinker@CopyRight                                  ***"<<endl;
    cout<<"*** Contact: walkandthinker@gmail.com                                 ***"<<endl;
    cout<<"*************************************************************************"<<endl;
}

#endif 
