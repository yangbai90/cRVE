#include "CRVE.h"

void CRVE::LableBC(){

    if(_nMaxDim!=3){
        cout<<"***********************************************************"<<endl;
        cout<<"*** Error: crve only supports dim=3 case            !!! ***"<<endl;
        cout<<"***********************************************************"<<endl;
        abort();
    }

    _RVEElmtConn.clear();

    bool _HasMLeft=false,_HasMRight=false;
    bool _HasMBottom=false,_HasMTop=false;
    bool _HasMBack=false,_HasMFront=false;

    bool _HasPLeft=false,_HasPRight=false;
    bool _HasPBottom=false,_HasPTop=false;
    bool _HasPBack=false,_HasPFront=false;

    //*******************************
    //*** phy id ---> phy name mapping
    //***     1  ---> mleft
    //***     2  ---> pleft
    //***     3  ---> mright
    //***     4  ---> pright

    int elmttype,subelmttpye,phyid;
    int ee,e;
    _RVEElmtPhyID.clear();
    _RVEElmtTypeID.clear();
    vector<int> elConn,conn;
    _nRVEBCElmts=0;
    // cout<<"Tol"<<_Tol<<endl;
    for(ee=1;ee<=_nBulkElmt;ee++){
        e=ee+_nElmts-_nBulkElmt;
        elConn=GetIthElmtConn(e);
        elmttype=GetIthElmtType(e);
        subelmttpye=GetSubElmtTypeViaGmshElmtType(elmttype);
        phyid=GetIthElmtPhyID(e);
        // cout<<"e="<<e<<", phyid="<<phyid<<"elConn size="<<elConn.size()<<endl;
        
        for(int isurface=1;isurface<=GetSurfaceNumsViaGmshElmtType(elmttype);isurface++){
            conn=GetIthElmtJthSurfaceNodeIndex(elmttype,e,isurface);
            //***********************************************
            //***********************************************
            if(IsNodesOnBC(conn,1,_Xmin)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(1);
                    _HasMLeft=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(2);
                    _HasPLeft=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            //****************************************
            if(IsNodesOnBC(conn,1,_Xmax)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(3);
                    _HasMRight=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(4);
                    _HasPRight=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            //***********************************************
            //***********************************************
            if(IsNodesOnBC(conn,2,_Ymin)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(5);
                    _HasMBottom=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(6);
                    _HasPBottom=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            //****************************************
            if(IsNodesOnBC(conn,2,_Ymax)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(7);
                    _HasMTop=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(8);
                    _HasPTop=true;
                }
                else{
                    cout<<"Ymax"<<", phyid="<<phyid<<", matrix id="<<_MatrixID
                        <<", particle id="<<_ParticleID
                        <<", elmt id="<<e<<endl;
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            //***********************************************
            //***********************************************
            if(IsNodesOnBC(conn,3,_Zmin)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(9);
                    _HasMBack=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(10);
                    _HasPBack=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            //***********************************************
            if(IsNodesOnBC(conn,3,_Zmax)){
                _RVEElmtConn.push_back(conn);
                _RVEElmtTypeID.push_back(subelmttpye);
                _nRVEBCElmts+=1;
                if(phyid==_MatrixID){
                    // for mleft
                    _RVEElmtPhyID.push_back(11);
                    _HasMFront=true;
                }
                else if(phyid==_ParticleID){
                    _RVEElmtPhyID.push_back(12);
                    _HasPFront=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: some element dosnt belongs to either matrix or particle!!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
        }
    }

    // cout<<"nLeft="<<_Left.size()<<", nRight="<<_Right.size()<<endl;

    if(_nRVEBCElmts<1){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: cant find bc elements for the RVE                      !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }

    _RVEPhyGroupNameList.clear();
    _RVEPhyID2NameList.clear();
    _RVEPhyName2IDList.clear();
    _RVEPhyDimVec.clear();

    if(_HasMLeft){
        _RVEPhyGroupNameList.push_back("mleft");
        _RVEPhyID2NameList.push_back(make_pair(1,"mleft"));
        _RVEPhyName2IDList.push_back(make_pair("mleft",1));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPLeft){
        _RVEPhyGroupNameList.push_back("pleft");
        _RVEPhyID2NameList.push_back(make_pair(2,"pleft"));
        _RVEPhyName2IDList.push_back(make_pair("pleft",2));
        _RVEPhyDimVec.push_back(2);
    }
    //**************************
    if(_HasMRight){
        _RVEPhyGroupNameList.push_back("mright");
        _RVEPhyID2NameList.push_back(make_pair(3,"mright"));
        _RVEPhyName2IDList.push_back(make_pair("mright",3));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPRight){
        _RVEPhyGroupNameList.push_back("pright");
        _RVEPhyID2NameList.push_back(make_pair(4,"pright"));
        _RVEPhyName2IDList.push_back(make_pair("pright",4));
        _RVEPhyDimVec.push_back(2);
    }

    //********************************************
    //********************************************
    if(_HasMBottom){
        _RVEPhyGroupNameList.push_back("mbottom");
        _RVEPhyID2NameList.push_back(make_pair(5,"mbottom"));
        _RVEPhyName2IDList.push_back(make_pair("mbottom",5));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPBottom){
        _RVEPhyGroupNameList.push_back("pbottom");
        _RVEPhyID2NameList.push_back(make_pair(6,"pbottom"));
        _RVEPhyName2IDList.push_back(make_pair("pbottom",6));
        _RVEPhyDimVec.push_back(2);
    }
    //**************************
    if(_HasMTop){
        _RVEPhyGroupNameList.push_back("mtop");
        _RVEPhyID2NameList.push_back(make_pair(7,"mtop"));
        _RVEPhyName2IDList.push_back(make_pair("mtop",7));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPTop){
        _RVEPhyGroupNameList.push_back("ptop");
        _RVEPhyID2NameList.push_back(make_pair(8,"ptop"));
        _RVEPhyName2IDList.push_back(make_pair("ptop",8));
        _RVEPhyDimVec.push_back(2);
    }

    //********************************************
    //********************************************
    if(_HasMBack){
        _RVEPhyGroupNameList.push_back("mback");
        _RVEPhyID2NameList.push_back(make_pair(9,"mback"));
        _RVEPhyName2IDList.push_back(make_pair("mback",9));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPBack){
        _RVEPhyGroupNameList.push_back("pback");
        _RVEPhyID2NameList.push_back(make_pair(10,"pback"));
        _RVEPhyName2IDList.push_back(make_pair("pback",10));
        _RVEPhyDimVec.push_back(2);
    }
    //**************************
    if(_HasMFront){
        _RVEPhyGroupNameList.push_back("mfront");
        _RVEPhyID2NameList.push_back(make_pair(11,"mfront"));
        _RVEPhyName2IDList.push_back(make_pair("mfront",11));
        _RVEPhyDimVec.push_back(2);
    }
    if(_HasPFront){
        _RVEPhyGroupNameList.push_back("pfront");
        _RVEPhyID2NameList.push_back(make_pair(12,"pfront"));
        _RVEPhyName2IDList.push_back(make_pair("pfront",12));
        _RVEPhyDimVec.push_back(2);
    }

    _RVEPhyGroupNameList.push_back("matrix");
    _RVEPhyID2NameList.push_back(make_pair(_MatrixID,"matrix"));
    _RVEPhyName2IDList.push_back(make_pair("matrix",_MatrixID));
    _RVEPhyDimVec.push_back(3);

    _RVEPhyGroupNameList.push_back("particle");
    _RVEPhyID2NameList.push_back(make_pair(_ParticleID,"particle"));
    _RVEPhyName2IDList.push_back(make_pair("particle",_ParticleID));
    _RVEPhyDimVec.push_back(3);

    _RVEPhyElmtsNumList.resize(1+_RVEPhyGroupNameList.size(),0);


}