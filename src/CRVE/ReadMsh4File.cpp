#include "CRVE.h"

void CRVE::ReadMsh4File(){
    ifstream in;
    in.open(_InputMeshFileName.c_str(),ios::in);
    while(!in.is_open()){
        cout<<"*** Error: cant open mesh file(name="<<_InputMeshFileName<<")!"<<endl;
        cout<<"***        please enter the correct file name:";
        cin>>_InputMeshFileName;
        in.open(_InputMeshFileName.c_str(),ios::in);
    }

    int MatrixMshPhyID=-1,ParticleMshPhyID=-1;
    string str;
    int nPhysics=0;
    vector<int> PhyDimVec;
    vector<pair<int,string>> PhyID2NameList;
    vector<double> NodeCoords;

    vector<vector<int>> ElmtConn;
    vector<int> ElmtDimVec,ElmtTypeVec,ElmtPhyIDVec,ElmtRealIndex;

    while(!in.eof()){
        getline(in,str);
        // cout<<"str="<<str<<endl;
        if(str.find("$PhysicalNames")!=string::npos){
            nPhysics=0;
            PhyDimVec.clear();PhyID2NameList.clear();
            int phydim,phyid;
            string phyname;
            in>>nPhysics;
            getline(in,str);
            for(int i=0;i<nPhysics;i++){
                getline(in,str);
                // cout<<"str="<<str<<endl;
                istringstream s_stream(str);
                s_stream>>phydim>>phyid>>phyname;
                phyname.erase(std::remove(phyname.begin(),phyname.end(),'"'),phyname.end());
                PhyDimVec.push_back(phydim);
                if(StrToLower(phyname).find("matrix")!=string::npos||
                   StrToLower(phyname).find("volume1")!=string::npos){
                    //if(phyid<100) phyid+=100000;
                    MatrixMshPhyID=phyid;
                    if(StrToLower(phyname).find("volume1")!=string::npos){
                        phyname="matrix";
                    }
                    // cout<<"work"<<endl;
                }
                if(StrToLower(phyname).find("particle")!=string::npos||
                   StrToLower(phyname).find("volume2")!=string::npos){
                    //if(phyid<100) phyid+=100000;
                    ParticleMshPhyID=phyid;
                    if(StrToLower(phyname).find("volume2")!=string::npos){
                        phyname="particle";
                    }
                }
                PhyID2NameList.push_back(make_pair(phyid,phyname));
            }
        }
        else if(str.find("$Nodes")!=string::npos){
            int nBlocks,minTag,maxTag;
            int nEntityDim,EntityTag,Parametric,numNodes;
            int count=0;
            int iInd,i,nodeid;
            double x,y,z;
            vector<int> temp;

            in>>nBlocks>>_nNodes>>minTag>>maxTag;
            _NodeCoords.resize(_nNodes*3,0.0);
            NodeCoords.resize(maxTag*3,0.0);
            _NodeRealIndex.resize(maxTag,0);
            _Cx=0.0;_Cy=0.0;_Cz=0.0;

            _Xmax=-1.0e16;_Xmin=1.0e16;
            _Ymax=_Xmax;_Ymin=_Xmin;
            _Zmax=_Xmax;_Zmin=_Xmin;
            int noderealid0;
            noderealid0=0;
            while(count<_nNodes){
                in>>nEntityDim>>EntityTag>>Parametric>>numNodes;
                temp.clear();
                for(i=0;i<numNodes;i++){
                    in>>iInd;
                    temp.push_back(iInd);
                    if(_NodeRealIndex[iInd-1]==0){
                        noderealid0+=1;
                        _NodeRealIndex[iInd-1]=noderealid0;
                    }
                }
                for(i=0;i<numNodes;i++){
                    in>>x>>y>>z;
                    // j=temp[i];
                    // nodeid=_NodeRealIndex[j-1];
                    nodeid=temp[i];
                    NodeCoords[(nodeid-1)*3+1-1]=x;
                    NodeCoords[(nodeid-1)*3+2-1]=y;
                    NodeCoords[(nodeid-1)*3+3-1]=z;


                    if(x>_Xmax) _Xmax=x;
                    if(x<_Xmin) _Xmin=x;
                    if(y>_Ymax) _Ymax=y;
                    if(y<_Ymin) _Ymin=y;
                    if(z>_Zmax) _Zmax=z;
                    if(z<_Zmin) _Zmin=z;

                    _Cx+=x/_nNodes;
                    _Cy+=y/_nNodes;
                    _Cz+=z/_nNodes;
                }
                count+=numNodes;
            }
            // cout<<"nNodes="<<_nNodes<<", nodeid="<<noderealid0<<endl;
            getline(in,str);
        }
        else if(str.find("$Elements")!=string::npos){
            int numEntity,minTag,maxTag;
            int EntityDim,EntityTag,elmttype,numElmts;
            int count;
            int elmtid,e;
            int phyid;
            int nodes,dim;
            int elmtrealid;
            string elmttypename;



            in>>numEntity>>_nElmts>>minTag>>maxTag;

            _ElmtConn.resize(_nElmts,vector<int>(0));
            _ElmtDimVec.resize(_nElmts,0);
            _ElmtTypeVec.resize(_nElmts,0);
            _ElmtPhyIDVec.resize(_nElmts,0);
            _ElmtRealIndex.resize(_nElmts,0);

            ElmtDimVec.resize(maxTag,0);
            ElmtTypeVec.resize(maxTag,0);
            ElmtPhyIDVec.resize(maxTag,0);
            ElmtRealIndex.resize(maxTag,0);
            ElmtConn.resize(maxTag,vector<int>(0));

            count=0;
            elmtrealid=0;
            while(count<_nElmts){
                in>>EntityDim>>EntityTag>>elmttype>>numElmts;
                // Entity tag is the final physical ID
                dim=EntityDim;
                phyid=EntityTag;
                nodes=GetElmtNodesNumViaGmshElmtType(elmttype);
                dim=GetElmtDimViaGmshElmtType(elmttype);
                elmttypename=GetElmtNameViaGmshElmtType(elmttype);
                if(dim>_nMaxDim) _nMaxDim=dim;
                if(dim<_nMinDim) _nMinDim=dim;
                if(phyid==MatrixMshPhyID||phyid==ParticleMshPhyID){
                    if(dim==3){
                        if(phyid<100) phyid+=100000;
                    }
                }

                if(dim==2){
                    _SurfaceElmtTypeName=elmttypename;
                }
                if(dim==3){
                    _BulkElmtTypeName=elmttypename;
                }

                for(e=0;e<numElmts;e++){
                    in>>elmtid;
                    if(_ElmtRealIndex[elmtid-1]==0){
                        elmtrealid+=1;
                        _ElmtRealIndex[elmtid-1]=elmtrealid;
                    }
                    
                    ElmtConn[elmtid-1].resize(nodes+1,0);
                    ElmtConn[elmtid-1][0]=nodes;
                    // if(elmtid==1){
                    //     cout<<"we have it, nnodes="<<nodes<<endl;
                    //     cout<<ElmtConn[elmtid-1][0]<<" "<<ElmtConn[elmtid-1].size()<<endl;
                    // }
                    for(int j=0;j<nodes;j++){
                        in>>ElmtConn[elmtid-1][j+1];
                    }
                    ElmtDimVec[elmtid-1]=dim;
                    ElmtTypeVec[elmtid-1]=elmttype;
                    ElmtPhyIDVec[elmtid-1]=phyid;
                }
                count+=numElmts;
            }
        }
    }
    in.close();

    // now we rearrange the node index and real node index
    int count=0;
    int nodeid,elmtid,nnodes;
    for(int i=0;i<static_cast<int>(_NodeRealIndex.size());i++){
        if(_NodeRealIndex[i]!=0){
            nodeid=_NodeRealIndex[i];
            _NodeCoords[(nodeid-1)*3+0]=NodeCoords[i*3+0];
            _NodeCoords[(nodeid-1)*3+1]=NodeCoords[i*3+1];
            _NodeCoords[(nodeid-1)*3+2]=NodeCoords[i*3+2];
            count+=1;
        }
    }
    if(count!=_nNodes){
        cout<<"***********************************************************"<<endl;
        cout<<"*** Error: real nodes num is less than msh's value  !!! ***"<<endl;
        cout<<"***********************************************************"<<endl;
        abort();
    }

    count=0;
    int j;
    int maxid=-1;
    for(int e=0;e<static_cast<int>(_ElmtRealIndex.size());e++){
        elmtid=_ElmtRealIndex[e];
        // if(e==0){
        //     cout<<"elmtit="<<elmtid<<",nodes="<<ElmtConn[e][0]<<", size="<<ElmtConn[e].size()<<endl;
        //     for(int i=0;i<ElmtConn[e][0];i++)cout<<ElmtConn[e][i+1]<<" ";
        //     cout<<endl;
        // }
        if(elmtid>0){
            count+=1;
            nnodes=ElmtConn[e][0];
            _ElmtConn[elmtid-1].resize(1+nnodes);
            _ElmtConn[elmtid-1][0]=nnodes;
            for(int i=0;i<nnodes;i++){
                j=ElmtConn[e][i+1];
                nodeid=_NodeRealIndex[j-1];
                if(nodeid>maxid) maxid=nodeid;
                _ElmtConn[elmtid-1][1+i]=nodeid;
            }
            _ElmtDimVec[elmtid-1]=ElmtDimVec[e];
            _ElmtTypeVec[elmtid-1]=ElmtTypeVec[e];
            _ElmtPhyIDVec[elmtid-1]=ElmtPhyIDVec[e];
        }
    }
    // cout<<"maxid="<<maxid<<endl;
    if(count!=_nElmts){
        cout<<"***********************************************************"<<endl;
        cout<<"*** Error: real elmts num is less than msh's value  !!! ***"<<endl;
        cout<<"***********************************************************"<<endl;
        abort();
    }



    _nBulkElmt=0;
    for(int e=0;e<_nElmts;e++){
        if(_ElmtDimVec[e]==_nMaxDim){
            _nBulkElmt+=1;
        }
    }
    // cout<<"nBulkElmts="<<_nBulkElmt<<", nElmts="<<_nElmts<<endl;

    if(MatrixMshPhyID==-1){
        cout<<"***********************************************************"<<endl;
        cout<<"*** Error: no physical id is given to matrix phase  !!! ***"<<endl;
        cout<<"***********************************************************"<<endl;
        abort();
    }

    if(ParticleMshPhyID==-1){
        cout<<"***********************************************************"<<endl;
        cout<<"*** Error: no physical id is given to particle phase!!! ***"<<endl;
        cout<<"***********************************************************"<<endl;
        abort();
    }
    if(!_HasMatrixID){
        if(MatrixMshPhyID<100) MatrixMshPhyID+=100000;
        _MatrixID=MatrixMshPhyID;
    }
    if(!_HasParticleID){
        if(ParticleMshPhyID<100) ParticleMshPhyID+=100000;
        _ParticleID=ParticleMshPhyID;
    }
}