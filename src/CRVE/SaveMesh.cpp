#include "CRVE.h"

void CRVE::SaveMesh(){
    ofstream out;
    string filename="new_"+_InputMeshFileName;
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
    for(int i=0;i<static_cast<int>(_Left.size());i++){
        iInd+=1;
        //elm-number elm-type number-of-tags < tag > ... node-number-list
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[iInd-1]<<" "<<_RVEElmtPhyID[iInd-1]<<" ";
        for(int j=0;j<static_cast<int>(_Left[i].size());j++){
            out<<_Left[i][j]<<" ";
        }
        out<<"\n";
    }
    for(int i=0;i<static_cast<int>(_Right.size());i++){
        iInd+=1;
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[iInd-1]<<" "<<_RVEElmtPhyID[iInd-1]<<" ";
        for(int j=0;j<static_cast<int>(_Right[i].size());j++){
            out<<_Right[i][j]<<" ";
        }
        out<<"\n";
    }
    //*********************************
    for(int i=0;i<static_cast<int>(_Bottom.size());i++){
        iInd+=1;
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[iInd-1]<<" "<<_RVEElmtPhyID[iInd-1]<<" ";
        for(int j=0;j<static_cast<int>(_Bottom[i].size());j++){
            out<<_Bottom[i][j]<<" ";
        }
        out<<"\n";
    }
    for(int i=0;i<static_cast<int>(_Top.size());i++){
        iInd+=1;
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[iInd-1]<<" "<<_RVEElmtPhyID[iInd-1]<<" ";
        for(int j=0;j<static_cast<int>(_Top[i].size());j++){
            out<<_Top[i][j]<<" ";
        }
        out<<"\n";
    }
    //***********************************
    for(int i=0;i<static_cast<int>(_Back.size());i++){
        iInd+=1;
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[i]<<" "<<_RVEElmtPhyID[i]<<" ";
        for(int j=0;j<static_cast<int>(_Back[i].size());j++){
            out<<_Back[i][j]<<" ";
        }
        out<<"\n";
    }
    for(int i=0;i<static_cast<int>(_Front.size());i++){
        iInd+=1;
        out<<iInd<<" "<<_RVEElmtTypeID[iInd-1]<<" "<<2<<" ";
        out<<_RVEElmtPhyID[i]<<" "<<_RVEElmtPhyID[i]<<" ";
        for(int j=0;j<static_cast<int>(_Front[i].size());j++){
            out<<_Front[i][j]<<" ";
        }
        out<<"\n";
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
        }
        out<<"\n";
    }
    out<<"$EndElements"<<endl;


    out.close();
}