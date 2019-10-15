#include <iostream>
#include <string>    


#include "GmshIO.h"

using namespace std;


int main(int args,char *argv[])
{
    GmshIO gmshio;

    if(gmshio.Init(args,argv)){
        gmshio.Run();
    }

    return 0;
}
