

// E1. Actividad Integradora 1 
//
/*

    EQUIPO:
    Amparo Alcaraz Tonella A01253885
    Valeria López Flores A00838648

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//Complejidad O(n)
void constructLps(string &pat, vector<int> &lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < pat.length()) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

//Complejidad O(n+m)
vector<int> KMPsearch(string &pat, string &txt) {
    int n = txt.length();
    int m = pat.length();
    vector<int> lps(m);
    vector<int> res;
    constructLps(pat, lps);
    int i = 0;
    int j = 0;
    while (i < n) {
        if (txt[i] == pat[j]) {
            i++;
            j++;
            if (j == m) {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        }
        else {
            if (j != 0){
                j = lps[j - 1];
            }else{
                i++;
            }
        }
    }
    return res;
}

//Complejidad O(n)
string longestPalindrome(string s, int &start) {
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
    start = (centerIndex - maxLen) / 2;
    return s.substr(start,maxLen);
}



void PalindromeOutput(vector<string> transmissions, string &outputText){
    string mirrorCodes;
    outputText += "============\n";
    outputText += "Palindromo mas grande \n";
     for (int i=0;i<transmissions.size();i++){
        outputText += "transmission"+ to_string(i+1) + ".txt ==> ";
        int positionHolder;
        mirrorCodes=longestPalindrome(transmissions[i], positionHolder);
        outputText += "Posicion: "+ to_string(positionHolder) + "\n";
        outputText += mirrorCodes + "\n";
        
    }
    

}

//Complejidad O(n*m)
string LCSubstring(const string& str1, const string& str2) {
    int str1Size = str1.size();
    int str2Size = str2.size();

    if(str1Size == 0 || str2Size == 0){
        return "";
    }
    vector<vector<int>> dp(str1Size + 1, vector<int>(str2Size + 1, 0));
    int maxLen = 0;
    int posEnd = 0;

    for (int i = 1; i <= str1Size; i++) {
        for (int j = 1; j <= str2Size; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    posEnd = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

   if (maxLen > 0) {
        return str1.substr(posEnd - maxLen, maxLen);
    } else {
        return "";
    }
}

void LCSubstringOutput(const vector<string>& transmissions, string& outputText) {
    outputText += "============\n";
    outputText += "Los Substrings mas largos son:\n";
    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = i + 1; j < transmissions.size(); ++j) {
            string lcs = LCSubstring(transmissions[i], transmissions[j]);
            outputText += "T" + to_string(i+1) + " - T" + to_string(j+1) + ": " + lcs + "\n";
        }
    }
  
}

//Complejidad O(n*m)
void findSubsequences(vector<string> transmissions, string mcode, string &outputText){
    string bestSubseq;
    int bestFile;
    int mostTimes=0;
    vector<int> holder;
    //cout<<mcode<<endl;
    for (int i=0; i<mcode.size(); i++){
        string sub=mcode;
        sub.erase(i, 1);
        //cout<<"subseq  "<<sub<<endl;
        for(int t=0;t<transmissions.size();t++){
            holder=KMPsearch(sub, transmissions[t]);
            if(holder.size()>mostTimes){
                mostTimes=holder.size();
                bestFile=t;
                bestSubseq=sub;
            }
        }   
    }
    outputText+="La subsecuencia más encontrada es: " +bestSubseq +" con "+ to_string(mostTimes) +" veces en el archivo" + to_string(bestFile) +".txt\n";
}

//Complejidad O(n*m)
void findCodes(vector<string> transmissions, vector<string>mcodes, string &outputText){
    string maxFound;
    int timesFound=0;
    for(int i=0;i<mcodes.size();i++){
        outputText += "Código: " + mcodes[i]+" \n";
        for(int j=0;j<transmissions.size();j++){
            vector<int> res = KMPsearch(mcodes[i], transmissions[j]);
            outputText += "transmission"+ to_string(j+1) + ".txt ==> ";
            outputText += to_string(res.size()) + " veces\n";
            for(int i=0;i<res.size();i++){
                outputText+= to_string(res[i]);
                if(i<res.size()-1){
                    outputText+=", ";
                }
            }
            outputText+= "\n";
        }
        findSubsequences(transmissions, mcodes[i], outputText);
        
        outputText+= "--------------\n \n";
    }
}



int main() {
    vector<string> transmissions;
    vector<string> mcodes;
    vector <string> mirrorCodes;
    vector <string> longestCommonCode;
    string filename;
    string outputText="";


    //TRANSMISSION FILES
    for(int i=0;i<3;i++){
        string num;
        num=to_string(i+1);

        //string num = to_string(i + 1);
        filename ="transmission";
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

    //MALICIOUS CODES
    filename="mcode.txt";
    ifstream input(filename);
    if (!input.is_open()) {
        cout<<"Error al abrir "<<filename<<endl;
    }else{
        cout<<"Se abrio "<<filename<< endl;
        string line;
        while (getline(input, line)) {
            mcodes.push_back(line);
        }
        input.close();
    }

    // ENCONTRAR CODIGOS MALICIOSOS (KMP)
    findCodes(transmissions,mcodes, outputText);

    // ECONTRAR ESPEJOS ( PALINDROMO MAS LARGO)
    PalindromeOutput(transmissions,outputText);

    // ENCONTRAR SIMILITUDES EN TRANSMISIONES (LONGEST COMMON SUBSTRING)
    LCSubstringOutput(transmissions, outputText);


    //OUTPUT
    ofstream outputFile("checking0.txt");
    if (outputFile.is_open()) {
        outputFile << outputText;
        cout<<outputText<<endl;

        outputFile.close();
        cout << "Se escribio en el achivo de output";
    } else {
        cout<< "No se pudo escribir en el achivo de output";
    }

    return 0;
}