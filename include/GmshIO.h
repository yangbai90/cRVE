#ifndef CRVE_GMSHIO_H
#define CRVE_GMSHIO_H

#include <iostream>
#include <iomanip>
#include <string> 
#include <vector> 

using namespace std;


class GmshIO
{
public:
    GmshIO();


    constexpr long int GetNodesNum() const {return _nNodes;}
    constexpr long int GetElmtsNum() const {return _nElmts;}
    constexpr int GetPhyGroupsNum() const {return _nPhyGroupNum;}

    constexpr double GetXmax() const {return _Xmax;}
    constexpr double GetXmin() const {return _Xmin;}
    constexpr double GetYmax() const {return _Ymax;}
    constexpr double GetYmin() const {return _Ymin;}
    constexpr double GetZmax() const {return _Zmax;}
    constexpr double GetZmin() const {return _Zmin;}    


private:
    vector<double> NodeCoords;
    vector<int> ElmtConn;
    int _nNodes,_nElmts,_nPhyGroupNum;
    double _Xmax,_Xmin,_Ymax,_Ymin,_Zmax,_Zmin;
};

#endif 
