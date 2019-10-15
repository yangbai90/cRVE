#include "GmshIO.h"

GmshIO::GmshIO()
{
    _nNodes=0;
    _nElmts=0;
    _nPhyGroupNum=0;

    _Xmax=-1.0e16;_Xmin=1.0e16;
    _Ymax=_Xmax;_Ymin=_Xmin;
    _Zmax=_Xmax;_Zmin=_Xmin;

    _nMaxDim=0;_nMinDim=3;

    _NodeCoords.clear();
    _ElmtConn.clear();

    _ElmtDimVec.clear();_ElmtTypeVec.clear();
    _ElmtPhyIDVec.clear();_ElmtGeoIDVec.clear();
    _MeshUniPhyID.clear();_MeshUniGeoID.clear();
}

//*********************
void GmshIO::Run(){
    _StartTime=chrono::high_resolution_clock::now();
    ReadMeshFile();
    LableCubic();
    SaveLabledMesh();
    _EndTime=chrono::high_resolution_clock::now();
    if(_IsPrint){
        Print();
    }
}
//*********************************
void GmshIO::Print() const{
    printf("*************************************************************************\n");
    printf("*** Job information summary:                                          ***\n");
    printf("***   Xmax=%14.6e,  Xmin=%14.6e,  Cx=%13.6e    ***\n",_Xmax,_Xmin,_Cx);
    printf("***   Ymax=%14.6e,  Ymin=%14.6e,  Cy=%13.6e    ***\n",_Ymax,_Ymin,_Cy);
    printf("***   Zmax=%14.6e,  Zmin=%14.6e,  Cz=%13.6e    ***\n",_Zmax,_Zmin,_Cz);
    printf("***   Physical group IDs=%3d , max dim=%2d, min dim=%2d, tol=%10.4e ***\n",GetPhyGroupsNum(),_nMaxDim,_nMinDim,_tol);
    printf("***   Mesh has %6d unique pyhsical ids                             ***\n",GetMshUniIDNum());
    if(_IsSplitMatrixAndParticle){
        printf("***   Split both the matrix and particles boundaries                  ***\n");
    }
    else if(_IsSplitMatrixOnly){
        printf("***   Split only the matrix boundaries                                ***\n");
    }
    else if(_IsSplitParticleOnly){
        printf("***   Split only the particle boundaries                              ***\n");
    }
    printf("***   Final physical group information:                               ***\n");
    printf("***   Physical ID-------physical dim--------------physical name       ***\n");
    for(int i=0;i<(int)newphyname.size();++i){
        printf("***   %5d             %5d  %32s       ***\n",newphyid[i],newphydim[i],newphyname[i].c_str());
    }
    printf("*************************************************************************\n");
    printf("*** Write results to %35s              ***\n",_NewGeoFileName.c_str());
    double duration=chrono::duration_cast<std::chrono::microseconds>(_EndTime-_StartTime).count()/1.0e6;
    printf("*** Time elapse: %16.6e [s]                                 ***\n",duration);
    printf("*************************************************************************\n");
}

