#include <iostream>
#include "Welcome.h"

#include "CRVE.h"

using namespace std;


int main(int args,char *argv[]){
    const int Year=2020;
    const int Month=4;
    const int Day=15;
    const double Version=0.1;
    Welcome(Year,Month,Day,Version);
    CRVE crve(args,argv);

    crve.Run();
    
    return 0;
}
