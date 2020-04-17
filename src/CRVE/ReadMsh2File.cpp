#include "CRVE.h"

void CRVE::ReadMsh2File(){
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
    while(!in.eof()){
        getline(in,str);
        // cout<<"str="<<str<<endl;
        if(str.find("$PhysicalNames")!=string::npos){
            nPhysics=0;
            PhyDimVec.clear();
            PhyID2NameList.clear();
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
            _nNodes=0;
            in>>_nNodes;
            int id;
            double x,y,z;


            _Cx=0.0;_Cy=0.0;_Cz=0.0;

            _Xmax=-1.0e16;_Xmin=1.0e16;
            _Ymax=_Xmax;_Ymin=_Xmin;
            _Zmax=_Xmax;_Zmin=_Xmin;
            _NodeCoords.resize(_nNodes*3,0.0);
            for(int i=0;i<_nNodes;i++){
                in>>id>>x>>y>>z;
                _NodeCoords[(id-1)*3+1-1]=x;
                _NodeCoords[(id-1)*3+2-1]=y;
                _NodeCoords[(id-1)*3+3-1]=z;
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
            getline(in,str);
        }
        else if(str.find("$Elements")!=string::npos){
            _nElmts=0;
            in>>_nElmts;
            _ElmtConn.resize(_nElmts,vector<int>(0));

            // cout<<"nElmts="<<_nElmts<<endl;
            
            _ElmtDimVec.resize(_nElmts,0);
            _ElmtTypeVec.resize(_nElmts,0);
            _ElmtPhyIDVec.resize(_nElmts,0);

            int elmtid;
            int phyid,geoid,ntags,elmttype;
            int nodes,dim;
            _MeshUniDim2PhyID.clear();
            _MeshUniDim2GeoID.clear();
            for(int ie=0;ie<_nElmts;ie++){
                in>>elmtid>>elmttype>>ntags>>phyid>>geoid;
                if(phyid==0&&geoid!=0) phyid=geoid;
                nodes=GetElmtNodesNumViaGmshElmtType(elmttype);
                dim=GetElmtDimViaGmshElmtType(elmttype);


                if(dim>_nMaxDim) _nMaxDim=dim;
                if(dim<_nMinDim) _nMinDim=dim;

                if(phyid==MatrixMshPhyID||phyid==ParticleMshPhyID){
                    if(dim==3){
                        if(phyid<100) phyid+=100000;
                    }
                }


                _ElmtConn[elmtid-1].resize(nodes+1,0);
                _ElmtConn[elmtid-1][0]=nodes;
                for(int j=0;j<nodes;j++){
                    in>>_ElmtConn[elmtid-1][j+1];
                }
                _ElmtDimVec[elmtid-1]=dim;
                _ElmtTypeVec[elmtid-1]=elmttype;
                _ElmtPhyIDVec[elmtid-1]=phyid;

                
                if(_MeshUniDim2PhyID.size()==0){
                    _MeshUniDim2PhyID.push_back(make_pair(dim,phyid));
                    _MeshUniDim2GeoID.push_back(make_pair(dim,geoid));
                }
                else{
                    bool IsUni=true;
                    for(unsigned int i=0;i<_MeshUniDim2PhyID.size();i++){
                        if(dim==_MeshUniDim2PhyID[i].first && phyid==_MeshUniDim2PhyID[i].second){
                            IsUni=false;
                            break;
                        }
                    }
                    if(IsUni){
                        _MeshUniDim2PhyID.push_back(make_pair(dim,phyid));
                        _MeshUniDim2GeoID.push_back(make_pair(dim,geoid));
                    }
                }
            }
        }
    }

    _nBulkElmt=0;
    for(int e=0;e<_nElmts;e++){
        if(_ElmtDimVec[e]==_nMaxDim){
            _nBulkElmt+=1;
        }
    }


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

    // cout<<"MatrixID="<<_MatrixID<<", ParticleID="<<_ParticleID<<endl;

    in.close();
}