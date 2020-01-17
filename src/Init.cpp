#include "GmshIO.h"
// #include "Help.h"
bool GmshIO::Init(int args,char *argv[]){
    for(int i=0;i<args;++i){
        if(string(argv[i]).find("-help")!=string::npos){
            //PrintHelp();
            return false;
        }
    }

    _IsSplitMatrixAndParticle=true;
    _IsSplitMatrixOnly=false;
    _IsSplitParticleOnly=false;
    SetTolerence(1.0e-3);
    _IsPrint=true;

    if(args<3){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: -i *.msh should be given!!!                                ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        return false;
    }

    for(int i=0;i<args;++i){
        if(string(argv[i]).find("-i")!=string::npos){
            if(i<args-1){
                SetMeshFileName(string(argv[i+1]));
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: msh file name should be given after -i                     ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-tol")!=string::npos){
            if(i<args-1){
                SetTolerence(atof(argv[i+1]));
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: value should be given after -tol                           ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                return false;
            }
        }
        else if(string(argv[i]).find("-bounall")!=string::npos){
            if(i<args-1){
                if(string(argv[i+1]).find("true")!=string::npos||
                   string(argv[i+1]).find("TRUE")!=string::npos){
                    _IsSplitMatrixAndParticle=true;
                    _IsSplitMatrixOnly=false;
                    _IsSplitParticleOnly=false;
                }
                else if(string(argv[i+1]).find("false")!=string::npos||
                   string(argv[i+1]).find("false")!=string::npos){
                    _IsSplitMatrixAndParticle=false;
                    _IsSplitMatrixOnly=true;
                    _IsSplitParticleOnly=false;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: unknown flag after -bounall !!!                            ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    return false;
                }
            }
            else{
                _IsSplitMatrixAndParticle=true;
                _IsSplitMatrixOnly=false;
                _IsSplitParticleOnly=false;
            }
        }
        else if(string(argv[i]).find("-bounmat")!=string::npos){
            if(i<args-1){
                if(string(argv[i+1]).find("true")!=string::npos||
                   string(argv[i+1]).find("TRUE")!=string::npos){
                    _IsSplitMatrixAndParticle=false;
                    _IsSplitMatrixOnly=true;
                    _IsSplitParticleOnly=false;
                }
                else if(string(argv[i+1]).find("false")!=string::npos||
                   string(argv[i+1]).find("false")!=string::npos){
                    _IsSplitMatrixAndParticle=false;
                    _IsSplitMatrixOnly=false;
                    _IsSplitParticleOnly=true;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: unknown flag after -bounmat !!!                            ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    return false;
                }
            }
            else{
                _IsSplitMatrixAndParticle=true;
                _IsSplitMatrixOnly=false;
                _IsSplitParticleOnly=false;
            }
        }
        else if(string(argv[i]).find("-bounpar")!=string::npos){
            if(i<args-1){
                if(string(argv[i+1]).find("true")!=string::npos||
                   string(argv[i+1]).find("TRUE")!=string::npos){
                    _IsSplitMatrixAndParticle=false;
                    _IsSplitMatrixOnly=false;
                    _IsSplitParticleOnly=true;
                }
                else if(string(argv[i+1]).find("false")!=string::npos||
                   string(argv[i+1]).find("false")!=string::npos){
                    _IsSplitMatrixAndParticle=true;
                    _IsSplitMatrixOnly=false;
                    _IsSplitParticleOnly=false;
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: unknown flag after -bounpar !!!                            ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    return false;
                }
            }
            else{
                _IsSplitMatrixAndParticle=true;
                _IsSplitMatrixOnly=false;
                _IsSplitParticleOnly=false;
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