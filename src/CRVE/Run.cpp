#include "CRVE.h"

void CRVE::ReadMesh(){
    if(_InputMeshFileName.find(".msh")!=string::npos||
       _InputMeshFileName.find(".gmsh2")!=string::npos){
        _MshFileVersion=GetGmshFileFormatVersion();
        if(_MshFileVersion>=2.0&&_MshFileVersion<3.0){
            ReadMsh2File();
        }
        else if(_MshFileVersion>=4.0){
            ReadMsh4File();
        }
    }
    else if(_InputMeshFileName.find("*.inp")!=string::npos){
        return;
    }
}
void CRVE::Run(){
    _StartTime=chrono::high_resolution_clock::now();
    ReadMesh();
    LableBC();
    SaveMesh();
}