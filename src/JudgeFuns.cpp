#include "GmshIO.h"

bool GmshIO::NodesOnSurface(int component,double val,vector<long int> &conn)
{
    double coord;
    int nnodes=conn.size();
    bool IsOnSurface=true;

    for(int i=0;i<nnodes;i++){
        coord=GetIthNodeJthCoord(conn[i],component);
        if(abs(coord-val)<_tol){
            IsOnSurface=true;
        }
        else{
            IsOnSurface=false;
            break;
        }
    }
    return IsOnSurface;
}
