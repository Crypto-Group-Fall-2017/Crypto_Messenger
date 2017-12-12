
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <exception>
#include <vector>
#include <fstream>

#include "stdio.h"

using namespace std;

#define DEBUG 0

int** des_key_mangler(int sessionKey[64])
{
    int** array2D = 0;
    array2D = new int*[16];

    for (int h = 0; h < 16; h++)
    {
        array2D[h] = new int[48];
    }

    //This is permutation for the 56-bit key
    const int PC1[56] = {
        57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
    //This is the permutation for the round keys
    const int PC2[48] = {
        13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3, 27, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47, 43, 48, 37, 55, 33, 52, 45, 41, 49, 35, 28, 31};
    //This is the shifting schedule
    const int shft[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    //This is the holder of the original session key split to a 56 bit array
    int sessionKey56[56];
    //These are the holders of each left and right halves of every round
    int leftHalf[16][28];
    int rightHalf[16][28];
    //This is the output 2D array for every round key
    int i = 0;
    int j = 0;
    int temp;

    //separates the session key into a 56-bit array via the PC1 array
    for (i = 0; i < 56; i++)
    {
        sessionKey56[i] = sessionKey[PC1[i]];
        if (DEBUG)
        {
            printf("%d ", sessionKey56[i]);
        }
    }
    //debugging the start of session keys
    if (DEBUG)
    {
        printf("\n56-bit, permutated session key at START:\n");
        for (i = 0; i < 56; i++)
        {
            if (DEBUG)
            {
                printf("%d ", sessionKey56[i]);
            }
        }
        printf("\n");
    }

    //separates 56-bit key into halves, left shifts them, and stores in leftHalf[0] & rightHalf[0]
    for (i = 0; i < 16; i++)
    {
        //I use this because shft[i] throws a bs undefined behavior error
        //temp = shft[i];
        //if shift is 1 place
        if (temp == 1)
        {
            for (j = 0; j < 28; j++)
            {
                //last place gets first in array
                if (j == 27)
                {
                    leftHalf[i][27] = sessionKey56[0];
                    rightHalf[i][27] = sessionKey56[28];
                    continue;
                }
                //otherwise left shift
                leftHalf[i][j] = sessionKey56[j + 1];
                rightHalf[i][j] = sessionKey56[j + 29];
            }
        }
        //if shift is 2 places
        else
        {
            for (j = 0; j < 28; j++)
            {
                //last 2 places gets first and second in array
                if (j == 26)
                {
                    leftHalf[i][j] = sessionKey56[(0)];
                    rightHalf[i][j] = sessionKey56[28];
                }
                else if (j == 27)
                {
                    leftHalf[i][j] = sessionKey56[1];
                    rightHalf[i][j] = sessionKey56[29];
                }
                //otherwise left shift
                else
                {
                    leftHalf[i][j] = sessionKey56[j + 2];
                    rightHalf[i][j] = sessionKey56[j + 30];
                }
            }
        }
        //reset the session key to the left and right half values for use in next round
        for (j = 0; j < 28; j ++)
        {
            sessionKey56[j] = leftHalf[i][j];
            sessionKey56[j + 28] = rightHalf[i][j];
        }
        //Debugging for session keys
        if (DEBUG)
        {
            printf("\n56-bit, permutated session key ROUND %d:\n", i);
            for (j = 0; j < 56; j++)
            {
                printf("%d ", sessionKey56[j]);
            }
            printf("\n");
        }
    }

    //creates and stores round keys for rounds 1-16
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 24; j++)
        {
            array2D[i][j] = leftHalf[i][PC2[j]];
            array2D[i][j + 24] = rightHalf[i][PC2[j + 24]];
        }
    }
    //Debugging for round keys
    if (DEBUG)
    {
        for (int i = 0; i < 16; i++)
        {
            printf("\nRound Key %d:\n", i);
            for (int j = 0; j < 48; j++)
            {
                printf("%d ", array2D[i][j]);
            }
            printf("\n");
        }
    }
    // array2D = roundKeys;


    return array2D;
}
