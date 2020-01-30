#include "CRVE.h"

void CRVE::PrintInfo(){
    cout<<"*************************************************************************"<<endl;
    cout<<"*** cRVE job information summary:                                     ***"<<endl;
   printf("***   nodes = %9d, elmts = %9d, tol = %14.6e      ***\n",_nNodes,_nElmts,_Tol);
   printf("***   max dim =%2d, min dim = %2d, physical groups = %9d          ***\n",_nMaxDim,_nMinDim,_nPhysics);
   printf("***   xmax= %14.6e, xmin= %14.6e, cx= %14.6e  ***\n",_Xmax,_Xmin,_Cx);
   printf("***   ymax= %14.6e, ymin= %14.6e, cy= %14.6e  ***\n",_Ymax,_Ymin,_Cy);
   printf("***   zmax= %14.6e, zmin= %14.6e, cz= %14.6e  ***\n",_Zmax,_Zmin,_Cz);
   cout<<"***-------------------------------------------------------------------***"<<endl;
   cout<<"***   +Physical ID-------physical dim-----------------physical name+  ***"<<endl;
   for(int i=0;i<_nPhysics;i++){
       printf("***   +%8d             %3d  %32s  +  ***\n",_PhysicID2NameVec[i].first,_PhysicGroupDimVec[i],_PhysicID2NameVec[i].second.c_str());
   }
//    printf("*************************************************************************\n");
   
}