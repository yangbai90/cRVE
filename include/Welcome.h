#pragma once

#include <iostream>

using namespace std;

void Welcome(const int &Year,const int &Month,const int &Day,const double &version){
    cout<<"***********************************************************"<<endl;
    cout<<"*** Welcome to use cRVE                                 ***"<<endl;
    cout<<"*** A c++ based tool for boundary labeling of RVE mesh  ***"<<endl;
   printf("*** Author: Yang Bai @ %4d.%02d.%02d                       ***\n",Year,Month,Day);
   printf("*** Version: %11.1f                                ***\n",version);
   cout<<"*** Bug report: walkandthinker@gmail.com                ***"<<endl;
   cout<<"*** Usage: 'crve -h' to see more options                ***"<<endl;
   cout<<"***********************************************************"<<endl;
}