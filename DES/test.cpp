#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <exception>
#include <vector>
#include <fstream>
#include <cstdio>
// <inttypes.h>

#include "des_exp_perm.h"
#include "p_box.h"
#include "des_main.h"

#define DEBUG 0

using namespace std;

uint64_t getSessionKey(){
    FILE *f;
    uint64_t key;
    f = fopen("session_key_8000", "r");
    if (f != NULL){
        fscanf(f, "%llu", &key);
        fclose(f);
    }
    if (DEBUG){
        printf("\nThis is the key seen by des.cpp: %llu\n", key);
    }
    return key;
}

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

string xorMessage(string message, string code){
    string output;
    for(int i = 0 ; i < message.length(); i++){
        output.push_back((uint8_t )message[i] ^ (uint8_t)code[i%8]);
        //cout << (( (uint8_t) one[i] )^( (uint8_t) two[i] )) << " ";
        //std::cout<<std::bitset<8>((( (uint8_t) one[i] )^( (uint8_t) two[i] )))<<std::endl;
    }
    // cout << endl;
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

int* intToBinary(uint64_t input){
    int *arr = new int[64];
    for (int i = 0; i < 64; i++){
        arr[i] = (input >> (63 - i)) & 1;
    }
    if (DEBUG){
        printf("\nInteger Array Value of Key:\n");
        for (int i = 0; i < 64; i++){
            printf("%d", arr[i]);
        }
        printf("\n");
    }
    return arr;
}

string padWithZeros(string input){
    int numToPad = input.length() % 8;
    for (int i = 0; i < numToPad; i++) {
        input += (char) 0;
    }
    return input;
}


int main(int argc, char const *argv[]) {

    uint64_t key = getSessionKey();
    string identifier = "helphelp";
    string plainText = "private.";

    ifstream inFile;
    inFile.open("file.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string input;
    getline(inFile,input, '\n');
    // cout << "test: "<< input << endl;

    inFile.close();

    string encryptedCode = BinToAc(des_encrypt(stringToBinary(identifier), intToBinary(key)));
    // cout << encryptedCode << endl;

    string xorResult = xorMessage((input),encryptedCode);
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
