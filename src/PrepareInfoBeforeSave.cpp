#include "GmshIO.h"

void GmshIO::SaveLabledMesh()
{
    vector<int> newphyid,newphydim;
    vector<string> newphyname;

    newphyid.clear();
    newphydim.clear();
    newphyname.clear();
    //int nPhyIDofMesh=_MeshUniPhyID.size();

    // no any geo information in *.msh file
    int nSurfaceElmts=0;
    if(_XminElConn.size()!=0)
    {
        newphyid.push_back(1);
        newphyname.push_back("left");
        newphydim.push_back(2);
        nSurfaceElmts+=_XminElConn.size();
    }
    if(_XmaxElConn.size()!=0)
    {
        newphyid.push_back(4);
        newphyname.push_back("right");
        newphydim.push_back(2);
        nSurfaceElmts+=_XmaxElConn.size();
    }
    //************************************
    if(_YminElConn.size()!=0)
    {
        newphyid.push_back(2);
        newphyname.push_back("bottom");
        newphydim.push_back(2);
        nSurfaceElmts+=_YminElConn.size();
    }
    if(_YmaxElConn.size()!=0)
    {
        newphyid.push_back(5);
        newphyname.push_back("top");
        newphydim.push_back(2);
        nSurfaceElmts+=_YmaxElConn.size();
    }
    //************************************
    if(_ZminElConn.size()!=0)
    {
        newphyid.push_back(3);
        newphyname.push_back("back");
        newphydim.push_back(2);
        nSurfaceElmts+=_ZminElConn.size();
    }
    if(_ZmaxElconn.size()!=0)
    {
        newphyid.push_back(6);
        newphyname.push_back("front");
        newphydim.push_back(2);
        nSurfaceElmts+=_ZmaxElconn.size();
    }
    int nVolumePhyIDStart=newphyid.size();
    for(int i=1;i<=int(_MeshUniPhyID.size());i++)
    {
        newphyid.push_back(nVolumePhyIDStart+i);
        newphyname.push_back("volume"+to_string(_MeshUniPhyID[i-1]));
        newphydim.push_back(3);
    }

    if(_PhyGroupArray.size()==0)
    {
        
    }

    ofstream out;
    out.open(_NewGeoFileName.c_str(),ios::out);
    if(!out.is_open())
    {
        cout<<"*** Error: can't write information to"<<_NewGeoFileName<<" !!!"<<endl;
        abort();
    }

    // start to write new geo file
    out<<"$MeshFormat"<<endl;
    out<<"2.2 0 8"<<endl;
    out<<"$EndMeshFormat"<<endl;

    // write out physical information
    out<<"$PhysicalNames"<<endl;
    out<<newphyname.size()<<endl;
    for(int i=0;i<int(newphyid.size());i++)
    {
        out<<newphydim[i]<<" "<<newphyid[i]<<" \""<<newphyname[i]<<"\""<<endl;
    }
    out<<"$EndPhysicalNames"<<endl;

    // write out nodes
    out<<"$Nodes"<<endl;
    out<<_nNodes<<endl;
    for(long int i=1;i<=_nNodes;i++)
    {
        out<<i<<" ";
        out<<GetIthNodeJthCoord(i,1)<<" ";
        out<<GetIthNodeJthCoord(i,2)<<" ";
        out<<GetIthNodeJthCoord(i,3)<<endl;
    }
    out<<"$EndNodes"<<endl;

    // write out elements
    out<<"$Elements"<<endl;
    out<<_nElmts+nSurfaceElmts<<endl;
    long int iInd=0;
    //*********************************
    for(size_t i=0;i<_XminElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<1<<" "<<1<<" ";
        for(size_t j=0;j<_XminElConn[i].size();j++)
        {
            out<<_XminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(size_t i=0;i<_XmaxElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<4<<" "<<4<<" ";
        for(size_t j=0;j<_XmaxElConn[i].size();j++)
        {
            out<<_XmaxElConn[i][j]<<" ";
        }
        out<<endl;
    }
    //*********************************
    for(size_t i=0;i<_YminElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<2<<" "<<2<<" ";
        for(size_t j=0;j<_YminElConn[i].size();j++)
        {
            out<<_YminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(size_t i=0;i<_YmaxElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<5<<" "<<5<<" ";
        for(size_t j=0;j<_YmaxElConn[i].size();j++)
        {
            out<<_YmaxElConn[i][j]<<" ";
        }
        out<<endl;
    }
    //***********************************
    for(size_t i=0;i<_ZminElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<3<<" "<<3<<" ";
        for(size_t j=0;j<_ZminElConn[i].size();j++)
        {
            out<<_ZminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(size_t i=0;i<_ZmaxElconn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<2<<" "<<2<<" ";
        out<<6<<" "<<6<<" ";
        for(size_t j=0;j<_ZmaxElconn[i].size();j++)
        {
            out<<_ZmaxElconn[i][j]<<" ";
        }
        out<<endl;
    }
    // new write out the volume mesh
    for(long int i=1;i<=_nElmts;i++)
    {
        iInd+=1;
        out<<iInd<<" "<<4<<" "<<2<<" ";
        out<<nVolumePhyIDStart+_ElmtPhyIDVec[i-1]<<" "
           <<nVolumePhyIDStart+_ElmtPhyIDVec[i-1]<<" ";
        
        for(int j=0;j<_ElmtConn[i-1][0];j++)
        {
            out<<_ElmtConn[i-1][1+j]<<" ";
        }
        out<<endl;
    }
    out<<"$EndElements"<<endl;

}