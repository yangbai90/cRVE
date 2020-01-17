#pragma once

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string> 
#include <sstream>
#include <fstream>
#include <vector> 
#include <set>
#include <algorithm>
#include <chrono>


//***************************
#include "Types.h"


using namespace std;


class CRVE
{
public:
    CRVE();

    bool Init(int args,char *argv[]);// init the mesh file name, and job type ...
    void Run();
    //***********************************
    //*** basic setting functions
    //***********************************
    void SetTolerance(const double &tol){_Tol=tol;}
    void SetMeshFileName(string name){_MeshFileName=name;}
    void SetMeshTpye(const MeshType &meshtype){_MeshType=meshtype;}
    void SetParticlePhaseName(string name);
    void SetMatrixPhaseName(string name);
    void SetParticlePhyID(const int &id) {_ParticlePhyID=id;}
    void SetMatrixPhyID(const int &id) {_MatrixPhyID=id;}

    //***********************************
    //*** basic getting functions
    //***********************************
    double GetTolerance()const{return _Tol;}
    MeshType GetMeshType()const{return _MeshType;}
    string GetMeshFileName()const{return _MeshFileName;}
    string GetParticlePhaseName()const{return _ParticlePhaseName;}
    string GetMatrixPhaseName()const{return _MatrixPhaseName;}
    int GetParticlePhyID()const{return _ParticlePhyID;}
    int GetMatrixPhyID()const{return _MatrixPhyID;}
    double GetMshVersionFromMshFile(string filename) const;

    //****************************************
    //*** basic getting functions for mesh
    //****************************************
    double GetIthNodeJthCoord(const int &i,const int &j)const{return _NodeCoords[(i-1)*3+j-1];}
    
    int GetIthElmtNodesNum(const int &i)const{return _ElmtConn[i-1][0];}
    int GetIthElmtJthIndex(const int &i,const int &j)const{return _ElmtConn[i-1][j];}


private:
    void ReadMeshFromMsh();
    void ReadMeshFromMsh4();
    void ReadMeshFromGmsh2();

private:
    //**********************************************
    //*** basic data 
    //**********************************************
    double _Tol=1.0e-5;
    MeshType _MeshType;
    string _MeshFileName;
    string _ParticlePhaseName="particle";
    string _MatrixPhaseName="matrix";
    bool _IsPrint;

    //**********************************************
    //*** basic information for the mesh
    //**********************************************
    int _nMaxDim=0,_nMinDim=0;
    int _nNodes=0;
    int _nElmts=0,_nVolumeElmts=0,_nSurfaceElmts=0,_nLineElmts=0;
    
    vector<double> _NodeCoords;
    vector<vector<int>> _ElmtConn;
    vector<int> _ElmtDimVec,_ElmtPhyIDVec,_ElmtGeoIDVec;

    double _Xmin,_Xmax,_Ymin,_Ymax,_Zmin,_Zmax;
    double _Cx,_Cy,_Cz;
    //**********************************************
    //*** basic information for physical groups
    //**********************************************
    int _nPhysics;
    int _ParticlePhyID,_MatrixPhyID;
    vector<int> _PhysicGroupDimVec;
    vector<pair<int,string>> _PhysicID2NameVec;
    vector<pair<string,int>> _PhysicName2IDVec;

};