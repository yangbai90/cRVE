#include "CRVE.h"

CRVE::CRVE(){
    _MeshFileName.clear();_NewMeshFileName.clear();
    _MeshType=MeshType::MSH;
    _Tol=1.0e-3;
    _IsPrint=false;
    _IsParticleIDSet=false;_IsMatrixIDSet=false;

    //*******************************************
    //*** basic physical information
    //*******************************************
    _ParticlePhyID=-1;_MatrixPhyID=-1;


    //*******************************************
    //*** basic information for mesh
    //*******************************************
    _nNodes=_nElmts=_nVolumeElmts=_nSurfaceElmts=0;
    _nMaxDim=-5;_nMinDim=5;

    _NodeCoords.clear();
    _ElmtConn.clear();

    _Xmin=1.0e16;_Xmax=-1.0e16;
    _Ymin=_Xmin;_Ymax=_Xmax;
    _Zmin=_Xmin;_Zmax=_Zmax;
    _Cx=_Cy=_Cz=0.0;
    
    
    //*******************************************
    //*** basic information for physical group
    //*******************************************
    _nPhysics=0;
    _PhysicGroupDimVec.clear();
    _PhysicID2NameVec.clear();
    _PhysicName2IDVec.clear();
    
    _ElmtDimVec.clear();_ElmtTypeVec.clear();
    _ElmtPhyIDVec.clear();_ElmtGeoIDVec.clear();
    _MeshUniPhyID.clear();_MeshUniGeoID.clear();

    _XminElConn.clear();_XmaxElConn.clear();
    _YminElConn.clear();_YmaxElConn.clear();
    _ZminElConn.clear();_ZmaxElConn.clear();

    _XminElmtID.clear();_XmaxElmtID.clear(),
    _YminElmtID.clear();_YmaxElmtID.clear();
    _ZminElmtID.clear();_ZmaxElmtID.clear();
    
    _XminElmtPhyID.clear();_XmaxElmtPhyID.clear();
    _YminElmtPhyID.clear();_YmaxElmtPhyID.clear();
    _ZminElmtPyhID.clear();_ZMaxElmtPhyID.clear();

    _XminElmtTypeVec.clear();_XmaxElmtTypeVec.clear();
    _YminElmtTypeVec.clear();_YmaxElmtTypeVec.clear();
    _ZminElmtTypeVec.clear();_ZmaxElmtTypeVec.clear();

    _XminElmtPhyNameVec.clear();_XmaxElmtPhyNameVec.clear();
    _YminElmtPhyNameVec.clear();_YmaxElmtPhyNameVec.clear();
    _ZminElmtPhyNameVec.clear();_ZmaxElmtPhyNameVec.clear();

}