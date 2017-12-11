// Implementation file for Main DES Encryption

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
#include "S_Box.h"
#include "des_key_mangler.h"


using namespace std;

int* xor_helper(int one[], int two[], int size){
    int *result = new int[size];

    for(int i = 0; i<size; i++){
        result[i] = one[i] ^ two[i];
    }

    return result;
}

int* des_encrypt_one_round(int inputArray[64], int mangledKey[48]){
    int *result = new int[64];

    //Split to two halves
    int left[32];
    int right[32];

    for(int i = 0; i < 32; i++){
        left[i] = inputArray[i];
        right[i] = inputArray[i+32];
    }

    //Take right half and do DES expansion
    int* expansion = des_exp_perm(right);

    //Take DES expansion result and xor with mangler output
    int *xor48 = xor_helper(expansion,mangledKey,48);

    //Take XOR'd result and pass through S-box
    S_box *sboxObj = new S_box();
    int *sbox32 = sboxObj->s_box(xor48);
        /* insert sbox function here! */

    //Take S-box result and pass through P-box
    int *pbox32 = p_box(sbox32);

    //XOR left half and P-box output
    pbox32 = xor_helper(left, pbox32, 32);

    //Original right half is new left half,
    //XOR output is new right half
    for(int i = 0; i < 64; i++){
        if(i<32){
            result[i] = right[i];
        }else{
            result[i] = pbox32[i-32];
        }
    }

    return result;
}


int* des_encrypt(int inputArray[64], int keyArray[64]){

    int** mangledKeys = des_key_mangler(keyArray);

    // Mangle key array and put in 2-D array of round keys (size 48)
    for(int i = 0; i < 16; i++){
        inputArray = des_encrypt_one_round(inputArray,mangledKeys[i]);
    }

    return inputArray;
}
