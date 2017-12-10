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

// char* convertToString(int array[64]){
//     char* arr = new char[8];
//     for (int i = 0; i < 8; i++) {
//         int result = 0;
//         for (int j = 7; j >= 0; j--) {
//             result |=  (array[(i*8)+j]) << (7-j);
//         }
//         arr[i] = (char) (result );
//     }
//     return arr;
// }

// void xorWithCode(int code[], char *str){
//
//
// }



int main(int argc, char const *argv[]) {

    //Testing p_box
    int input1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

    int* arr = p_box(input1);

    // for(int i = 0; i < 32; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl << endl;



    //Testing des_expansion
    arr = des_exp_perm(input1);

    // for(int i = 0; i < 48; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl << endl;



    // EX: IP ADDRESS 130.5.5.25
    int identifier[] = {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1};
    int private_key[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};

    arr = des_encrypt(identifier, private_key);
    cout << "Cypher Text - DES Output" << endl;
    for(int i = 0; i < 64; i++){
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    char plainText[] = "private message.";
    // cout << "Plain Text Message: " << plainText << endl;
    //
    //
    // int mess[] = {1,0,0,0,0,1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1};
    // cout << convertToString(mess);



    //Testing des_encrypt
    int input2[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    int input3[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};

    arr = des_encrypt(input2, input3);

    // for(int i = 0; i < 64; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl << endl;



    //Testing XOR
    int input4[] = {0,1,1,0};
    int input5[] = {1,1,1,0};

    arr = xor_helper(input4, input5, 4);

    // for(int i = 0; i < 4; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl << endl;


    return 0; //No error.
}
