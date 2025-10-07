#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    for(int i=0;i<3;i++){
        string num;
        //Hay que cambiar esta seccion por algo que combierta i a string
        if(i+1==1){
            num="1";
        }else if(i+1==2){
            num="2";
        }else if(i+1==3){
            num="3";
        }
        //string num = to_string(i + 1);
        string filename ="transmission";
        filename+=num;
        filename+=".txt";
        ifstream input(filename);
        if (!input.is_open()) {
            cout<<"Error al abrir "<<"transmission"<<endl;
        }else{
            cout<<"Se abrio "<<filename<< endl;
            string line;
            while (getline(input, line)) {
                cout << line << endl;
            }
            input.close();
        }
    }
    return 0;
}