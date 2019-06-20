#include "GmshIO.h"

bool GmshIO::NodesOnSurface(int component,double val,vector<long int> &conn)
{
    double x,y,z;
    int nnodes=conn.size();
    bool IsOnSurface=true;

    if(component==1)
    {
        IsOnSurface=true;
        for(int i=0;i<nnodes;i++)
        {
            x=GetIthNodeJthCoord(conn[i],1);
            if(abs(x-val)<_tol)
            {
                IsOnSurface=true;
            }
            else
            {
                IsOnSurface=false;
                return IsOnSurface;
            }
        }
        return IsOnSurface;
    }
    else if(component==2)
    {
        IsOnSurface=true;
        for(int i=0;i<nnodes;i++)
        {
            y=GetIthNodeJthCoord(conn[i],2);
            z=GetIthNodeJthCoord(conn[i],3);
            if(abs(y-val)<_tol)
            {
                IsOnSurface=true;
            }
            else
            {
                IsOnSurface=false;
                return IsOnSurface;
            }
        }
        return IsOnSurface;
    }
    else if(component==3)
    {
        IsOnSurface=true;
        for(int i=0;i<nnodes;i++)
        {
            z=GetIthNodeJthCoord(conn[i],3);
            if(abs(z-val)<_tol)
            {
                IsOnSurface=true;
            }
            else
            {
                IsOnSurface=false;
                return IsOnSurface;
            }
        }
        return IsOnSurface;
    }
    return false;
}
