#include <iostream>
#include "Welcome.h"

using namespace std;


int main(int args,char *argv[]){
    if(args||argv[0]){}
    const int Year=2020;
    const int Month=4;
    const int Day=15;
    const double Version=0.1;
    Welcome(Year,Month,Day,Version);
    return 0;
}
