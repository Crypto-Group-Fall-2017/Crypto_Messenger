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

using namespace std;

int main(int argc, char const *argv[]) {
    int input[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    int* arr = p_box(input);

    for(int i = 0; i < 32; i++){
        cout << arr[i] << " ";
    }

    return 0; //No error.
}
