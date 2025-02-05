// csuppv0_0_20112019.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main(){	
	int i = 0;
	int j = 0;
	string line, str;
	int number[9];

	//============ READING FROM FILE

	string lineOfFile[6] = { "TEMPERATURA: " ,"VLAZNOST: ","OSVETLJENOST: " , "INTERVAL TEMPERATURE: [", "STOPNJA VLAZNOSTI: [", "INTERVAL OSVETLJENOSTI: [" };
	
	
	ifstream infile("csupp_config.txt");																			//open file
	if (infile.is_open())
	{
		while (getline(infile, line))																				//for each line
		{
			str = line.substr(0, lineOfFile[i].length());
			if (str == lineOfFile[i]) {																				//if the start of the string is correct
				number[j] = stoi(line.substr(lineOfFile[i].length(), (lineOfFile[i].length()+1)), 0, 10);			//stores the number in the string
				if (i > 2) {																						//if we should have two numbers per line
					j++;
					number[j] = stoi(line.substr((lineOfFile[i].length()+4), (lineOfFile[i].length() + 1)), 0, 10); //then it stored the second one as well
				}
			}
			else {
				cout << "Invalid input file\n";																		//error if the line doesn't match TODO: implement more than just a message
				break;
			}
			i++;
			j++;
		}
		infile.close();
	} else cout << "Unable to open file";

	//=============================

	int targetTemp = number[0];
	int targetRelativeHumidity = number[1];
	int targetIllumination = number[2];
	int tempRange[2] = { number[3], number[4] };
	int relativeHumidityRange[2] = { number[5], number[6] };
	int illuminationRange[2] = { number[7], number[8] };
	int temp, relativeHumidity, illumination, dTemp, dRelativeHumidity, dIllumination;
	unsigned int comparisonResult[3];


	//============ IZPIS
	
	cout << "|======================|\n|                      |\n|***AVTOMATSKI NACIN***|\n|                      |\n|======================|\n\n\n";
	cout << "Zelene vrednosti:\n" << targetTemp << "°C, " << targetRelativeHumidity << "%, " << targetIllumination << "lx\n\n";
	cout << "Intervali:\n" << tempRange[0] << '-' << tempRange[1] << "°C, " << relativeHumidityRange[0] << '-' << relativeHumidityRange[1] << "%, " << illuminationRange[0] << '-' << illuminationRange[1] << "lx\n\n";
	cout << "Temperatura| Vlaznost |Osvetljenost|       Odstopanja       |  Ukazi  \n";

	//============ AVTOMATSKI NACIN 1

	srand(time(NULL));
	for (int i = 0; i < 10; i++) {


		temp = rand() % (tempRange[1] - tempRange[0] + 1) + tempRange[0];															// random number generation for input values
		relativeHumidity = rand() % (relativeHumidityRange[1] - relativeHumidityRange[0] + 1) + relativeHumidityRange[0];
		illumination = rand() % (illuminationRange[1] - illuminationRange[0] + 1) + illuminationRange[0];

		

		for (int j = 0; j < 3; j++) // resets the values of the previous comparisons
			comparisonResult[j] = 0;

	

		if (temp < targetTemp)      // compares stuff
			comparisonResult[0] = 1;
		else if (temp > targetTemp) 
			comparisonResult[0] = 2;
		
		if (relativeHumidity < targetRelativeHumidity)
			comparisonResult[1] = 1;
		else if (relativeHumidity > targetRelativeHumidity)
			comparisonResult[1] = 2;

		if (illumination < targetIllumination)
			comparisonResult[2] = 1;
		else if (illumination > targetIllumination)
			comparisonResult[2] = 2;

		dTemp = temp - targetTemp;
		dRelativeHumidity = relativeHumidity - targetRelativeHumidity;
		dIllumination = illumination - targetIllumination;


		


		//========================================================== a fuckton of couts

		cout << "......." << temp << "°C|......." << relativeHumidity << "%|.....";
		if (illumination < 10000)
			cout << '.';
		if (illumination < 1000)
			cout << '.';
		if (illumination < 100)
			cout << '.';
		cout << illumination << "lx|..";
		if ((dTemp < 10) && (dTemp > -10))
			cout << '.';
		if (dTemp >= 0)
			cout << '+';
		cout << dTemp << "°C|..";
		if ((dRelativeHumidity < 10) && (dRelativeHumidity > -10))
			cout << '.';
		if (dRelativeHumidity >= 0)
			cout << '+';
			
		cout << dRelativeHumidity << "%|.";
		if ((dIllumination < 10000) && (dIllumination > -10000))
			cout << '.';
		if ((dIllumination < 1000) && (dIllumination > -1000))
			cout << '.';
		if ((dIllumination < 100) && (dIllumination > -100))
			cout << '.';
		if ((dIllumination < 10) && (dIllumination > -10))
			cout << '.';
		if (dIllumination >= 0)
			cout << '+';
		cout << dIllumination << "lx|T" << comparisonResult[0] << ",V" << comparisonResult[1] << ",O" << comparisonResult[2] << "\n";

		//==========================================================
	

	}

	

	//float parameters[9];  // 0: temp, 1: relative humidity, 2: illumination
						  // 3-4: temp range, 5-6: relative humidity range, 7-8: illumination range


	

	


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
