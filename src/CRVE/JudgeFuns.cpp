#include "CRVE.h"

bool CRVE::IsNodesOnSurface(const int &component,const double &val,vector<int> &conn){
    double coord;
    int nnodes=conn.size();
    bool IsOnSurface=true;

    for(int i=0;i<nnodes;i++){
        coord=GetIthNodeJthCoord(conn[i],component);
        if(abs(coord-val)<_Tol){
            IsOnSurface=true;
        }
        else{
            IsOnSurface=false;
            break;
        }
    }
    return IsOnSurface;
}