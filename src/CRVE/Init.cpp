#include "CRVE.h"
#include "Help.h"

bool CRVE::Init(int args,char *argv[]){
    for(int i=0;i<args;++i){
        if(string(argv[i]).find("-help")!=string::npos){
            PrintHelp();
            return false;
        }
    }


    if(args<3){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: -i *.msh or -i *.gmsh2 should be given!!!                  ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        return false;
    }

    _IsPrint=false;
    _IsParticleIDSet=false;_IsMatrixIDSet=false;

    for(int i=0;i<args;++i){
        if(string(argv[i]).find("-i")!=string::npos){
            if(i<args-1){
                SetMeshFileName(string(argv[i+1]));
                SetMeshType(MeshType::MSH);
                if(GetMshVersionFromMshFile(GetMeshFileName())>2.2){
                    SetMeshType(MeshType::MSH4);
                }
                if(string(argv[i+1]).find(".gmsh2")!=string::npos){
                    SetMeshType(MeshType::GMSH2);
                }
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: msh or gmsh2 file name should be given after -i            ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-tol")!=string::npos){
            if(i<args-1){
                SetTolerance(atof(argv[i+1]));
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: value should be given after -tol                           ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-pid")!=string::npos){
            if(i<args-1){
                SetParticlePhyID(atoi(argv[i+1]));
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: value should be given after -pid                           ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-mid")!=string::npos){
            if(i<args-1){
                SetMatrixPhyID(atoi(argv[i+1]));
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: value should be given after -Mid                           ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-print")!=string::npos){
            if(i<args-1){
                if(string(argv[i+1]).find("true")!=string::npos||
                   string(argv[i+1]).find("TRUE")!=string::npos){
                   _IsPrint=true;
                }
                else if(string(argv[i+1]).find("false")!=string::npos||
                   string(argv[i+1]).find("false")!=string::npos){
                    _IsPrint=false;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: unknown flag after -print !!!                              ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    return false;
                }
            }
            else{
                _IsPrint=true;
            }
        }
    }
    return true;
}