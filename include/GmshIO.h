#ifndef CRVE_GMSHIO_H
#define CRVE_GMSHIO_H

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string> 
#include <sstream>
#include <fstream>
#include <vector> 
#include <set>
#include <algorithm>
using namespace std;


class GmshIO
{
public:
    GmshIO();
    bool ReadMeshFile();
    void SetMeshFileName(string filename) {_GeoFileName=filename;}

public:
    inline long int GetNodesNum() const {return _nNodes;}
    inline long int GetElmtsNum() const {return _nElmts;}
    inline int GetPhyGroupsNum() const {return _nPhyGroupNum;}

    inline double GetXmax() const {return _Xmax;}
    inline double GetXmin() const {return _Xmin;}
    inline double GetYmax() const {return _Ymax;}
    inline double GetYmin() const {return _Ymin;}
    inline double GetZmax() const {return _Zmax;}
    inline double GetZmin() const {return _Zmin;}    

private:
    // Gmsh file related information functions
    int GetNodesNumViaElmtType(int elmttype) const;
    int GetElmtDimViaElmtType(int elmttype) const;
    string GetElmtNameViaElmtType(int elmttype) const;
    

private:
    string _GeoFileName;
    vector<double> _NodeCoords;
    vector<vector<int>> _ElmtConn;
    int _nNodes,_nElmts,_nPhyGroupNum;
    double _Xmax,_Xmin,_Ymax,_Ymin,_Zmax,_Zmin;

    vector<int> _PhyGroupDimVec;
    vector<pair<int,string>> _PhyGroupArray;
    
    vector<int> _ElmtDimVec,_ElmtTypeVec,_ElmtPhyIDVec,_ElmtGeoIDVec;
};

#endif 
