#include "CRVE.h"

CRVE::CRVE(int args,char *argv[]){
    _InputMeshFileName.clear();
    _HasFileName=false;

    _HasFormatOption=false;
    _OutputFileFormat=FileFormat::Msh;
    _HasPrint=true;

    _nNodes=0;_nElmts=0;
    _nMaxDim=-1;_nMinDim=4;
    _NodeCoords.clear();
    _ElmtConn.clear();
    _PhyGroupNameList.clear();
    _PhyID2NameList.clear();
    _PhyName2IDList.clear();
    _PhyDimVec.clear();

    _ParticleID=-1;_MatrixID=-1;;
    _HasParticleID=false;_HasMatrixID=false;

    _Tol=1.0e-2;

    _nGP=2;

    bool HasHelp=false;

    vector<double> numbers;

    if(args==1){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: no option is given                                     !!! ***"<<endl;
        cout<<"***        you should run 'crve -i your.msh'                      !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }
    else if(args==2){
        if(string(argv[1]).compare("-h")==0||
           string(argv[1]).compare("-help")==0){
            HasHelp=true;
        }
        else{
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: invalid option is given                                !!! ***"<<endl;
            cout<<"***        you should run 'crve -i your.msh'                      !!! ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
    }
    else if(args==3){
        if(string(argv[1]).compare("-i")==0&&
           (string(argv[2]).find(".msh")||
            string(argv[2]).find(".gmsh")||
            string(argv[2]).find(".inp"))){
            _InputMeshFileName=string(argv[2]);
            _OutputFileFormat=FileFormat::Msh;
            _HasFileName=true;
        }
        else{
            cout<<"*************************************************************************"<<endl;
            cout<<"*** Error: you should run 'crve -i your.msh'                      !!! ***"<<endl;
            cout<<"*************************************************************************"<<endl;
            abort();
        }
    }
    else{
        string str,str2,substr;
        for(int i=1;i<args;i++){
            str=string(argv[i]);
            if(str.compare("-i")==0){
                if(i<args-1){
                    str2=string(argv[i+1]);
                    if(str2.find(".msh")||str2.find(".gmsh")||str2.find(".inp")){
                        _InputMeshFileName=str2;
                        _HasFileName=true;
                    }
                    else{
                        cout<<"*************************************************************************"<<endl;
                        cout<<"*** Error: unsupported file format                                !!! ***"<<endl;
                        cout<<"*************************************************************************"<<endl;
                        abort();
                    }
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: no file name found after -i option                     !!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            else if(str.compare("-h")==0||str.compare("-help")==0){
                HasHelp=true;
            }
            else if(str.compare("-pid")==0){
                if(i<args-1){
                    str2=string(argv[i+1]);
                    numbers=SplitStrNum(str2);
                    if(numbers.size()<1){
                        cout<<"*************************************************************************"<<endl;
                        cout<<"*** Error: no number is given after -pid option                   !!! ***"<<endl;
                        cout<<"*************************************************************************"<<endl;
                        abort();
                    }
                    else{
                        _ParticleID=static_cast<int>(numbers[0]);
                        _HasParticleID=true;
                    }
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: no number is given after -pid option                   !!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            else if(str.compare("-mid")==0){
                if(i<args-1){
                    str2=string(argv[i+1]);
                    numbers=SplitStrNum(str2);
                    if(numbers.size()<1){
                        cout<<"*************************************************************************"<<endl;
                        cout<<"*** Error: no number is given after -mid option                   !!! ***"<<endl;
                        cout<<"*************************************************************************"<<endl;
                        abort();
                    }
                    else{
                        _MatrixID=static_cast<int>(numbers[0]);
                        _HasMatrixID=true;
                    }
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: no number is given after -mid option                   !!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            else if(str.compare("-print")==0){
                _HasPrint=true;
            }
            else if(str.compare("-tol")==0){
                if(i<args-1){
                    str2=string(argv[i+1]);
                    numbers=SplitStrNum(str2);
                    if(numbers.size()<1){
                        cout<<"*************************************************************************"<<endl;
                        cout<<"*** Error: no value is given after -tol option                    !!! ***"<<endl;
                        cout<<"*************************************************************************"<<endl;
                        abort();
                    }
                    else{
                        if(numbers[0]<1.0e-15){
                            cout<<"*************************************************************************"<<endl;
                            cout<<"*** Error: invalid value for -tol option                          !!! ***"<<endl;
                            cout<<"*************************************************************************"<<endl;
                            abort();
                        }
                        _Tol=static_cast<double>(numbers[0]);
                    }
                }
                else{
                    cout<<"*************************************************************************"<<endl;
                    cout<<"*** Error: no value is given after -tol option                    !!! ***"<<endl;
                    cout<<"*************************************************************************"<<endl;
                    abort();
                }
            }
            else{
                cout<<"*************************************************************************"<<endl;
                cout<<"*** Error: unsupported option is detected                         !!! ***"<<endl;
                cout<<"*************************************************************************"<<endl;
                abort();
            }
        }
    }

    if(HasHelp){
        PrintHelp();
        return;
    }

    if(!_HasFileName){
        cout<<"*************************************************************************"<<endl;
        cout<<"*** Error: no mesh file is given                                  !!! ***"<<endl;
        cout<<"*************************************************************************"<<endl;
        abort();
    }
}

//****************************************************
void CRVE::PrintHelp()const{
    cout<<"*************************************************************************"<<endl;
    cout<<"*** Normally, you should run: 'crve -i your.msh'                      ***"<<endl;
    cout<<"*** To show this menu: 'crve -h' or 'crve -help'                      ***"<<endl;
    cout<<"*** To specify the particle phase phase id:                           ***"<<endl;
    cout<<"***    crve -i your.msh -pid 10001                                    ***"<<endl;
    cout<<"*** To specify the matrix phase phase id:                             ***"<<endl;
    cout<<"***    crve -i your.msh -mid 10002                                    ***"<<endl;
    cout<<"***  by default, the smaller id is the matri phase                    ***"<<endl;
    cout<<"*** To print out some information:                                    ***"<<endl;
    cout<<"***    crve -i your.msh -print                                        ***"<<endl;
    cout<<"*** To set the tolerance:                                             ***"<<endl;
    cout<<"***    crve -i your.msh -tol 1.0e-3                                   ***"<<endl;
    cout<<"*************************************************************************"<<endl;
}