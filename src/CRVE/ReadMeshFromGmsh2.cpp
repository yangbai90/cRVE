#include "CRVE.h"

void CRVE::ReadMeshFromGmsh2(){
    ifstream in;
    in.open(_MeshFileName.c_str(),ios::in);
    while(!in.is_open())
    {
        cout<<"*** Error: can't open geo file(name="<<_MeshFileName<<")!"<<endl;
        cout<<"*** Please enter the correct msh file name:";
        cin>>_MeshFileName;
        in.open(_MeshFileName.c_str(),ios::in);
    }


    _nPhysics=0;
    _PhysicGroupDimVec.clear();
    _PhysicID2NameVec.clear();
    _PhysicName2IDVec.clear();
    _nVolumeElmts=0;
    
    string str;
    double version;
    int format,size;
    while(!in.eof()){
        getline(in,str);

        if(str.find("$MeshFormat")!=string::npos){
            // read the mesh format block
            in>>version>>format>>size;
            if((version!=2.0)&&(version!=2.1)&&(version!=2.2)){
                cout<<"*** Error: version="<<version<<" is not supported!"<<endl;
                abort();
            }
        }
        else if(str.find("$PhysicalNames")!=string::npos){
            // read PhysicalName group information
            _nPhysics=0;
            _PhysicGroupDimVec.clear();
            _PhysicID2NameVec.clear();
            _PhysicName2IDVec.clear();

            

            int phydim,phyid;
            string phyname;
            in>>_nPhysics;
            getline(in,str);//remove \n in this line
            for(int i=0;i<_nPhysics;i++){
                getline(in,str);
                istringstream s_stream(str);
                s_stream>>phydim>>phyid>>phyname;
                // remove the '"' ,keep only the text
                phyname.erase(std::remove(phyname.begin(),phyname.end(),'"'),phyname.end());
                _PhysicGroupDimVec.push_back(phydim);
                _PhysicID2NameVec.push_back(make_pair(phyid,phyname));
                _PhysicName2IDVec.push_back(make_pair(phyname,phyid));
                if(phyname.find("matrix")!=string::npos||phyname.find("MATRIX")!=string::npos){
                    _MatrixPhyID=phyid;
                }
                if(phyname.find("particle")!=string::npos||phyname.find("PARTICLE")!=string::npos){
                    _ParticlePhyID=phyid;
                }
            }
        }
        else if(str.find("$Nodes")!=string::npos){
            // start to read the node block
            _nNodes=0;
            in>>_nNodes;
            
            _NodeCoords.resize(_nNodes*3,0.0);
            int id;
            double x,y,z;

            _Cx=0.0;_Cy=0.0;_Cz=0.0;


            _Xmax=-1.0e16;_Xmin=1.0e16;
            _Ymax=_Xmax;_Ymin=_Xmin;
            _Zmax=_Xmax;_Zmin=_Xmin;
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
            _ElmtTypeVec.resize(_nElmts,0);
            _ElmtDimVec.resize(_nElmts,0);
            _ElmtPhyIDVec.resize(_nElmts,0);
            _ElmtGeoIDVec.resize(_nElmts,0);

            _nVolumeElmts=0;

            long int elmtid;
            int phyid,geoid,ntags,elmttype;
            int nodes,dim;
            _MeshUniGeoID.clear();
            _MeshUniPhyID.clear();
            int tempid;
            for(int ie=0;ie<_nElmts;ie++){
                in>>elmtid>>elmttype>>ntags>>phyid>>geoid;
                nodes=GetNodesNumViaElmtType(elmttype);
                dim=GetElmtDimViaElmtType(elmttype);

                if(dim>_nMaxDim) _nMaxDim=dim;
                if(dim<_nMinDim) _nMinDim=dim;

                _ElmtConn[elmtid-1].resize(nodes+1,0);
                _ElmtConn[elmtid-1][0]=nodes;
                for(int j=0;j<nodes;j++){
                    in>>_ElmtConn[elmtid-1][j+1];
                }
                if(dim==3&&nodes==4){
                    // for tet 4 mesh
                    tempid=_ElmtConn[elmtid-1][3];
                    _ElmtConn[elmtid-1][3]=_ElmtConn[elmtid-1][4];
                    _ElmtConn[elmtid-1][4]=tempid;
                }

                if(dim==3){
                    _nVolumeElmts+=1;
                }
               
                _ElmtDimVec[elmtid-1]=dim;
                _ElmtTypeVec[elmtid-1]=elmttype;
                _ElmtPhyIDVec[elmtid-1]=phyid;
                _ElmtGeoIDVec[elmtid-1]=geoid;

                if(_MeshUniGeoID.size()==0){
                    _MeshUniGeoID.push_back(geoid);
                    _MeshUniPhyID.push_back(phyid);
                }
                else{
                    bool IsUni=true;
                    for(unsigned int i=0;i<_MeshUniGeoID.size();i++){
                        if(geoid==_MeshUniGeoID[i]||phyid==_MeshUniPhyID[i]){
                            IsUni=false;
                            break;
                        }
                    }
                    if(IsUni){
                        _MeshUniGeoID.push_back(geoid);
                        _MeshUniPhyID.push_back(phyid);
                    }
                }
            }
        }
    }// while read file loop
    in.close();


    if(!_IsParticleIDSet){
        if(_MeshUniPhyID.size()>=2){
            _ParticlePhyID=_MeshUniPhyID[_MeshUniPhyID.size()-1];
        }
        else{
            _ParticlePhyID=50000;
        }
    }
    else{
        // we need to check the physical id given by user is valid or not
        bool IsValid;
        IsValid=false;
        for(auto it:_MeshUniPhyID){
            if(it==_ParticlePhyID){
                IsValid=true;
                break;
            }
        }
        if(!IsValid){
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: invalid physical id for particle given by user !!!         ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
    }

    if(!_IsMatrixIDSet){
        if(_MeshUniPhyID.size()>=2){
            _MatrixPhyID=_MeshUniPhyID[_MeshUniPhyID.size()-2];
        }
        else{
            _MatrixPhyID=50000-1;
        }
    }
    else{
        bool IsValid;
        IsValid=false;
        for(auto it:_MeshUniPhyID){
            if(it==_MatrixPhyID){
                IsValid=true;
                break;
            }
        }
        if(!IsValid){
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: invalid physical id for matrix given by user !!!           ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
    }

    // if(_MeshUniPhyID.size()==2){
    //     _MatrixPhyID=_MeshUniPhyID[0];
    //     _ParticlePhyID=_MeshUniPhyID[1];
    // }
    // else if(_MeshUniPhyID.size()>2){
    //     // for multiple fibers case
    //     _MatrixPhyID=-1;
    //     _ParticlePhyID=1;
    // }
}