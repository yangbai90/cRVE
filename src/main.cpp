#include <iostream>
#include "Welcome.h"

#include "CRVE.h"

using namespace std;


int main(int args,char *argv[]){
    const int Year=2020;
    const int Month=5;
    const int Day=31;
    const double Version=0.2;
    Welcome(Year,Month,Day,Version);
    CRVE crve(args,argv);

    crve.Run();
    
    return 0;
}
