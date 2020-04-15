#include "CRVE.h"

double CRVE::GetGmshFileFormatVersion()const{
    ifstream in;
    string str;
    double version=2.1;
    int format,size;
    in.open(_InputMeshFileName.c_str(),ios::in);
    while(!in.eof()){
        getline(in,str);
        if(str.find("$MeshFormat")!=string::npos){
            // read the mesh format block
            in>>version>>format>>size;
            break;
        }
    }
    in.close();
    return version;
}
//*************************************************************************
int CRVE::GetElmtDimViaGmshElmtType(const int &elmttype)const{
    switch (elmttype){
    case 1:
        // 2-node line
        return 1;
    case 2:
        //3-node triangle.
        return 2;
    case 3:
        //4-node quadrangle.
        return 2;
    case 4:
        // 4-node tetrahedron.
        return 3;
    case 5:
        // 8-node hexahedron.
        return 3;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return 1;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return 2;
    case 10:
        // 9-node second order quadrangle 
        return 2;
    case 11:
        // 10-node second order tetrahedron
        return 3;
    case 12:
        // 27-node second order hexahedron
        return 3;
    case 15:
        // 1-node point
        return 0;
    case 16:
        // 8-node second order quadrangle 
        return 2;
    case 17:
        // 20-node second order hexahedron
        return 3;
    default:
        return -1;
    }
}

//*************************************************************************
int CRVE::GetElmtSubDimViaGmshElmtType(const int &elmttype)const{
    switch (elmttype){
    case 1:
        // 2-node line
        return 1-1;
    case 2:
        //3-node triangle.
        return 2-1;
    case 3:
        //4-node quadrangle.
        return 2-1;
    case 4:
        // 4-node tetrahedron.
        return 3-1;
    case 5:
        // 8-node hexahedron.
        return 3-1;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return 1-1;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return 2-1;
    case 10:
        // 9-node second order quadrangle 
        return 2-1;
    case 11:
        // 10-node second order tetrahedron
        return 3-1;
    case 12:
        // 27-node second order hexahedron
        return 3-1;
    case 15:
        // 1-node point
        return 0-1;
    case 16:
        // 8-node second order quadrangle 
        return 2-1;
    case 17:
        // 20-node second order hexahedron
        return 3-1;
    default:
        return -1-1;
    }
}

//*************************************************************************
int CRVE::GetElmtNodesNumViaGmshElmtType(const int &elmttype)const{
    switch (elmttype){
    case 1:
        // 2-node line
        return 2;
    case 2:
        //3-node triangle.
        return 3;
    case 3:
        //4-node quadrangle.
        return 4;
    case 4:
        // 4-node tetrahedron.
        return 4;
    case 5:
        // 8-node hexahedron.
        return 8;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return 3;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return 6;
    case 10:
        // 9-node second order quadrangle 
        return 9;
    case 11:
        // 10-node second order tetrahedron
        return 10;
    case 12:
        // 27-node second order hexahedron
        return 27;
    case 15:
        // 1-node point
        return 1;
    case 16:
        // 8-node second order quadrangle 
        return 8;
    case 17:
        // 20-node second order hexahedron
        return 20;
    default:
        return -1;
    }
}
//********************************************
int CRVE::GetSubElmtTypeViaGmshElmtType(const int &elmttype)const{
    switch (elmttype){
    case 1:
        // 2-node line
        return 15;
    case 2:
        //3-node triangle.
        return 1;
    case 3:
        //4-node quadrangle.
        return 1;
    case 4:
        // 4-node tetrahedron.
        return 2;
    case 5:
        // 8-node hexahedron.
        return 3;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return 15;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return 8;
    case 10:
        // 9-node second order quadrangle 
        return 8;
    case 11:
        // 10-node second order tetrahedron
        return 9;
    case 12:
        // 27-node second order hexahedron
        return 10;
    case 15:
        // 1-node point
        return -1;
    case 16:
        // 8-node second order quadrangle 
        return 8;
    case 17:
        // 20-node second order hexahedron
        return 16;
    default:
        return -1;
    }
}
//********************************************
int CRVE::GetSurfaceNumsViaGmshElmtType(const int &elmttype)const{
    switch (elmttype){
    case 1:
        // 2-node line
        return -1;
    case 2:
        //3-node triangle.
        return -1;
    case 3:
        //4-node quadrangle.
        return -1;
    case 4:
        // 4-node tetrahedron.
        return 4;
    case 5:
        // 8-node hexahedron.
        return 6;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return -1;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return -1;
    case 10:
        // 9-node second order quadrangle 
        return -1;
    case 11:
        // 10-node second order tetrahedron
        return 4;
    case 12:
        // 27-node second order hexahedron
        return 6;
    case 15:
        // 1-node point
        return -1;
    case 16:
        // 8-node second order quadrangle 
        return -1;
    case 17:
        // 20-node second order hexahedron
        return 6;
    default:
        return -1;
    }
}
//***************************************************************
vector<int> CRVE::GetIthElmtJthSurfaceNodeIndex(const int &elmttype,const int &i,const int &j)const{
    vector<int> conn,elConn;
    conn.clear();
    switch (elmttype){
    case 1:
        // 2-node line
        return conn;
    case 2:
        //3-node triangle.
        return conn;
    case 3:
        //4-node quadrangle.
        return conn;
    case 4:
        // 4-node tetrahedron.
        // 4-node tetrahedron
        elConn=GetIthElmtConn(i);
        conn.resize(3,0);
        if(j==1){
            conn[0]=elConn[0];conn[1]=elConn[2];conn[2]=elConn[1];
        }
        else if(j==2){
            conn[0]=elConn[0];conn[1]=elConn[3];conn[2]=elConn[2];
        }
        else if(j==3){
            conn[0]=elConn[3];conn[1]=elConn[1];conn[2]=elConn[2];
        }
        else if(j==4){
            conn[0]=elConn[0];conn[1]=elConn[1];conn[2]=elConn[3];
        }
        else{
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: tet4 only have 4 surfaces!!! surface id out of range!!!    ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
        return conn;
    case 5:
        // 8-node hexahedron.
        return conn;
    case 8:
        // 3-node second order line (2 nodes associated with the vertices and 1 with the edge).
        return conn;
    case 9:
        // 6-node second order triangle (3 nodes associated with the vertices and 3 with the edges).
        return conn;
    case 10:
        // 9-node second order quadrangle 
        return conn;
    case 11:
        // 10-node second order tetrahedron
        return conn;
    case 12:
        // 27-node second order hexahedron
        return conn;
    case 15:
        // 1-node point
        return conn;
    case 16:
        // 8-node second order quadrangle 
        return conn;
    case 17:
        // 20-node second order hexahedron
        return conn;
    default:
        return conn;
    }
}
