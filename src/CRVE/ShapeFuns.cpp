#include "CRVE.h"

double CRVE::Shp2d(const int &nNodes,const int &elmttype,const double &xi,const double &eta,const double (&X)[28],const double (&Y)[28],const double (&Z)[28]){
    double detjac=0.0;
    switch (elmttype)
    {
    case 2:
        //3-node triangle.
        _Shp[1][0]=1.0-xi-eta;
        _Shp[1][1]=-1.0;
        _Shp[1][2]=-1.0;

        _Shp[2][0]=xi;
        _Shp[2][1]=1.0;
        _Shp[2][2]=0.0;

        _Shp[3][0]=eta;
        _Shp[3][1]=0.0;
        _Shp[3][2]=1.0;
        break;
    case 3:
        //4-node quadrangle.
        _Shp[1][0]=(1.0-xi)*(1.0-eta)/4.0;
        _Shp[2][0]=(1.0+xi)*(1.0-eta)/4.0;
        _Shp[3][0]=(1.0+xi)*(1.0+eta)/4.0;
        _Shp[4][0]=(1.0-xi)*(1.0+eta)/4.0;

        _Shp[1][1]= (eta-1.0)/4.0;
        _Shp[1][2]= (xi -1.0)/4.0;
        _Shp[2][1]= (1.0-eta)/4.0;
        _Shp[2][2]=-(1.0+xi )/4.0;
        _Shp[3][1]= (1.0+eta)/4.0;
        _Shp[3][2]= (1.0+xi )/4.0;
        _Shp[4][1]=-(1.0+eta)/4.0;
        _Shp[4][2]= (1.0-xi )/4.0;
        break;
    case 9:
        //6-node ]econd order triangle
        _Shp[1][0]= (1.0-xi-eta)*(1.0-2*xi-2*eta);
        _Shp[1][1]=-3.0+4.0*eta+4.0*xi;
        _Shp[1][2]=-3.0+4.0*eta+4.0*xi;
        _Shp[2][0]= xi*(2.0*xi-1.0);
        _Shp[2][1]= 4.0*xi-1.0;
        _Shp[2][2]= 0.0;
        _Shp[3][0]= eta*(2.0*eta-1.0);
        _Shp[3][1]= 0.0;
        _Shp[3][2]= 4.0*eta-1.0;
        _Shp[4][0]= 4.0*xi*(1.0-xi-eta);
        _Shp[4][1]= 4.0*(1.0-eta-2*xi);
        _Shp[4][2]=-4.0*xi;
        _Shp[5][0]= 4.0*xi*eta;
        _Shp[5][1]= 4.0*eta;
        _Shp[5][2]= 4.0*xi;
        _Shp[6][0]= 4.0*eta*(1.0-xi-eta);
        _Shp[6][1]=-4.0*eta;
        _Shp[6][2]= 4.0*(1-2*eta-xi);
        break;
    case 10:
        // 9-node]second order quadrangle
        _Shp[1][0]=(xi*xi-xi )*(eta*eta-eta)/4.0;
        _Shp[2][0]=(xi*xi+xi )*(eta*eta-eta)/4.0;
        _Shp[3][0]=(xi*xi+xi )*(eta*eta+eta)/4.0;
        _Shp[4][0]=(xi*xi-xi )*(eta*eta+eta)/4.0;
        _Shp[5][0]=(1.0-xi*xi)*(eta*eta-eta)/2.0;
        _Shp[6][0]=(xi*xi+xi )*(1.0-eta*eta)/2.0;
        _Shp[7][0]=(1.0-xi*xi)*(eta*eta+eta)/2.0;
        _Shp[8][0]=(xi*xi-xi )*(1.0-eta*eta)/2.0;
        _Shp[9][0]=(1.0-xi*xi)*(1.0-eta*eta);
        _Shp[1][1]=(2.0*xi-1.0)*(eta*eta-eta)/4.0;
        _Shp[1][2]=(xi*xi-xi  )*(2.0*eta-1.0)/4.0;
        _Shp[2][1]=(2.0*xi+1.0)*(eta*eta-eta)/4.0;
        _Shp[2][2]=(xi*xi+xi  )*(2.0*eta-1.0)/4.0;
        _Shp[3][1]=(2.0*xi+1.0)*(eta*eta+eta)/4.0;
        _Shp[3][2]=(xi*xi+xi  )*(2.0*eta+1.0)/4.0;
        _Shp[4][1]=(2.0*xi-1.0)*(eta*eta+eta)/4.0;
        _Shp[4][2]=(xi*xi-xi  )*(2.0*eta+1.0)/4.0;
        _Shp[5][1]=-xi*(eta*eta-eta);
        _Shp[5][2]=(1.0-xi*xi )*(2.0*eta-1.0)/2.0;
        _Shp[6][1]=(2.0*xi+1.0)*(1.0-eta*eta)/2.0;
        _Shp[6][2]=-(xi*xi+xi )*eta;
        _Shp[7][1]=-xi*(eta*eta+eta);
        _Shp[7][2]=(1.0-xi*xi )*(2.0*eta+1.0)/2.0;
        _Shp[8][1]=(2.0*xi-1.0)*(1.0-eta*eta)/2.0;
        _Shp[8][2]=-(xi*xi-xi )*eta;
        _Shp[9][1]=-2.0*xi*(1.0-eta*eta);
        _Shp[9][2]=-2.0*eta*(1.0-xi*xi);
        break;
    case 16:
        // 8-node second order quadrangle
        _Shp[1][0]=(1.0-xi)*(1.0-eta)*(-xi-eta-1.0)/4.0;
        _Shp[2][0]=(1.0+xi)*(1.0-eta)*( xi-eta-1.0)/4.0;
        _Shp[3][0]=(1.0+xi)*(1.0+eta)*( xi+eta-1.0)/4.0;
        _Shp[4][0]=(1.0-xi)*(1.0+eta)*(-xi+eta-1.0)/4.0;
        _Shp[5][0]=(1.0-xi*xi)*(1.0-eta    )/2.0;
        _Shp[6][0]=(1.0+xi   )*(1.0-eta*eta)/2.0;
        _Shp[7][0]=(1.0-xi*xi)*(1.0+eta    )/2.0;
        _Shp[8][0]=(1.0-xi   )*(1.0-eta*eta)/2.0;
        // deriva]ives over xi and eta
        _Shp[1][1]=(1.0-eta)*(2.0*xi+eta)/4.0;
        _Shp[1][2]=(1.0-xi )*(xi+2.0*eta)/4.0;
        _Shp[2][1]=(1.0-eta)*(2.0*xi-eta)/4.0;
        _Shp[2][2]=(1.0+xi )*(2.0*eta-xi)/4.0;
        _Shp[3][1]=(1.0+eta)*(2.0*xi+eta)/4.0;
        _Shp[3][2]=(1.0+xi )*(xi+2.0*eta)/4.0;
        _Shp[4][1]=(1.0+eta)*(2.0*xi-eta)/4.0;
        _Shp[4][2]=(1.0-xi )*(2.0*eta-xi)/4.0;
        _Shp[5][1]=xi*(eta-1.0);
        _Shp[5][2]=(xi*xi-1.0)/2.0;
        _Shp[6][1]=(1.0-eta*eta)/2.0;
        _Shp[6][2]=-(1.0+xi)*eta;
        _Shp[7][1]=-xi*(1.0+eta);
        _Shp[7][2]=(1.0-xi*xi)/2.0;
        _Shp[8][1]=(eta*eta-1.0)/2.0;
        _Shp[8][2]=(xi-1.0)*eta;
        break;
    default:
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: unsupported element type for area calculation          !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }

    _dxdxi=0.0;_dydxi=0.0;_dzdxi=0.0;
    _dxdeta=0.0;_dydeta=0.0;_dzdeta=0.0;
    for(int i=1;i<=nNodes;i++){
        _dxdxi+=_Shp[i][1]*X[i];
        _dydxi+=_Shp[i][1]*Y[i];
        _dzdxi+=_Shp[i][1]*Z[i];

        _dxdeta+=_Shp[i][2]*X[i];
        _dydeta+=_Shp[i][2]*Y[i];
        _dzdeta+=_Shp[i][2]*Z[i];
    }

    detjac=(_dydxi*_dzdeta-_dydeta*_dzdxi)*(_dydxi*_dzdeta-_dydeta*_dzdxi)
           +(_dzdxi*_dxdeta-_dzdeta*_dxdxi)*(_dzdxi*_dxdeta-_dzdeta*_dxdxi)
           +(_dxdxi*_dydeta-_dxdeta*_dydxi)*(_dxdxi*_dydeta-_dxdeta*_dydxi);
    detjac=sqrt(detjac);

    if(detjac<1.0e-15){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: singular element in 2D case                            !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        // abort();
    }

    return detjac;
}

