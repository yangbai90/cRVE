#include "GmshIO.h"


void GmshIO::LableCubic()
{
    _NewGeoFileName="new_"+_GeoFileName;
    
    long int iXmin=0,iXmax=0,iYmin=0,iYmax=0,iZmin=0,iZmax=0;
    vector<long int> conn;
    vector<long int> elConn;
    _XminElConn.clear();_XminElmtID.clear();_XminElmtPhyID.clear();_XminElmtTypeVec.clear();
    _XmaxElConn.clear();_XmaxElmtID.clear();_XmaxElmtPhyID.clear();_XmaxElmtTypeVec.clear();

    _YminElConn.clear();_YminElmtID.clear();_YminElmtPhyID.clear();_YminElmtTypeVec.clear();
    _YmaxElConn.clear();_YmaxElmtID.clear();_YmaxElmtPhyID.clear();_YmaxElmtTypeVec.clear();

    _ZminElConn.clear();_ZminElmtID.clear();_ZminElmtPyhID.clear();_ZminElmtTypeVec.clear();
    _ZmaxElconn.clear();_ZmaxElmtID.clear();_ZMaxElmtPhyID.clear();_ZmaxElmtTypeVec.clear();

    _XminElmtPhyNameVec.clear();_XmaxElmtPhyNameVec.clear();
    _YminElmtPhyNameVec.clear();_YmaxElmtPhyNameVec.clear();
    _ZminElmtPhyNameVec.clear();_ZmaxElmtPhyNameVec.clear();

    int elmttype,subelmttype,phyid;
    for(long int e=1;e<=_nElmts;++e)
    {
        elConn=GetIthElmtConn(e);
        elmttype=GetIthElmtType(e);
        phyid=_ElmtPhyIDVec[e-1];
        //*********************************************
        // check the edge surfaces                  ***
        //*********************************************
        if(_nMaxDim==3){
            subelmttype=GetSurfaceElmtTypeViaBulkElmtType(elmttype);
            if(subelmttype==-1){return;}// unsupported case
            // for 3D case, we check the surface elements(2D)
            for(int isurface=1;isurface<=GetElmtSurfaceNumsViaElmtType(elmttype);++isurface){
                conn=GetIthElmtJthSurfaceConn(elmttype,e,isurface);
                if(NodesOnSurface(1,_Xmin,conn)){
                    iXmin+=1;
                    _XminElConn.push_back(conn);
                    _XminElmtID.push_back(e);
                    _XminElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _XminElmtPhyNameVec.push_back("mleft");
                            _XminElmtPhyID.push_back(1);
                        }
                        else if(phyid==_ParticlePhyID){
                            _XminElmtPhyNameVec.push_back("pleft");
                            _XminElmtPhyID.push_back(2);
                        }
                        else{
                            _XminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _XminElmtPhyNameVec.push_back("mleft");
                            _XminElmtPhyID.push_back(1);
                        }
                        else{
                            _XminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _XminElmtPhyNameVec.push_back("pleft");
                            _XminElmtPhyID.push_back(1);
                        }
                        else{
                            _XminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
                if(NodesOnSurface(1,_Xmax,conn)){
                    iXmax+=1;
                    _XmaxElConn.push_back(conn);
                    _XmaxElmtID.push_back(e);
                    _XmaxElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _XmaxElmtPhyNameVec.push_back("mright");
                            _XmaxElmtPhyID.push_back(3);
                        }
                        else if(phyid==_ParticlePhyID){
                            _XmaxElmtPhyNameVec.push_back("pright");
                            _XmaxElmtPhyID.push_back(4);
                        }
                        else{
                            _XmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _XmaxElmtPhyNameVec.push_back("mright");
                            _XmaxElmtPhyID.push_back(2);
                        }
                        else{
                            _XmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _XminElmtPhyNameVec.push_back("pright");
                            _XmaxElmtPhyID.push_back(2);
                        }
                        else{
                            _XminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
                if(NodesOnSurface(2,_Ymin,conn)){
                    iYmin+=1;
                    _YminElConn.push_back(conn);
                    _YminElmtID.push_back(e);
                    _YminElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _YminElmtPhyNameVec.push_back("mbottom");
                            _YminElmtPhyID.push_back(5);
                        }
                        else if(phyid==_ParticlePhyID){
                            _YminElmtPhyNameVec.push_back("pbottom");
                            _YminElmtPhyID.push_back(6);
                        }
                        else{
                            _YminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _YminElmtPhyNameVec.push_back("mbottom");
                            _YminElmtPhyID.push_back(3);
                        }
                        else{
                            _YminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _YminElmtPhyNameVec.push_back("pbottom");
                            _YminElmtPhyID.push_back(3);
                        }
                        else{
                            _YminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
                if(NodesOnSurface(2,_Ymax,conn)){
                    iYmax+=1;
                    _YmaxElConn.push_back(conn);
                    _YmaxElmtID.push_back(e);
                    _YmaxElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _YmaxElmtPhyNameVec.push_back("mtop");
                            _YmaxElmtPhyID.push_back(7);
                        }
                        else if(phyid==_ParticlePhyID){
                            _YmaxElmtPhyNameVec.push_back("ptop");
                            _YmaxElmtPhyID.push_back(8);
                        }
                        else{
                            _YmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _YmaxElmtPhyNameVec.push_back("mtop");
                            _YmaxElmtPhyID.push_back(4);
                        }
                        else{
                            _YmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _YmaxElmtPhyNameVec.push_back("ptop");
                            _YmaxElmtPhyID.push_back(4);
                        }
                        else{
                            _YmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
                if(NodesOnSurface(3,_Zmin,conn)){
                    iZmin+=1;
                    _ZminElConn.push_back(conn);
                    _ZminElmtID.push_back(e);
                    _ZminElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _ZminElmtPhyNameVec.push_back("mback");
                            _ZminElmtPyhID.push_back(9);
                        }
                        else if(phyid==_ParticlePhyID){
                            _ZminElmtPhyNameVec.push_back("pback");
                            _ZminElmtPyhID.push_back(10);
                        }
                        else{
                            _ZminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _ZminElmtPhyNameVec.push_back("mback");
                            _ZminElmtPyhID.push_back(5);
                        }
                        else{
                            _ZminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _ZminElmtPhyNameVec.push_back("pback");
                            _ZminElmtPyhID.push_back(5);
                        }
                        else{
                            _ZminElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
                if(NodesOnSurface(3,_Zmax,conn)){
                    iZmax+=1;
                    _ZmaxElconn.push_back(conn);
                    _ZmaxElmtID.push_back(e);
                    _ZmaxElmtTypeVec.push_back(subelmttype);
                    if(_IsSplitMatrixAndParticle){
                        if(phyid==_MatrixPhyID){
                            _ZmaxElmtPhyNameVec.push_back("mfront");
                            _ZMaxElmtPhyID.push_back(11);
                        }
                        else if(phyid==_ParticlePhyID){
                            _ZmaxElmtPhyNameVec.push_back("pfront");
                            _ZMaxElmtPhyID.push_back(12);
                        }
                        else{
                            _ZmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitMatrixOnly){
                        if(phyid==_MatrixPhyID){
                            _ZmaxElmtPhyNameVec.push_back("mfront");
                            _ZMaxElmtPhyID.push_back(6);
                        }
                        else{
                            _ZmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                    else if(_IsSplitParticleOnly){
                        if(phyid==_ParticlePhyID){
                            _ZmaxElmtPhyNameVec.push_back("pfront");
                            _ZMaxElmtPhyID.push_back(6);
                        }
                        else{
                            _ZmaxElmtPhyNameVec.push_back("invalid");
                        }
                    }
                }
            }
        }
        else{
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: currently, crve only works for 3D case!!!                  ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
    }

    //*******************************************************
    //*** Now all the information is ready
    //*** before we write to a new *.msh file
    //*** PrepareInfoBeforeSave should be called!!!
    //*******************************************************

}
