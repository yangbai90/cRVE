#include "CRVE.h"

void CRVE::LableRVE(){
    // _nPhysics=0;
    // _PhysicGroupDimVec.clear();
    // _PhysicID2NameVec.clear();
    // _PhysicName2IDVec.clear();
    bool HasParticle,HasMatrix;
    // for particle phase
    HasParticle=false;
    for(auto it:_PhysicID2NameVec){
        if(it.second=="particle"){
            HasParticle=true;
            break;
        }
    }
    if(!HasParticle){
        _nPhysics+=1;
        _PhysicID2NameVec.push_back(make_pair(_ParticlePhyID,"particle"));
        _PhysicName2IDVec.push_back(make_pair("particle",_ParticlePhyID));
        _PhysicGroupDimVec.push_back(_nMaxDim);
    }
    // for matrix phase
    HasMatrix=false;
    for(auto it:_PhysicID2NameVec){
        if(it.second=="matrix"){
            HasMatrix=true;
            break;
        }
    }
    if(!HasMatrix){
        _nPhysics+=1;
        _PhysicID2NameVec.push_back(make_pair(_MatrixPhyID,"matrix"));
        _PhysicName2IDVec.push_back(make_pair("matrix",_MatrixPhyID));
        _PhysicGroupDimVec.push_back(_nMaxDim);
    }

    // Now we split the m/p-left surface
    if(_MeshType==MeshType::GMSH2){
        _NewMeshFileName="new_"+_MeshFileName.substr(0,_MeshFileName.size()-6)+".msh";
    }
    else{
        _NewMeshFileName="new_"+_MeshFileName;
    }
    
    int iXmin=0,iXmax=0,iYmin=0,iYmax=0,iZmin=0,iZmax=0;
    vector<int> conn;
    vector<int> elConn;
    _XminElConn.clear();_XminElmtID.clear();_XminElmtPhyID.clear();_XminElmtTypeVec.clear();
    _XmaxElConn.clear();_XmaxElmtID.clear();_XmaxElmtPhyID.clear();_XmaxElmtTypeVec.clear();

    _YminElConn.clear();_YminElmtID.clear();_YminElmtPhyID.clear();_YminElmtTypeVec.clear();
    _YmaxElConn.clear();_YmaxElmtID.clear();_YmaxElmtPhyID.clear();_YmaxElmtTypeVec.clear();

    _ZminElConn.clear();_ZminElmtID.clear();_ZminElmtPyhID.clear();_ZminElmtTypeVec.clear();
    _ZmaxElConn.clear();_ZmaxElmtID.clear();_ZMaxElmtPhyID.clear();_ZmaxElmtTypeVec.clear();

    _XminElmtPhyNameVec.clear();_XmaxElmtPhyNameVec.clear();
    _YminElmtPhyNameVec.clear();_YmaxElmtPhyNameVec.clear();
    _ZminElmtPhyNameVec.clear();_ZmaxElmtPhyNameVec.clear();

    int elmttype,subelmttype,phyid;


    bool HasMLeft,HasMRight;
    bool HasMBottom,HasMTop;
    bool HasMBack,HasMFront;

    bool HasPLeft,HasPRight;
    bool HasPBottom,HasPTop;
    bool HasPBack,HasPFront;

    HasMLeft=HasMRight=HasMBottom=HasMTop=HasMBack=HasMFront=false;
    HasPLeft=HasPRight=HasPBottom=HasPTop=HasPBack=HasPFront=false;
    if(_nMaxDim<3){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: currently, crve only works for 3D case!!!                  ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }
    for (int e = 1; e <= _nElmts; ++e){
        elConn = GetIthElmtConn(e);
        elmttype = GetIthElmtType(e);
        phyid = _ElmtPhyIDVec[e - 1];
        //*********************************************
        // check the edge surfaces                  ***
        //*********************************************
        subelmttype = GetSurfaceElmtTypeViaBulkElmtType(elmttype);
        if (subelmttype == -1)
        {
            continue;
        } // unsupported case
        // for 3D case, we check the surface elements(2D)
        for (int isurface = 1; isurface <= GetElmtSurfaceNumsViaElmtType(elmttype); ++isurface)
        {
            conn = GetIthElmtJthSurfaceConn(elmttype, e, isurface);
            if (IsNodesOnSurface(1, _Xmin, conn))
            {
                iXmin += 1;
                _XminElConn.push_back(conn);
                _XminElmtID.push_back(e);
                _XminElmtTypeVec.push_back(subelmttype);

                if (phyid == _MatrixPhyID)
                {
                    _XminElmtPhyNameVec.push_back("mleft");
                    _XminElmtPhyID.push_back(1);
                    HasMLeft = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _XminElmtPhyNameVec.push_back("pleft");
                    _XminElmtPhyID.push_back(2);
                    HasPLeft = true;
                }
            }
            if (IsNodesOnSurface(1, _Xmax, conn))
            {
                iXmax += 1;
                _XmaxElConn.push_back(conn);
                _XmaxElmtID.push_back(e);
                _XmaxElmtTypeVec.push_back(subelmttype);

                if (phyid == _MatrixPhyID)
                {
                    _XmaxElmtPhyNameVec.push_back("mright");
                    _XmaxElmtPhyID.push_back(3);
                    HasMRight = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _XmaxElmtPhyNameVec.push_back("pright");
                    _XmaxElmtPhyID.push_back(4);
                    HasPRight = true;
                }
            }
            if (IsNodesOnSurface(2, _Ymin, conn))
            {
                iYmin += 1;
                _YminElConn.push_back(conn);
                _YminElmtID.push_back(e);
                _YminElmtTypeVec.push_back(subelmttype);

                if (phyid == _MatrixPhyID)
                {
                    _YminElmtPhyNameVec.push_back("mbottom");
                    _YminElmtPhyID.push_back(5);
                    HasMBottom = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _YminElmtPhyNameVec.push_back("pbottom");
                    _YminElmtPhyID.push_back(6);
                    HasPBottom = true;
                }
            }
            if (IsNodesOnSurface(2, _Ymax, conn))
            {
                iYmax += 1;
                _YmaxElConn.push_back(conn);
                _YmaxElmtID.push_back(e);
                _YmaxElmtTypeVec.push_back(subelmttype);

                if (phyid == _MatrixPhyID)
                {
                    _YmaxElmtPhyNameVec.push_back("mtop");
                    _YmaxElmtPhyID.push_back(7);
                    HasMTop = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _YmaxElmtPhyNameVec.push_back("ptop");
                    _YmaxElmtPhyID.push_back(8);
                    HasPTop = true;
                }
            }

            if (IsNodesOnSurface(3, _Zmin, conn))
            {
                iZmin += 1;
                _ZminElConn.push_back(conn);
                _ZminElmtID.push_back(e);
                _ZminElmtTypeVec.push_back(subelmttype);
                if (phyid == _MatrixPhyID)
                {
                    _ZminElmtPhyNameVec.push_back("mback");
                    _ZminElmtPyhID.push_back(9);
                    HasMBack = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _ZminElmtPhyNameVec.push_back("pback");
                    _ZminElmtPyhID.push_back(10);
                    HasPBack = true;
                }
            }
            if (IsNodesOnSurface(3, _Zmax, conn))
            {
                iZmax += 1;
                _ZmaxElConn.push_back(conn);
                _ZmaxElmtID.push_back(e);
                _ZmaxElmtTypeVec.push_back(subelmttype);

                if (phyid == _MatrixPhyID)
                {
                    _ZmaxElmtPhyNameVec.push_back("mfront");
                    _ZMaxElmtPhyID.push_back(11);
                    HasMFront = true;
                }
                else if (phyid == _ParticlePhyID)
                {
                    _ZmaxElmtPhyNameVec.push_back("pfront");
                    _ZMaxElmtPhyID.push_back(12);
                    HasPFront = true;
                }
            }
        }
    }

    //*******************************************************
    //*** Now all the information is ready
    //*** before we write to a new *.msh file
    //*** just check out the physical groups, make sure the 
    //*** information is completed!!!
    //*******************************************************
    bool IsInList=false;
    if(HasMLeft){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mleft"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(1,"mleft"));
            _PhysicName2IDVec.push_back(make_pair("mleft",1));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPLeft){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="pleft"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(2,"pleft"));
            _PhysicName2IDVec.push_back(make_pair("pleft",2));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    //******************************************************************
    if(HasMRight){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mright"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(3,"mright"));
            _PhysicName2IDVec.push_back(make_pair("mright",3));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPRight){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="pright"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(4,"pright"));
            _PhysicName2IDVec.push_back(make_pair("pright",4));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }

    //******************************************************************
    if(HasMBottom){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mbottom"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(5,"mbottom"));
            _PhysicName2IDVec.push_back(make_pair("mbottom",5));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPBottom){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="pbottom"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(6,"pbottom"));
            _PhysicName2IDVec.push_back(make_pair("pbottom",6));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    //******************************************************************
    if(HasMTop){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mtop"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(7,"mtop"));
            _PhysicName2IDVec.push_back(make_pair("mtop",7));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPTop){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="ptop"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(8,"ptop"));
            _PhysicName2IDVec.push_back(make_pair("ptop",8));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }

    //******************************************************************
    if(HasMBack){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mback"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(9,"mback"));
            _PhysicName2IDVec.push_back(make_pair("mback",9));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPBack){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="pback"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(10,"pback"));
            _PhysicName2IDVec.push_back(make_pair("pback",10));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }

    //******************************************************************
    if(HasMFront){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="mfront"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(11,"mfront"));
            _PhysicName2IDVec.push_back(make_pair("mfront",11));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
    if(HasPFront){
        IsInList=false;
        for(auto it:_PhysicID2NameVec){
            if(it.second=="pfront"){
                IsInList=true;
                break;
            }
        }
        if(!IsInList){
            _PhysicID2NameVec.push_back(make_pair(12,"pfront"));
            _PhysicName2IDVec.push_back(make_pair("pfront",12));
            _PhysicGroupDimVec.push_back(2);
            _nPhysics+=1;
        }
    }
}