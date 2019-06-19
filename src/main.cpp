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
    gmshio.LableCubic();

    cout<<"PhyGroup IDs="<<gmshio.GetPhyGroupsNum()<<endl;
   
    cout<<gmshio.GetElmtsNum()<<endl;
    cout<<"Mesh has "<<gmshio.GetMshUniIDNum()<<" ids"<<endl;
    
    cout<<"Xmax="<<gmshio.GetXmax()<<", Xmin="<<gmshio.GetXmin()<<endl;
    cout<<"Ymax="<<gmshio.GetYmax()<<", Ymin="<<gmshio.GetYmin()<<endl;
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