//********************************************
double CRVE::Shp3d(const int &nNodes,const int &elmttype,const double &xi,const double &eta,const double &zeta,const double (&X)[28],const double (&Y)[28],const double (&Z)[28]){
    double detjac=0.0;
    double sqrt2=sqrt(2.0);
    double sqrt3=sqrt(3.0);
    switch (elmttype){
    case 4:
        //4-node tetrahedron.
        _Shp[1][0]= (3.0+8.0*xi-2.0*sqrt2*zeta)/12.0;
        _Shp[1][1]= 8.0/12.0;
        _Shp[1][2]= 0.0;
        _Shp[1][3]=-2.0*sqrt2/12.0;

        _Shp[2][0]= (3.0-4.0*xi-4.0*sqrt3*eta-2.0*sqrt2*zeta)/12.0;
        _Shp[2][1]=-4.0/12.0;
        _Shp[2][2]=-4.0*sqrt3/12.0;
        _Shp[2][3]=-2.0*sqrt2/12.0;

        // _Shp[3][0]= (3.0-4.0*xi+4.0*sqrt3*eta-2.0*sqrt2*zeta)/12.0;
        // _Shp[3][1]=-4.0/12.0;
        // _Shp[3][2]= 4.0*sqrt3/12.0;
        // _Shp[3][3]=-2.0*sqrt2/12.0;

        // _Shp[4][0]= (1.0+2.0*sqrt2*zeta)/4.0;
        // _Shp[4][1]= 0.0;
        // _Shp[4][2]= 0.0;
        // _Shp[4][3]= 2.0*sqrt2/4.0;

        // in order to fit the gmsh order
        _Shp[4][0]= (3.0-4.0*xi+4.0*sqrt3*eta-2.0*sqrt2*zeta)/12.0;
        _Shp[4][1]=-4.0/12.0;
        _Shp[4][2]= 4.0*sqrt3/12.0;
        _Shp[4][3]=-2.0*sqrt2/12.0;

        _Shp[3][0]= (1.0+2.0*sqrt2*zeta)/4.0;
        _Shp[3][1]= 0.0;
        _Shp[3][2]= 0.0;
        _Shp[3][3]= 2.0*sqrt2/4.0;

        break;
    case 5:
        //8-node hexahedron.
        _Shp[1][0] = (1 - xi) * (1 - eta) * (1 - zeta) / 8.0;
        _Shp[1][1] =-(1 - eta) * (1 - zeta) / 8.0;
        _Shp[1][2] =-(1 - xi) * (1 - zeta) / 8.0;
        _Shp[1][3] =-(1 - xi) * (1 - eta) / 8.0;
        _Shp[2][0] = (1 + xi) * (1 - eta) * (1 - zeta) / 8.0;
        _Shp[2][1] = (1 - eta) * (1 - zeta) / 8.0;
        _Shp[2][2] =-(1 + xi) * (1 - zeta) / 8.0;
        _Shp[2][3] =-(1 + xi) * (1 - eta) / 8.0;
        _Shp[3][0] = (1 + xi) * (1 + eta) * (1 - zeta) / 8.0;
        _Shp[3][1] = (1 + eta) * (1 - zeta) / 8.0;
        _Shp[3][2] = (1 + xi) * (1 - zeta) / 8.0;
        _Shp[3][3] =-(1 + xi) * (1 + eta) / 8.0;
        _Shp[4][0] = (1 - xi) * (1 + eta) * (1 - zeta) / 8.0;
        _Shp[4][1] =-(1 + eta) * (1 - zeta) / 8.0;
        _Shp[4][2] = (1 - xi) * (1 - zeta) / 8.0;
        _Shp[4][3] =-(1 - xi) * (1 + eta) / 8.0;
        _Shp[5][0] = (1 - xi) * (1 - eta) * (1 + zeta) / 8.0;
        _Shp[5][1] =-(1 - eta) * (1 + zeta) / 8.0;
        _Shp[5][2] =-(1 - xi) * (1 + zeta) / 8.0;
        _Shp[5][3] = (1 - xi) * (1 - eta) / 8.0;
        _Shp[6][0] = (1 + xi) * (1 - eta) * (1 + zeta) / 8.0;
        _Shp[6][1] = (1 - eta) * (1 + zeta) / 8.0;
        _Shp[6][2] =-(1 + xi) * (1 + zeta) / 8.0;
        _Shp[6][3] = (1 + xi) * (1 - eta) / 8.0;
        _Shp[7][0] = (1 + xi) * (1 + eta) * (1 + zeta) / 8.0;
        _Shp[7][1] = (1 + eta) * (1 + zeta) / 8.0;
        _Shp[7][2] = (1 + xi) * (1 + zeta) / 8.0;
        _Shp[7][3] = (1 + xi) * (1 + eta) / 8.0;
        _Shp[8][0] = (1 - xi) * (1 + eta) * (1 + zeta) / 8.0;
        _Shp[8][1] =-(1 + eta) * (1 + zeta) / 8.0;
        _Shp[8][2] = (1 - xi) * (1 + zeta) / 8.0;
        _Shp[8][3] = (1 - xi) * (1 + eta) / 8.0;
        break;
    // case 11:
    //     //10-node second order tetrahedron
    //     break;
    // case 12:
    //     //27-node second order hexahedron 
    //     break;
    // case 17:
    //     // 20-node second order hexahedron 
    default:
        break;
    }

    _dxdxi=0.0;_dydxi=0.0;_dzdxi=0.0;
    _dxdeta=0.0;_dydeta=0.0;_dzdeta=0.0;
    _dxdzeta=0.0;_dydzeta=0.0;_dzdzeta=0.0;
    for(int i=1;i<=nNodes;i++){
        _dxdxi+=_Shp[i][1]*X[i];
        _dydxi+=_Shp[i][1]*Y[i];
        _dzdxi+=_Shp[i][1]*Z[i];

        _dxdeta+=_Shp[i][2]*X[i];
        _dydeta+=_Shp[i][2]*Y[i];
        _dzdeta+=_Shp[i][2]*Z[i];

        _dxdzeta+=_Shp[i][3]*X[i];
        _dydzeta+=_Shp[i][3]*Y[i];
        _dzdzeta+=_Shp[i][3]*Z[i];
    }
    
    _Jac[0][0]=  _dxdxi;_Jac[0][1]=  _dydxi;_Jac[0][2]=  _dzdxi;
    _Jac[1][0]= _dxdeta;_Jac[1][1]= _dydeta;_Jac[1][2]= _dzdeta;
    _Jac[2][0]=_dxdzeta;_Jac[2][1]=_dydzeta;_Jac[2][2]=_dzdzeta;

    // taken from https://en.wikipedia.org/wiki/Rule_of_Sarrus
    detjac=_Jac[0][0]*_Jac[1][1]*_Jac[2][2]
          +_Jac[0][1]*_Jac[1][2]*_Jac[2][0]
          +_Jac[0][2]*_Jac[1][0]*_Jac[2][1]
          -_Jac[2][0]*_Jac[1][1]*_Jac[0][2]
          -_Jac[2][1]*_Jac[1][2]*_Jac[0][0]
          -_Jac[2][2]*_Jac[1][0]*_Jac[0][1];

    // cout<<_dxdxi<<","<<_dydxi<<","<<_dzdxi<<endl;
    
    if(abs(detjac)<1.0e-15){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: singular element in 3D case                            !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        // abort();
    }

    return detjac;
}