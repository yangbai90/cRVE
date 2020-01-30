#include "CRVE.h"

void CRVE::Run(){
    _JobStartTime=chrono::high_resolution_clock::now();
    if(_MeshType==MeshType::GMSH2){
        ReadMeshFromGmsh2();
    }
    else if(_MeshType==MeshType::MSH){
        ReadMeshFromMsh();
    }
    else if(_MeshType==MeshType::MSH4){
        ReadMeshFromMsh4();
    }
    else{
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: unsupported mesh type !!!                                  ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }
    LableRVE();
    SaveNewMesh();
    _JobEndTime=chrono::high_resolution_clock::now();
    _Duration=chrono::duration_cast<std::chrono::microseconds>(_JobEndTime-_JobStartTime).count()/1.0e6;

    if(_IsPrint){
        PrintInfo();
    }
    
    cout<<"***-------------------------------------------------------------------***"<<endl;
   printf("*** Job finished, write new mesh to %31s   ***\n",_NewMeshFileName.c_str());
    cout<<"***-------------------------------------------------------------------***"<<endl;
    // cout<<"*************************************************************************"<<endl;
    printf("*************************************************************************\n");
    printf("*** Time elapse: %16.6e [s]                                 ***\n",_Duration);
    printf("*************************************************************************\n");
}