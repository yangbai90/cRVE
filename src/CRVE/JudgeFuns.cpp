#include "CRVE.h"

bool CRVE::IsNodeOnBC(const int &nodeid,const int &component,const double &bccoord)const{
    double pos;
    pos=GetIthNodeJthCoord(nodeid,component);

    if(abs(pos-bccoord)<=_Tol){
        return true;
    }else{
        return false;
    }
}

//**********************************
bool CRVE::IsNodesOnBC(const vector<int> &nodeids,const int &component,const double &bccoord)const{
    bool IsOn=true;
    for(auto it:nodeids){
        // cout<<it<<" ";
        if(!IsNodeOnBC(it,component,bccoord)){
            IsOn=false;
            break;
        }
    }
    // cout<<endl<<endl;
    return IsOn;
}