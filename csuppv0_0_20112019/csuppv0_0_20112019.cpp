// csuppv0_0_20112019.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	/*float temp;
	float relativeHumidity;
	float illumination;
	float tempRange[2];
	float relativeHumidityRange[2];
	float illuminationRange[2];

	float parameters[9];*/  // 0: temp, 1: relative humidity, 2: illumination
						  // 3-4: temp range, 5-6: relative humidity range, 7-8: illumination range

	uint8_t i = 0;
	string line, number;
	size_t sizeOfLine;
	ifstream infile("csupp_config.txt");
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			sizeOfLine = sizeof(line);
			number = line.substr(sizeOfLine - 3, sizeOfLine - 1);
			cout << number << '\n';


			

			/*switch (i) {
			case 0:
				
				break;
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;
			case 4:

				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 8:

				break;


			}*/
		}
		infile.close();
	}

	else cout << "Unable to open file";

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
