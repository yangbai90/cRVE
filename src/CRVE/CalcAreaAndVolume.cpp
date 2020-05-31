#include "CRVE.h"

void CRVE::CalcAreaAndVolume(){
    _RVEVolumeList.resize(_RVEPhyGroupNameList.size()+1,0.0);
    vector<double> gp2d,gp3d;
    int l1=0,l2=0;

    _nGP=2;
    if(_nGP==2){
        l1=3;
        gp2d.resize(l1*3,0.0);
        gp2d[0*3+1]=2.0/3.0;
        gp2d[0*3+2]=1.0/6.0;
        gp2d[0*3+0]=1.0/3.0;

        gp2d[1*3+1]=1.0/6.0;
        gp2d[1*3+2]=2.0/3.0;
        gp2d[1*3+0]=1.0/3.0;
    
        gp2d[2*3+1]=1.0/6.0;
        gp2d[2*3+2]=1.0/6.0;
        gp2d[2*3+0]=1.0/3.0;

        l2=4;
        gp3d.resize(l2*4,0.0);
        double a=0.585410196624969;
        double b=0.138196601125011;

        gp3d[0*4+1]=a;
        gp3d[0*4+2]=b;
        gp3d[0*4+3]=b;
        gp3d[0*4+0]=1.0/24.0;

        gp3d[1*4+1]=b;
        gp3d[1*4+2]=a;
        gp3d[1*4+3]=b;
        gp3d[1*4+0]=1.0/24.0;
    
        gp3d[2*4+1]=b;
        gp3d[2*4+2]=b;
        gp3d[2*4+3]=a;
        gp3d[2*4+0]=1.0/24.;

        gp3d[3*4+1]=b;
        gp3d[3*4+2]=b;
        gp3d[3*4+3]=b;
        gp3d[3*4+0]=1.0/24.0;
    }
    else if(_nGP==3){
       l1=4;
       gp2d.resize(l1*3,0.0);
       gp2d[0*3+1]=double(1.5505102572168219018027159252941e-01L);
       gp2d[0*3+2]=double(1.7855872826361642311703513337422e-01L);
       gp2d[0*3+0]=double(1.5902069087198858469718450103758e-01L);
       
       gp2d[1*3+1]=double(6.4494897427831780981972840747059e-01L);
       gp2d[1*3+2]=double(7.5031110222608118177475598324603e-02L);
       gp2d[1*3+0]=double(9.0979309128011415302815498962418e-02L);
       
       gp2d[2*3+1]=double(1.5505102572168219018027159252941e-01L);
       gp2d[2*3+2]=double(6.6639024601470138670269327409637e-01L);
       gp2d[2*3+0]=double(1.5902069087198858469718450103758e-01L);
       
       gp2d[3*3+1]=double(6.4494897427831780981972840747059e-01L);
       gp2d[3*3+2]=double(2.8001991549907407200279599420481e-01L);
       gp2d[3*3+0]=double(9.0979309128011415302815498962418e-02L);

       l2=5;
       gp3d.resize(l2*4,0.0);
       gp3d[0*4+1]= 0.25;
       gp3d[0*4+2]= 0.25;
       gp3d[0*4+3]= 0.25;
       gp3d[0*4+0]=-2.0/15;

       gp3d[1*4+1]= 0.5;
       gp3d[1*4+2]= 1.0/6.0;
       gp3d[1*4+3]= 1.0/6.0;
       gp3d[1*4+0]= 0.075;
   
       gp3d[2*4+1]= 1.0/6.0;
       gp3d[2*4+2]= 0.5;
       gp3d[2*4+3]= 1.0/6.0;
       gp3d[2*4+0]= 0.075;

       gp3d[3*4+1]= 1.0/6.0;
       gp3d[3*4+2]= 1.0/6.0;
       gp3d[3*4+3]= 0.5;
       gp3d[3*4+0]= 0.075;

       gp3d[4*4+1]=1.0/6.0;
       gp3d[4*4+2]=1.0/6.0;
       gp3d[4*4+3]=1.0/6.0;
       gp3d[4*4+0]=0.075;
    }
    
    double X[28],Y[28],Z[28];
    int nNodes,phyid,elmttype,e,iInd;
    double xi,eta,zeta,w,volume,detjac;
    for(int e=0;e<static_cast<int>(_RVEElmtConn.size());e++){
        //elm-number elm-type number-of-tags < tag > ... node-number-list
        // out<<iInd<<" "<<_RVEElmtTypeID[i]<<" "<<2<<" ";
        // out<<_RVEElmtPhyID[i]<<" "<<_RVEElmtPhyID[i]<<" ";
        // for(int j=0;j<static_cast<int>(_RVEElmtConn[i].size());j++){
        //     out<<_RVEElmtConn[i][j]<<" ";
        // }
        // out<<"\n";
        elmttype=_RVEElmtTypeID[e];
        phyid=_RVEElmtPhyID[e];
        
        // _RVEPhyElmtsNumList[_RVEElmtPhyID[i]]+=1;
        nNodes=static_cast<int>(_RVEElmtConn[e].size());
        for(int i=0;i<nNodes;i++){
            iInd=_RVEElmtConn[e][i];
            X[i+1]=GetIthNodeJthCoord(iInd,1);
            Y[i+1]=GetIthNodeJthCoord(iInd,2);
            Z[i+1]=GetIthNodeJthCoord(iInd,3);
        }
        volume=0.0;
        for(int gp=0;gp<l1;gp++){
            xi=gp2d[gp*3+1];
            eta=gp2d[gp*3+2];
            w=gp2d[gp*3+0];
            detjac=Shp2d(nNodes,elmttype,xi,eta,X,Y,Z);
            volume+=detjac*w;
        }
        _RVEVolumeList[phyid]+=volume;
        // cout<<"elmt id="<<e<<", phy id="<<phyid<<", volume="<<volume<<endl;
    }

    // Now we do the volume interation for the bulk
    volume=0.0;
    for(int ee=1;ee<=_nBulkElmt;ee++){
        e=ee+_nElmts-_nBulkElmt;
        elmttype=GetIthElmtType(e);
        phyid=GetIthElmtPhyID(e);
        nNodes=_ElmtConn[e-1][0];
        // cout<<"elmttype="<<elmttype<<", phyid="<<phyid
        //     <<", e="<<e<<", matrix id="<<_MatrixID<<", particle id="<<_ParticleID<<endl;
        for(int j=0;j<nNodes;j++){
            iInd=_ElmtConn[e-1][j+1];
            X[j+1]=GetIthNodeJthCoord(iInd,1);
            Y[j+1]=GetIthNodeJthCoord(iInd,2);
            Z[j+1]=GetIthNodeJthCoord(iInd,3);
            // cout<<"\n"<<X[j]<<" "<<Y[j]<<" "<<Z[j]<<endl;
        }

        volume=0.0;
        for(int gp=0;gp<l2;gp++){
            xi=gp3d[gp*4+1];eta=gp3d[gp*4+2];zeta=gp3d[gp*4+3];
            w=gp3d[gp*4+0];
            detjac=Shp3d(nNodes,elmttype,xi,eta,zeta,X,Y,Z);
            // if(e==10000){
            //     cout<<"detjac="<<detjac<<", w="<<w<<endl;
            // }
            // detjac=0.0*zeta;
            volume+=detjac*w;
        }

        if(phyid==_MatrixID){
            _RVEVolumeList[_RVEPhyElmtsNumList.size()-1]+=volume;
        }
        else if(phyid==_ParticleID){
            _RVEVolumeList[_RVEPhyElmtsNumList.size()]+=volume;
        }
    }
}