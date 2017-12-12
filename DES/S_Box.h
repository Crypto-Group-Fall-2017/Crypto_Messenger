#ifndef S_BOX_H_
#define S_BOX_H_

#include <stdexcept>
#include <string.h>

class S_box{
	int output[32];
public:
	int* s_box(int* const input){
		std::string box[4][16] = { "1000", "0010", "0011", "0101", "0000", "0100", "0001", "1010", "1001", "1011", "1111", "1110", "1100", "1101", "0110", "0111",
				"0000", "0100", "0001", "1010", "1100", "1101", "0110", "0111", "1000", "0010", "0011", "0101", "1100", "1101", "0110", "0111",
				"1001", "1011", "1111", "1110", "0000", "0100", "0001", "1010", "1000", "0010", "0011", "0101", "1100", "1101", "0110", "0111",
				"1100", "1101", "0110", "0111", "1001", "1011", "1111", "1110", "0000", "0100", "0001", "1010", "1000", "0010", "0011", "0101"
		};

		int obit1, obit2, i = 0;
		int n = 5, m = 3;
		int index = 0;
		int h = 0;

		while(i < 48){
			if(i%6 == 0) obit1 = input[i];

			if(i%n == 0 && i != 0){
				obit2 = input[i];
				n = n+6;

				obit1 = obit1 << 1;

				std::string temp = box[obit1 + obit2][index];
				index = 0;

				output[h] = (int)temp[0] - 48;
				h++;
				output[h] = (int)temp[1] - 48;
				h++;
				output[h] = (int)temp[2] - 48;
				h++;
				output[h] = (int)temp[3] - 48;
				h++;
			}

			else if (i%6 != 0){
				index = index + (input[i] << m);
				m--;
				if(m < 0) m = 3;
			}

			++i;
		}

		return output;
	}
};

#endif /* S_BOX_H_ */
