#include "GmshIO.h"


void GmshIO::LableCubic()
{
    _NewGeoFileName="new_"+_GeoFileName;
    
    int iXmin=0,iXmax=0,iYmin=0,iYmax=0,iZmin=0,iZmax=0;
    vector<long int> conn(3,0);
    vector<long int> elConn;
    for(long int e=0;e<_nElmts;e++)
    {
        elConn=GetIthElmtConn(e+1);
        // check first surface
        conn[0]=elConn[0];conn[1]=elConn[2];conn[2]=elConn[1];
        if(NodesOnSurface(1,_Xmin,conn))
        {
            iXmin+=1;
            _XminElConn.push_back(conn);
        }
        else if(NodesOnSurface(1,_Xmax,conn))
        {
            iXmax+=1;
            _XmaxElConn.push_back(conn);
        }
        else if(NodesOnSurface(2,_Ymin,conn))
        {
            iYmin+=1;
            _YminElConn.push_back(conn);
        }
        else if(NodesOnSurface(2,_Ymax,conn))
        {
            iYmax+=1;
            _YmaxElConn.push_back(conn);
        }
        else if(NodesOnSurface(3,_Zmin,conn))
        {
            iZmin+=1;
            _ZminElConn.push_back(conn);
        }
        else if(NodesOnSurface(3,_Zmax,conn))
        {
            iZmax+=1;
            _ZmaxElconn.push_back(conn);
        }
    }

}
