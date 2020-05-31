#include "CRVE.h"

void CRVE::ReadMesh(){
    if(_InputMeshFileName.find(".msh")!=string::npos&&
       (_InputMeshFileName.find(".gmsh")==string::npos||
        _InputMeshFileName.find(".gmsh2")==string::npos)){
        _MshFileVersion=GetGmshFileFormatVersion();
        if(_MshFileVersion>=2.0&&_MshFileVersion<3.0){
            ReadMsh2File();
        }
        else if(_MshFileVersion>=4.0){
            ReadMsh4File();
        }
    }
    else if(_InputMeshFileName.find(".gmsh")!=string::npos||
            _InputMeshFileName.find(".gmsh2")!=string::npos){
        // cout<<"work"<<endl;
        ReadGmshFile();
    }
    else if(_InputMeshFileName.find("*.inp")!=string::npos){
        return;
    }
}
void CRVE::Run(){
    // cout<<"***-------------------------------------------------------------------***"<<endl;
    cout<<"*** Start to run the cRVE job ...                                     ***"<<endl;
    // cout<<"***-------------------------------------------------------------------***"<<endl;
    _StartTime=chrono::high_resolution_clock::now();
    ReadMesh();
    LableBC();
    SaveMesh();

    _StartFEMTime=chrono::high_resolution_clock::now();
    CalcAreaAndVolume();
    _EndFEMTime=chrono::high_resolution_clock::now();

    PrintInfo();
    _EndTime=chrono::high_resolution_clock::now();
    double Duration=chrono::duration_cast<std::chrono::microseconds>(_EndTime-_StartTime).count()/1.0e6;
    cout<<"***-------------------------------------------------------------------***"<<endl;
    printf("*** cRVE job finished !       Elapsed time: %16.3f s        ***\n",Duration);
    cout<<"*************************************************************************"<<endl;
    printf("*** Write result file to [%35s]        ***\n",_OutputMeshFileName.c_str());
    cout<<"*************************************************************************"<<endl;
}