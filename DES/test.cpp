#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <exception>
#include <vector>
#include <fstream>

#include "des_exp_perm.h"
#include "p_box.h"
#include "des_main.h"

using namespace std;

string BinToAc(int array[64]){
    string output;
    int result = 0;
    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            result = result + (array[i + (8*j)] << (7-i));
        }
        output.push_back((char)result);
        result = 0;
    }
    return output;
}

string xor8(string one, string two){
    string output;
    for(int i = 0 ; i < 8; i++){
        output.push_back((uint8_t )one[i] ^ (uint8_t)two[i]);
        //cout << (( (uint8_t) one[i] )^( (uint8_t) two[i] )) << " ";
        //std::cout<<std::bitset<8>((( (uint8_t) one[i] )^( (uint8_t) two[i] )))<<std::endl;
    }
    // cout << endl;
    return output;
}

int* stringToBinary(string input){
    int length = input.length();
    int *arr = new int[length*8];
    for (int i = 0; i < length; i++) {
        uint8_t ascii8bits = (uint8_t) input[i];
        for(int j = 0; j < 8 ; j++){
            arr[(i*8)+j] = (ascii8bits >> (7-j)) & 1;
        }
    }
    return arr;
}


int main(int argc, char const *argv[]) {

    string key = "estoniar";
    string identifier = "helphelp";
    string plainText = "private.";

    ifstream inFile;
    inFile.open("file.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string input;
    string input2;
    while(!inFile.eof()){
        inFile >> input;
        input2 += input + " ";
    }

    inFile.close();

    input2.resize(input2.length()-1);

    string encryptedCode = BinToAc(des_encrypt(stringToBinary(identifier),stringToBinary(key)));
    // cout << encryptedCode << endl;

    string xorResult = xor8(input2,encryptedCode);
    // cout << xorResult << endl;

    string getMessageBack = xor8(xorResult, encryptedCode);
    // cout << getMessageBack << endl;

    //write to file:
    xorResult += "\n";

    ofstream myfile;
    myfile.open ("file.txt");
    myfile << xorResult;
    myfile.close();


    return 0; //No error.
}
