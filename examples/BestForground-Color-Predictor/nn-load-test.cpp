#include<iostream>
#include<sstream>
#include<iomanip>
#include<typeinfo>
#include"lib/toynn.hpp"
#define ENDC "\x1b[0m"
using namespace std;

string to_string(unsigned short i){
    stringstream s;
    s<<i;
    return s.str();
}
string bgcolor(unsigned short r,unsigned short g,unsigned short b) {
    return   "\x1b[48;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
}
string fgcolor(unsigned short r,unsigned short g,unsigned short b) {
    return   "\x1b[38;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m";
}
int main(){
    srand((unsigned)time(NULL));
    NeuralNetwork nn = NeuralNetwork::load("weights.txt");
    cout<<bgcolor(0,255,72)<<fgcolor(0,0,0)<<"Nueral Network"<<ENDC<<endl;
    string fgwhite_rgb = fgcolor(255,255,255)+" white";
    string fgblack_rgb = fgcolor(0,0,0)+" black";
    int data_size = 30;
    try{
        // Data prepration
        long double r,g,b;
        Matrix *x;
        long double *y;
        x = new Matrix[data_size];
        y = new long double[data_size];
        for(int i=0;i<data_size;i++){
            x[i] = Matrix(3,1);
            r = rand()%256; 
            g = rand()%256; 
            b = rand()%256;
            x[i].assign(0,0,r);
            x[i].assign(1,0,g);
            x[i].assign(2,0,b);
            if(r+g+b >300)
                y[i] = 0;//black
            else
                y[i] = 1; //white
        }

        // prediction part
        int tcorrect = 0.0;
        Matrix preds(2,1);
        for(int i=0;i<data_size;i++){
            r = x[i].at(0,0);
            g = x[i].at(1,0);
            b = x[i].at(2,0);
            preds = nn.predict(x[i]/255);
            int index = -1;
            if(preds.at(0,0)>preds.at(1,0)){
                index = 0;
            }else{
                index = 1;
            }
            cout<<"\t"<<bgcolor(r,g,b)                              \
                <<(y[i]==1?fgwhite_rgb:fgblack_rgb)+"<=actual      "\
                <<(index==1?fgwhite_rgb:fgblack_rgb)+"<=predicted  "\
                <<ENDC;
            
            if(y[i] == index){
                tcorrect++;
                cout<<" "<<bgcolor(0,255,0)<<fgcolor(0,0,0)<<preds.at(index,0)*100<<"%"<<ENDC<<endl;
            }else{
                cout<<" "<<bgcolor(255,0,0)<<fgcolor(255,255,255)<<preds.at(index,0)*100<<"%"<<ENDC<<endl;
            }
        }
        cout<<"accuracy : "<<(double)((double)tcorrect/data_size)*100<<"%"<<endl;

    }catch(ToyNNInputException e){
        cerr<<e.getError();
    }
    catch(MatrixException e){
        cerr<<e.getError();
    }
    
}