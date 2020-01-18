#include <iostream>

#include "CRVE.h"

using namespace std;


int main(int args,char *argv[]){
    CRVE crve;
    if(crve.Init(args,argv)){
        crve.Run();
    }
    return 0;
}
