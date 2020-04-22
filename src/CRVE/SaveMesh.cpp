#include "CRVE.h"

void CRVE::SaveMesh(){
    ofstream out;
    string filename="new_"+_InputMeshFileName;
    _OutputMeshFileName=filename;
    out.open(filename.c_str(),ios::out);

    out<<"$MeshFormat\n";
    out<<"2.2 0 8\n";
    out<<"$EndMeshFormat\n";

    // write out physical information
    out<<"$PhysicalNames\n";
    out<<_RVEPhyGroupNameList.size()<<"\n";
    for(int i=0;i<static_cast<int>(_RVEPhyGroupNameList.size());i++){
        out<<_RVEPhyDimVec[i]<<" "
           <<_RVEPhyID2NameList[i].first<<" "
           <<"\""<<_RVEPhyID2NameList[i].second<<"\""<<"\n"; 
    }

    // write out nodes
    out<<"$Nodes\n";
    out<<_nNodes<<"\n";
    for(int i=1;i<=_nNodes;i++){
        out<<i<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,1)<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,2)<<" ";
        out<<scientific<<setprecision(6)<<GetIthNodeJthCoord(i,3)<<"\n";
    }
    out<<"$EndNodes\n";

    //*******************************************************
    // write out elements
    out<<"$Elements\n";
    out<<_nRVEBCElmts+_nBulkElmt<<"\n";
    int iInd=0;
    //*********************************
    //*** elm-number elm-type number-of-tags < tag > ... node-number-list
    for(auto &it:_RVEPhyElmtsNumList) it=0;
    for(int i=0;i<static_cast<int>(_RVEElmtConn.size());i++){
        iInd+=1;
        //elm-number elm-type number-of-tags < tag > ... node-number-list
        out<<iInd<<" "<<_RVEElmtTypeID[i]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[i]<<" "<<_RVEElmtPhyID[i]<<" ";
        for(int j=0;j<static_cast<int>(_RVEElmtConn[i].size());j++){
            out<<_RVEElmtConn[i][j]<<" ";
            // out<<_NodeRealIndex[_RVEElmtConn[i][j]-1]<<" ";
        }
        out<<"\n";
        
        _RVEPhyElmtsNumList[_RVEElmtPhyID[i]]+=1;
        
    }
    //*******************************************************
    int e,ei;
    for(int ee=1;ee<=_nBulkElmt;ee++){
        e=ee+_nElmts-_nBulkElmt;
        ei=iInd+ee;
        out<<ei<<" "<<GetIthElmtType(e)<<" "<<2<<" ";
        out<<GetIthElmtPhyID(e)<<" "<<GetIthElmtPhyID(e)<<" ";
        for(int j=0;j<_ElmtConn[e-1][0];j++){
            out<<_ElmtConn[e-1][j+1]<<" ";
            // out<<_NodeRealIndex[_ElmtConn[e-1][j+1]-1]<<endl;
        }
        out<<"\n";
        if(GetIthElmtPhyID(e)==_MatrixID){
            _RVEPhyElmtsNumList[_RVEPhyElmtsNumList.size()-1]+=1;
        }
        else if(GetIthElmtPhyID(e)==_ParticleID){
            _RVEPhyElmtsNumList[_RVEPhyElmtsNumList.size()  ]+=1;
        }
    }
    out<<"$EndElements"<<endl;


    out.close();
}