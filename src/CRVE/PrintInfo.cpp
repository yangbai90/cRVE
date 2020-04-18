#include "CRVE.h"

void CRVE::PrintInfo()const{
    cout<<"***-------------------------------------------------------------------***"<<endl;
    printf("*** Elmts=%8d,BulkElmts=%8d,BCElmts=%8d,Nodes=%8d ***\n",_nRVEBCElmts+_nBulkElmt,_nBulkElmt,_nRVEBCElmts,_nNodes);
    printf("*** Physical groups = %5d, min dim = %3d, max dim = %3d             ***\n",static_cast<int>(_RVEPhyGroupNameList.size()),_nMinDim,_nMaxDim);
    printf("*** Physical id <-----> Physical name <-----> Elements <-----> Volume ***\n");
    
    // cout<<"nPhysical ="<<static_cast<int>(_RVEPhyGroupNameList.size())<<endl;
    int phyid,nelmts;
    string phyname;
    double volume;
    for(int i=0;i<static_cast<int>(_RVEPhyID2NameList.size());i++){
        phyid=_RVEPhyID2NameList[i].first;
        phyname=_RVEPhyID2NameList[i].second;
        if(phyid==_MatrixID){
            nelmts=_RVEPhyElmtsNumList[_RVEPhyElmtsNumList.size()-1];
            volume=0.0;
        }
        else if(phyid==_ParticleID){
            nelmts=_RVEPhyElmtsNumList[_RVEPhyElmtsNumList.size()];
            volume=0.0;
        }
        else{
            nelmts=_RVEPhyElmtsNumList[phyid];
            volume=_RVEVolumeList[phyid];
        }
        printf("*** %8d     %16s            %8d      %11.3e***\n",phyid,phyname.c_str(),nelmts,volume);
    }
}