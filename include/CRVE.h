#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <sstream>


#include "FileFormat.h"
#include "StringUtils.h"

using namespace std;


class CRVE{
public:
    CRVE(int args,char *argv[]);

    void Run();
    void ReadMesh();
    void LableBC();
    void SaveMesh();

    void PrintHelp() const;
    void PrintInfo() const;

private:
    //**********************************************
    //*** for mesh reading functions
    //**********************************************
    void ReadMsh2File(); // for old version msh file 2.2,2.1,2.0
    void ReadMsh4File(); // for new version msh file 4.0,4.1,4.2
    void ReadGmshFile(); // for the gmsh file from netgen



    //**********************************************
    //*** common get functions
    //**********************************************
    inline double GetIthNodeJthCoord(const int &i,const int &j)const{
        return _NodeCoords[(i-1)*3+j-1];
    }
    inline vector<int> GetIthElmtConn(const int &i)const{
        vector<int> temp;
        temp.clear();
        for(int j=1;j<=_ElmtConn[i-1][0];j++){
            temp.push_back(_ElmtConn[i-1][j]);
        }
        return temp;
    }

    inline int GetIthElmtType(const int &i)const{return _ElmtTypeVec[i-1];}
    inline int GetIthElmtPhyID(const int &i)const{return _ElmtPhyIDVec[i-1];}


    //**********************************************
    //*** for Gmsh related information functions
    //**********************************************
    double GetGmshFileFormatVersion()const;
    int GetElmtDimViaGmshElmtType(const int &elmttype)const;
    int GetElmtSubDimViaGmshElmtType(const int &elmttype)const;
    int GetElmtNodesNumViaGmshElmtType(const int &elmttype)const;
    int GetSubElmtTypeViaGmshElmtType(const int &elmttype)const;
    string GetElmtNameViaGmshElmtType(const int &elmttype)const;

    int GetSurfaceNumsViaGmshElmtType(const int &elmttype)const;
    vector<int> GetIthElmtJthSurfaceNodeIndex(const int &elmttype,const int &i,const int &j)const;




private:
    //*********************************************
    //*** Functions for labeling the boundaries
    //*********************************************
    bool IsNodeOnBC(const int &nodeid,const int &component,const double &bccoord)const;
    bool IsNodesOnBC(const vector<int> &nodeids,const int &component,const double &bccoord)const;
    bool IsSurfaceOnBC(const int &lineid,const int &component,const double &bccoord)const;

private:
    //********************************************
    //*** for the mesh file information
    //********************************************
    string _InputMeshFileName;
    string _OutputMeshFileName="";
    bool _HasFileName;

private:
    //*******************************************
    //*** for the args based options
    //*******************************************
    bool _HasFormatOption;
    FileFormat _OutputFileFormat=FileFormat::Msh;
    bool _HasPrint=true;

private:
    //*******************************************
    //*** for mesh information and physical groups
    //*******************************************
    double _Tol=1.0e-2;
    double _Xmax,_Xmin,_Ymax,_Ymin,_Zmax,_Zmin;
    double _Cx,_Cy,_Cz;
    int _nNodes=0,_nElmts=0,_nBulkElmt=0,_nRVEBCElmts=0;
    int _nMaxDim=-1,_nMinDim=4;
    vector<double> _NodeCoords;
    vector<vector<int>> _ElmtConn;
    vector<string> _PhyGroupNameList;
    vector<pair<int,string>> _PhyID2NameList;
    vector<pair<string,int>> _PhyName2IDList;
    // vector<pair<int,int>> _MshElmtDimPhyIDList;
    vector<pair<int,int>> _MeshUniDim2PhyID,_MeshUniDim2GeoID;
    vector<int> _PhyDimVec;
    vector<int> _ElmtDimVec,_ElmtPhyIDVec,_ElmtTypeVec;
    int _ParticleID,_MatrixID;
    bool _HasParticleID,_HasMatrixID;
    double _MshFileVersion;

    //*********************************************
    //*** for BC labeling
    //*********************************************
    vector<vector<int>> _RVEElmtConn;
    vector<int> _RVEElmtPhyID,_RVEElmtTypeID;
    vector<string> _RVEPhyGroupNameList;
    vector<pair<int,string>> _RVEPhyID2NameList;
    vector<pair<string,int>> _RVEPhyName2IDList;
    vector<int> _RVEPhyDimVec;
    vector<int> _RVEPhyElmtsNumList;


private:
    //*************************************
    //*** for time profiling
    //*************************************
    chrono::high_resolution_clock::time_point _StartTime,_EndTime;
};