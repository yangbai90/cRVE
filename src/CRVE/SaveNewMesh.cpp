#include "CRVE.h"

void CRVE::SaveNewMesh(){
    ofstream out;
    out.open(_NewMeshFileName.c_str(),ios::out);
    if(!out.is_open())
    {
        cout<<"*** Error: can't write information to"<<_NewMeshFileName<<" !!!"<<endl;
        abort();
    }

    

    // start to write new geo file
    out<<"$MeshFormat\n";
    out<<"2.2 0 8\n";
    out<<"$EndMeshFormat\n";

    // write out physical information
    out<<"$PhysicalNames\n";
    out<<_nPhysics<<"\n";
    for(int i=0;i<_nPhysics;i++){
        if(_PhysicGroupDimVec[i]==0){
            out<<_PhysicGroupDimVec[i]<<" "<<_PhysicID2NameVec[i].first
               <<" \""<<_PhysicID2NameVec[i].second<<"\""<<"\n";
        }
    }
    for(int i=0;i<_nPhysics;i++){
        if(_PhysicGroupDimVec[i]==1){
            out<<_PhysicGroupDimVec[i]<<" "<<_PhysicID2NameVec[i].first
               <<" \""<<_PhysicID2NameVec[i].second<<"\""<<"\n";
        }
    }
    for(int i=0;i<_nPhysics;i++){
        if(_PhysicGroupDimVec[i]==2){
            out<<_PhysicGroupDimVec[i]<<" "<<_PhysicID2NameVec[i].first
               <<" \""<<_PhysicID2NameVec[i].second<<"\""<<"\n";
        }
    }
    for(int i=0;i<_nPhysics;i++){
        if(_PhysicGroupDimVec[i]==3){
            out<<_PhysicGroupDimVec[i]<<" "<<_PhysicID2NameVec[i].first
               <<" \""<<_PhysicID2NameVec[i].second<<"\""<<"\n";
        }
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

    //***********************************
    //*** write out elements
    //***********************************
    int nSurfaceElmts;
    nSurfaceElmts=_XminElConn.size()+_XmaxElConn.size()
                 +_YminElConn.size()+_YmaxElConn.size()
                 +_ZminElConn.size()+_ZmaxElConn.size();
    
    out<<"$Elements\n";
    out<<_nVolumeElmts+nSurfaceElmts<<"\n";
    long int iInd=0;
    //*********************************
    //*** elm-number elm-type number-of-tags < tag > ... node-number-list
    for(int i=0;i<int(_XminElConn.size());i++){
        iInd+=1;
        //elm-number elm-type number-of-tags < tag > ... node-number-list
        out<<iInd<<" "<<_XminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_XminElmtPhyID[i]<<" "<<_XminElmtPhyID[i]<<" ";
        for(int j=0;j<int(_XminElConn[i].size());j++)
        {
            out<<_XminElConn[i][j]<<" ";
        }
        out<<"\n";
    }
    for(int i=0;i<int(_XmaxElConn.size());i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_XmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_XmaxElmtPhyID[i]<<" "<<_XmaxElmtPhyID[i]<<" ";
        for(int j=0;j<int(_XmaxElConn[i].size());j++)
        {
            out<<_XmaxElConn[i][j]<<" ";
        }
        out<<endl;
    }
    //*********************************
    for(int i=0;i<int(_YminElConn.size());i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_YminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_YminElmtPhyID[i]<<" "<<_YminElmtPhyID[i]<<" ";
        for(int j=0;j<int(_YminElConn[i].size());j++)
        {
            out<<_YminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(int i=0;i<int(_YmaxElConn.size());i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_YmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_YmaxElmtPhyID[i]<<" "<<_YmaxElmtPhyID[i]<<" ";
        for(int j=0;j<int(_YmaxElConn[i].size());j++)
        {
            out<<_YmaxElConn[i][j]<<" ";
        }
        out<<endl;
    }
    //***********************************
    for(int i=0;i<int(_ZminElConn.size());i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_ZminElmtTypeVec[i]<<" "<<2<<" ";
        out<<_ZminElmtPyhID[i]<<" "<<_ZminElmtPyhID[i]<<" ";
        for(int j=0;j<int(_ZminElConn[i].size());j++)
        {
            out<<_ZminElConn[i][j]<<" ";
        }
        out<<endl;
    }
    for(int i=0;i<int(_ZmaxElConn.size());i++)
    {
        iInd+=1;
        out<<iInd<<" "<<_ZmaxElmtTypeVec[i]<<" "<<2<<" ";
        out<<_ZMaxElmtPhyID[i]<<" "<<_ZMaxElmtPhyID[i]<<" ";
        for(int j=0;j<int(_ZmaxElConn[i].size());j++)
        {
            out<<_ZmaxElConn[i][j]<<" ";
        }
        out<<endl;
    }
    // now write out the volume mesh
    for(int i=1;i<=_nElmts;i++)
    {
        if(_ElmtDimVec[i-1]==3){
            iInd+=1;
            out<<iInd<<" "<<4<<" "<<2<<" ";
            out<<_ElmtPhyIDVec[i-1]<<" "
               <<_ElmtPhyIDVec[i-1]<<" ";
        
            for(int j=0;j<_ElmtConn[i-1][0];j++)
            {
                out<<_ElmtConn[i-1][1+j]<<" ";
            }
            out<<endl;
        }
    }
    out<<"$EndElements"<<endl;

    cout<<"*************************************************************************"<<endl;
   printf("*** Job finished, write new mesh to %30s   ***\n",_NewMeshFileName.c_str());
    cout<<"*************************************************************************"<<endl;
}