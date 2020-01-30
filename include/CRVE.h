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


#include "Types.h"

using namespace std;


class CRVE{
public:
    CRVE();
    bool Init(int args,char *argv[]);
    void Run();

    //********************************************
    //** basic setting functions
    //********************************************
    void SetMeshFileName(string name){_MeshFileName=name;}
    void SetMeshType(MeshType meshtype){_MeshType=meshtype;}
    void SetTolerance(const double tol){_Tol=tol;}

    void SetParticlePhyID(const int &id){_ParticlePhyID=id;_IsParticleIDSet=true;}
    void SetMatrixPhyID(const int &id){_MatrixPhyID=id;_IsMatrixIDSet=true;}


    //********************************************
    //** basic getting functions
    //********************************************
    int GetNodesNumViaElmtType(int elmttype) const;
    int GetElmtDimViaElmtType(int elmttype) const;
    int GetElmtSurfaceNumsViaElmtType(int elmttype) const;
    int GetSurfaceElmtTypeViaBulkElmtType(int elmttype) const;
    vector<int> GetIthElmtJthSurfaceConn(const int &elmttype,const int &e,const int &j)const;
    string GetElmtNameViaElmtType(int elmttype) const;

    inline int GetIthElmtType(const int &e)const{
        return _ElmtTypeVec[e-1];
    }
    vector<int> GetIthElmtConn(const int &i)const{
        vector<int> tempconn;
        tempconn.resize(_ElmtConn[i-1][0]);
        for(int j=1;j<=_ElmtConn[i-1][0];j++){
            tempconn[j-1]=_ElmtConn[i-1][j];
        }
        return tempconn;
    }
    string GetMeshFileName()const{return _MeshFileName;}
    double GetMshVersionFromMshFile(string filename)const;

    inline double GetIthNodeJthCoord(const int &i,const int &j)const{return _NodeCoords[(i-1)*3+j-1];}

    bool IsNodesOnSurface(const int &component,const double &val,vector<int> &conn);

private:
    void ReadMeshFromGmsh2();
    void ReadMeshFromMsh();
    void ReadMeshFromMsh4();
    void LableRVE();
    void SaveNewMesh();

private:
    //*******************************************
    //*** basic private data information
    //*******************************************
    string _MeshFileName,_NewMeshFileName;
    MeshType _MeshType=MeshType::MSH;
    double _Tol;
    bool _IsPrint;
    bool _IsParticleIDSet,_IsMatrixIDSet;

    //*******************************************
    //*** basic physical information
    //*******************************************
    int _ParticlePhyID,_MatrixPhyID;


    //*******************************************
    //*** basic information for mesh
    //*******************************************
    int _nNodes,_nElmts,_nVolumeElmts,_nSurfaceElmts;
    int _nMaxDim,_nMinDim;

    vector<double> _NodeCoords;
    vector<vector<int>> _ElmtConn;

    double _Xmin,_Xmax,_Ymin,_Ymax,_Zmin,_Zmax;
    double _Cx,_Cy,_Cz;
    
    
    //*******************************************
    //*** basic information for physical group
    //*******************************************
    int _nPhysics;
    vector<int> _PhysicGroupDimVec;
    vector<pair<int,string>> _PhysicID2NameVec;
    vector<pair<string,int>> _PhysicName2IDVec;
    
    vector<int> _ElmtDimVec,_ElmtTypeVec,_ElmtPhyIDVec,_ElmtGeoIDVec;
    vector<int> _MeshUniPhyID,_MeshUniGeoID;

    vector<vector<int>> _XminElConn,_XmaxElConn,
                             _YminElConn,_YmaxElConn,
                             _ZminElConn,_ZmaxElConn;
    vector<int>      _XminElmtID,_XmaxElmtID,
                     _YminElmtID,_YmaxElmtID,
                     _ZminElmtID,_ZmaxElmtID;
    vector<int>      _XminElmtPhyID,_XmaxElmtPhyID,
                     _YminElmtPhyID,_YmaxElmtPhyID,
                     _ZminElmtPyhID,_ZMaxElmtPhyID;
    vector<int>      _XminElmtTypeVec,_XmaxElmtTypeVec,
                     _YminElmtTypeVec,_YmaxElmtTypeVec,
                     _ZminElmtTypeVec,_ZmaxElmtTypeVec;
    vector<string>   _XminElmtPhyNameVec,_XmaxElmtPhyNameVec,
                     _YminElmtPhyNameVec,_YmaxElmtPhyNameVec,
                     _ZminElmtPhyNameVec,_ZmaxElmtPhyNameVec;

};