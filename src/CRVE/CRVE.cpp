#include "CRVE.h"

CRVE::CRVE(){
    _Tol=1.0e-5;
    _MeshType=MeshType::MSH;
    _MeshFileName="";
    _ParticlePhaseName="particle";
    _MatrixPhaseName="matrix";

    _IsPrint=false;

    //**********************************************
    //*** basic information for the mesh
    //**********************************************
    _nMaxDim=-1,_nMinDim=4;
    _nNodes=0;
    _nElmts=0;_nVolumeElmts=0;
    _nSurfaceElmts=0;_nLineElmts=0;
    
    _NodeCoords.clear();
    _ElmtConn.clear();

    _Xmin=1.0e16;_Xmax=-1.0e16;
    _Ymin=_Xmin;_Ymax=_Xmax;
    _Zmin=_Xmin;_Zmax=_Zmin;
    _Cx=0.0;_Cy=0.0;_Cz=0.0;
    //**********************************************
    //*** basic information for physical groups
    //**********************************************
    _nPhysics=0;
    _ParticlePhyID=1;_MatrixPhyID=2;
    _PhysicGroupDimVec.clear();
    _PhysicID2NameVec.clear();
    _PhysicName2IDVec.clear();
}