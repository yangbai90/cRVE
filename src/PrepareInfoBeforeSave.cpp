#include "GmshIO.h"

void GmshIO::SaveLabledMesh()
{

    newphyid.clear();
    newphydim.clear();
    newphyname.clear();
    //int nPhyIDofMesh=_MeshUniPhyID.size();

    // no any geo information in *.msh file
    int nSurfaceElmts=0;
    if(_XminElConn.size()!=0)
    {
        if(_IsSplitMatrixAndParticle){
            newphyid.push_back(1);
            newphyname.push_back("mleft");
            newphydim.push_back(2);

            newphyid.push_back(2);
            newphyname.push_back("pleft");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(1);
            newphyname.push_back("mleft");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(1);
            newphyname.push_back("pleft");
            newphydim.push_back(2);
        }
        nSurfaceElmts+=_XminElConn.size();
    }
    if(_XmaxElConn.size()!=0)
    {
        if(_IsSplitMatrixAndParticle){
            newphyid.push_back(3);
            newphyname.push_back("mright");
            newphydim.push_back(2);

            newphyid.push_back(4);
            newphyname.push_back("pright");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(2);
            newphyname.push_back("mright");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(2);
            newphyname.push_back("pright");
            newphydim.push_back(2);
        }
        nSurfaceElmts+=_XmaxElConn.size();
    }
    //************************************
    if(_YminElConn.size()!=0)
    {
        if(_IsSplitMatrixAndParticle){
            newphyid.push_back(5);
            newphyname.push_back("mbottom");
            newphydim.push_back(2);

            newphyid.push_back(6);
            newphyname.push_back("pbottom");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(3);
            newphyname.push_back("mbottom");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(3);
            newphyname.push_back("pbottom");
            newphydim.push_back(2);
        }
        nSurfaceElmts+=_YminElConn.size();
    }
    if(_YmaxElConn.size()!=0)
    {
       if(_IsSplitMatrixAndParticle){
            newphyid.push_back(7);
            newphyname.push_back("mtop");
            newphydim.push_back(2);

            newphyid.push_back(8);
            newphyname.push_back("ptop");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(4);
            newphyname.push_back("mtop");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(4);
            newphyname.push_back("ptop");
            newphydim.push_back(2);
        }
        nSurfaceElmts+=_YmaxElConn.size();
    }
    //************************************
    if(_ZminElConn.size()!=0)
    {
        if(_IsSplitMatrixAndParticle){
            newphyid.push_back(9);
            newphyname.push_back("mback");
            newphydim.push_back(2);

            newphyid.push_back(10);
            newphyname.push_back("pback");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(5);
            newphyname.push_back("mback");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(5);
            newphyname.push_back("pback");
            newphydim.push_back(2);
        }
        nSurfaceElmts+=_ZminElConn.size();
    }
    if(_ZmaxElconn.size()!=0)
    {
        if(_IsSplitMatrixAndParticle){
            newphyid.push_back(11);
            newphyname.push_back("mfront");
            newphydim.push_back(2);

            newphyid.push_back(12);
            newphyname.push_back("pfront");
            newphydim.push_back(2);
        }
        else if(_IsSplitMatrixOnly){
            newphyid.push_back(6);
            newphyname.push_back("mfront");
            newphydim.push_back(2);
        }
        else if(_IsSplitParticleOnly){
            newphyid.push_back(6);
            newphyname.push_back("pfront");
            newphydim.push_back(2);
        }
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
    out<<"$MeshFormat\n";
    out<<"2.2 0 8\n";
    out<<"$EndMeshFormat\n";

    // write out physical information
    out<<"$PhysicalNames\n";
    out<<newphyname.size()<<"\n";
    for(int i=0;i<int(newphyid.size());i++)
    {
        out<<newphydim[i]<<" "<<newphyid[i]<<" \""<<newphyname[i]<<"\""<<"\n";
    }
    out<<"$EndPhysicalNames\n";

    // write out nodes
    out<<"$Nodes\n";
    out<<_nNodes<<"\n";
    for(long int i=1;i<=_nNodes;i++)
    {
        out<<i<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,1)<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,2)<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,3)<<"\n";
    }
    out<<"$EndNodes\n";

    // write out elements
    out<<"$Elements\n";
    out<<_nElmts+nSurfaceElmts<<"\n";
    long int iInd=0;
    //*********************************
    //*** elm-number elm-type number-of-tags < tag > ... node-number-list
    for(size_t i=0;i<_XminElConn.size();i++)
    {
        iInd+=1;
        //elm-number elm-type number-of-tags < tag > ... node-number-list
        out<<iInd<<" "<<_XminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_XminElmtPhyID[i]<<" "<<_XminElmtPhyID[i]<<" ";
        for(size_t j=0;j<_XminElConn[i].size();j++)
        {
            out<<_XminElConn[i][j]<<" ";
        }
        out<<"\n";
    }
    for(size_t i=0;i<_XmaxElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_XmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_XmaxElmtPhyID[i]<<" "<<_XmaxElmtPhyID[i]<<" ";
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
        out<<iInd<<" "<<_YminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_YminElmtPhyID[i]<<" "<<_YminElmtPhyID[i]<<" ";
        for(size_t j=0;j<_YminElConn[i].size();j++)
        {
            out<<_YminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(size_t i=0;i<_YmaxElConn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_YmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_YmaxElmtPhyID[i]<<" "<<_YmaxElmtPhyID[i]<<" ";
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
        out<<iInd<<" "<<_ZminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_ZminElmtPyhID[i]<<" "<<_ZminElmtPyhID[i]<<" ";
        for(size_t j=0;j<_ZminElConn[i].size();j++)
        {
            out<<_ZminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(size_t i=0;i<_ZmaxElconn.size();i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_ZmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_ZMaxElmtPhyID[i]<<" "<<_ZMaxElmtPhyID[i]<<" ";
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