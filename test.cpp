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
#include "des_exp_perm.h"

using namespace std;

int main(int argc, char const *argv[]) {

    int input[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int* arr = des_exp_perm(input);

    for(int i = 0; i < 48; i++){
        cout << arr[i] << " ";
    }

    return 0; //No error.
}
