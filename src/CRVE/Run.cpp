#include "CRVE.h"

void CRVE::Run(){
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
}