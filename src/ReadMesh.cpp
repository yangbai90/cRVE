#include "GmshIO.h"


bool GmshIO::ReadMeshFile()
{
    ifstream in;
    in.open(_GeoFileName.c_str(),ios::in);
    while(!in.is_open())
    {
        cout<<"*** Error: can't open geo file(name="<<_GeoFileName<<")!"<<endl;
        cout<<"*** Please enter the correct msh file name:";
        cin>>_GeoFileName;
        in.open(_GeoFileName.c_str(),ios::in);
    }
    
    string str;
    double version;
    int format,size;
    while(!in.eof())
    {
        getline(in,str);

        if(str.find("$MeshFormat")!=string::npos)
        {
            // read the mesh format block
            in>>version>>format>>size;
            if((version!=2.0)&&(version!=2.1)&&(version!=2.2))
            {
                cout<<"*** Error: version="<<version<<" is not supported!"<<endl;
                return false;
            }
        }
        else if(str.find("$PhysicalNames")!=string::npos)
        {
            // read PhysicalName group information
            _nPhyGroupNum=0;
            _PhyGroupDimVec.clear();
            _PhyGroupArray.clear();

            int phydim,phyid;
            string phyname;
            in>>_nPhyGroupNum;
            getline(in,str);//remove \n in this line
            for(int i=0;i<_nPhyGroupNum;i++)
            {
                getline(in,str);
                istringstream s_stream(str);
                s_stream>>phydim>>phyid>>phyname;
                // remove the '"' ,keep only the text
                phyname.erase(std::remove(phyname.begin(),phyname.end(),'"'),phyname.end());
                _PhyGroupDimVec.push_back(phydim);
                _PhyGroupArray.push_back(make_pair(phyid,phyname));
            }
        }
        else if(str.find("$Nodes")!=string::npos)
        {
            // start to read the node block
            _nNodes=0;
            in>>_nNodes;
            _NodeCoords.resize(_nNodes*3,0.0);
            long int id;
            double x,y,z;
            for(long int i=0;i<_nNodes;i++)
            {
                in>>id>>x>>y>>z;
                _NodeCoords[(id-1)*3+1-1]=x;
                _NodeCoords[(id-1)*3+2-1]=y;
                _NodeCoords[(id-1)*3+3-1]=z;
            }
            getline(in,str);
        }
        else if(str.find("$Elements")!=string::npos)
        {
            _nElmts=0;
            in>>_nElmts;
            _ElmtConn.resize(_nElmts,vector<int>(0));
            
            _ElmtDimVec.resize(_nElmts,0);
            _ElmtTypeVec.resize(_nElmts,0);
            _ElmtPhyIDVec.resize(_nElmts,0);
            _ElmtGeoIDVec.resize(_nElmts,0);

            long int elmtid;
            int phyid,geoid,ntags,elmttype;
            int nodes,dim;
            for(long int ie=0;ie<_nElmts;ie++)
            {
                in>>elmtid>>elmttype>>ntags>>phyid>>geoid;
                nodes=GetNodesNumViaElmtType(elmttype);
                dim=GetElmtDimViaElmtType(elmttype);
                _ElmtConn[elmtid-1].resize(nodes+1,0);
                _ElmtConn[elmtid-1][0]=nodes;
                for(int j=0;j<nodes;j++)
                {
                    in>>_ElmtConn[elmtid-1][j+1];
                }
                _ElmtDimVec[elmtid-1]=dim;
                _ElmtTypeVec[elmtid-1]=elmttype;
                _ElmtPhyIDVec[elmtid-1]=phyid;
                _ElmtGeoIDVec[elmtid-1]=geoid;

            }

        }
    }// while read file loop
    return true;
}
