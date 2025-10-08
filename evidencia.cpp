#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void longestPalindrome(string s) {
    string T = "^";
    for (char c : s) {
        T += "#";
        T += c;
    }
    T += "#$";

    int n = T.size();
    vector<int> P(n, 0);
    int C = 0, R = 0; 
    vector<string> left;
    vector<string> right;

    for (int i = 1; i < n - 1; i++) {
        int mirr = 2*C - i; 
        if (i < R)
            P[i] = min(R - i, P[mirr]);        
            while (T[i + (1 + P[i])] == T[i - (1 + P[i])]){
                P[i]++;
                if (i + P[i] > R) {
                C = i;
                R = i + P[i];

            }
        }
    }

    // encontrar el palindromo mas largo
    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; i++) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    int start = (centerIndex - maxLen) / 2;
    cout << s.substr(start, maxLen) << endl;
}

string KMP(){
    return"";
}


int main() {
    vector<string> transmissions;
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
            cout<<"Error al abrir "<<filename<<endl;
        }else{
            cout<<"Se abrio "<<filename<< endl;
            string line;
            while (getline(input, line)) {
                transmissions.push_back(line);
            }
            input.close();
        }
    }
    for (int i=0;i<transmissions.size();i++){
        cout<<transmissions[i]<<endl;
    }
    string str="dnjklhcknfgdghhshhshdg";
    longestPalindrome(str);
    return 0;
}