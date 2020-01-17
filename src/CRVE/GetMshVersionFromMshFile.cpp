#include "CRVE.h"

double CRVE::GetMshVersionFromMshFile(string filename)const{
    ifstream in;
    in.open(filename.c_str(),ios::in);
    if(!in.is_open()){
        cout<<"*** Error: can't open geo file(name="<<filename<<")!"<<endl;
        cout<<"*** Please enter the correct msh file name !!!";
        abort();
    }
    string str;
    double version;
    int format,size;
    while(!in.eof()){
        getline(in,str);

        if(str.find("$MeshFormat")!=string::npos){
            // read the mesh format block
            in>>version>>format>>size;
            if((version!=2.0)&&(version!=2.1)&&(version!=2.2)&&(version!=4.0)&&(version!=4.1)){
                cout<<"*** Error: version="<<version<<" is not supported!"<<endl;
                abort();
            }
            else{
                break;
            }
        }
    }
    in.close();
    return version;
}