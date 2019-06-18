#include "GmshIO.h"

GmshIO::GmshIO()
{
    _nNodes=0;
    _nElmts=0;
    _nPhyGroupNum=0;

    _Xmax=-1.0e16;_Xmin=1.0e16;
    _Ymax=_Xmax;_Ymin=_Xmin;
    _Zmax=_Xmax;_Zmin=_Xmin;

    _NodeCoords.clear();
    _ElmtConn.clear();
}

