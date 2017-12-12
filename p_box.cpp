// Implementation file for DES P-Box

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

int* p_box(int input32bits[32]){
    // Const Array holds the position (plus 1) of the new expanded array.
    static const int desPbox[32] = {
        16,  7, 20, 21, 29, 12, 28, 17,  1, 15, 23, 26,  5, 18, 31, 10,
        2,  8, 24, 14, 32, 27,  3,  9, 19, 13, 30,  6, 22, 11,  4, 25
    };
    int *result = new int[32];
    /*
    Loops through 32 bits and puts them in the right place, subtract by one
    since array holds indexes 1-->32.
    */
    for(int i = 0; i < 32; i++){
        result[i] = input32bits[desPbox[i]-1];
    }
    return result;
}
