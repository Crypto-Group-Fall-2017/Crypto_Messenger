/*****
 Agustin Malo
 Crypto Fall 17
 Nemo
 Ex 2
 btrans.cpp
 *****/
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <exception>
#include <vector>
#include <fstream>
using namespace std;

int* des_exp_perm(int input32bits[32]){
    // Const Array holds the position (plus 1) of the new expanded array.
    static const int desExpansion[48] = {
       32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
        8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
       16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
       24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
    };
    int *result = new int[48];
    /*
    Loops through 48 bits and puts them in the right place, subtract by one
    since array holds indexes 1-->32.
    */
    for(int i = 0; i < 48; i++){
        result[i] = input32bits[desExpansion[i]-1];
    }
    return result;
}
