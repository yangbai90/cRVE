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
    gmshio.SetTolerence(0.001);

    cout<<"PhyGroup IDs="<<gmshio.GetPhyGroupsNum()<<endl;
   
    cout<<"Elmts="<<gmshio.GetElmtsNum()<<", Nodes="<<gmshio.GetNodesNum()<<endl;
    cout<<"Mesh has "<<gmshio.GetMshUniIDNum()<<" ids"<<endl;
    
    cout<<"Xmax="<<gmshio.GetXmax()<<", Xmin="<<gmshio.GetXmin()<<endl;
    cout<<"Ymax="<<gmshio.GetYmax()<<", Ymin="<<gmshio.GetYmin()<<endl;
    cout<<"Zmax="<<gmshio.GetZmax()<<", Zmin="<<gmshio.GetZmin()<<endl;

    gmshio.LableCubic();
    gmshio.SaveLabledMesh();
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
