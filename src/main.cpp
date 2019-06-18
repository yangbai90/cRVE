#include <iostream>
#include <string>    

#include "Help.h"
#include "GmshIO.h"

using namespace std;


int main(int args,char *argv[])
{
    GmshIO gmshio;
    

    gmshio.SetMeshFileName("test.msh");
    gmshio.ReadMeshFile();
   
   
    cout<<gmshio.GetElmtsNum()<<endl;
   

    if(args>=2)
    {
        if(string("-help").find(argv[1])!=string::npos )
        {
            PrintHelp();
            return 0;
        }
    }    
    return 0;
}
