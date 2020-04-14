#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>


#include "FileFormat.h"

using namespace std;


class CRVE{
public:
    CRVE(int args,char *argv[]);

    void Run();
    void ReadMesh();
    void LableBC();

    void PrintInfo();

private:
    //**********************************************
    //*** for mesh reading functions
    //**********************************************
    void ReadMsh2File(); // for old version msh file 2.2,2.1,2.0
    void ReadMsh4File(); // for new version msh file 4.0,4.1,4.2
    void ReadGmshFile(); // for the gmsh file from netgen


    //**********************************************
    //*** for Gmsh related information functions
    //**********************************************
    int GetElmtDimViaGmshElmtType(const int &elmttype)const;
    int GetElmtSubDimViaGmshElmtType(const int &elmttype)const;
    int GetElmtNodesNumViaGmshElmtType(const int &elmttype)const;
    string GetElmtNameViaGmshElmtType(const int &elmttype)const;




private:
    //********************************************
    //*** for the mesh file information
    //********************************************
    string _InputMeshFileName;

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
    int _nNodes=0,_nElmts=0;
    int _nMaxDim=-1,_nMinDim=4;
    vector<double> _NodeCoords;
    vector<vector<int>> _ElmtConn;
    vector<string> _PhyGroupNameList;
    vector<pair<int,string>> _PhyID2NameList;
    vector<pair<string,int>> _PhyName2IDList;
    vector<int> _PhyDimVec;
};