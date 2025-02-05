// csuppv1_0_20112019.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
//#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>


#include <time.h>
#include <stdlib.h>

#include "functions.h"
using namespace std;

/*class Parameters {
	float tempC, tempF, tempK, tempR, tempDe, tempN, tempRe, tempRo, humidity, illumination;
} param;*/


int main(){
	int i = 0;
	int j = 0;
	int number[9] = { 1,1,1,1,1,1,1,1,1 };
	int* pNumber;
	pNumber = &number[0];
	int iterations = 100;
	int delay = 0;
	char modeSelect = '!';


	readFromFile(pNumber);

	//=============================

	int targetTemp = number[0];
	int targetRelativeHumidity = number[1];
	int targetIllumination = number[2];
	int tempRange[2] = { number[3], number[4] };
	int relativeHumidityRange[2] = { number[5], number[6] };
	int illuminationRange[2] = { number[7], number[8] };
	int temp, humidity, illumination, dTemp, dHumidity, dIllumination;
	unsigned int comparisonResult[3];


	//============ some couts

	cout << "Centralni sistem za upravljanje poslovnega prostora, v0.00 [02122019]\n";
	cout << "===============================================\n\n";
	cout << "|===================|\n";
	cout << "|                   |\n";
	cout <<	"|****GLAVNI MENI****|\n";
	cout << "|                   |\n";
	cout <<	"|===================|\n";


	//============ main menu
	do {

		cout << "\n======================\n";
		cout << " 0) Izhod\n";
		cout << " 1) Avtomatski nacin\n";
		cout << " 2) Avtomatski nacin 2\n";
		cout << " +) Pomoc\n";
		cout << "====================\n";
		cin >> modeSelect;
		if (modeSelect == '0')
			return 0;
		if (modeSelect == '+') {
			if (displayHelp())
				cout << "Unable to display help\n";
		}

	} while (modeSelect != '0' && modeSelect != '1' && modeSelect != '2');




	//========== auto mode couts

	cout << "\n|========================|\n";
	cout <<	"|                        |\n";
	if (modeSelect == '1')
		cout << "|****AVTOMATSKI NACIN****|";
	if (modeSelect == '2')
		cout << "|***AVTOMATSKI NACIN 2***|";
	cout << "\n|                        |\n";
	cout <<	"|========================|\n\n\n";
	cout << "Zelene vrednosti:\n" << targetTemp << "°C, " << targetRelativeHumidity << "%, " << targetIllumination << "lx\n\n";
	cout << "Intervali:\n" << tempRange[0] << '-' << tempRange[1] << "°C, " << relativeHumidityRange[0] << '-' << relativeHumidityRange[1] << "%, " << illuminationRange[0] << '-' << illuminationRange[1] << "lx\n\n";

	if (modeSelect == '2') {
		cout << "Vnesite stevilo meritev:\n";
		cin >> iterations;
		cout << "\nVnesite casovni razmik med meritvami [ms]:";
		cin >> delay;
	}

	cout << "Temperatura| Vlaznost |Osvetljenost|       Odstopanja       |  Ukazi  \n";



	//============ AVTOMATSKI NACIN 1 & 2
	double long avgTemp = 0, avgHumidity = 0, avgIllumination = 0, avgDTemp = 0, avgDHumidity = 0, avgDIllumination = 0;


	srand(time(NULL));
	for (int t = 0; i < iterations; i++) {


		temp = rand() % (tempRange[1] - tempRange[0] + 1) + tempRange[0];															// random number generation for input values
		humidity = rand() % (relativeHumidityRange[1] - relativeHumidityRange[0] + 1) + relativeHumidityRange[0];
		illumination = rand() % (illuminationRange[1] - illuminationRange[0] + 1) + illuminationRange[0];


		//======resets the values of the previous comparisons

		for (int j = 0; j < 3; j++)
			comparisonResult[j] = 0;


		//================== compares stuff

		dTemp = temp - targetTemp;


		if (temp < targetTemp) {
			comparisonResult[0] = 1;
			if (dTemp > 10)
				humidity -= 5;

		}
		else if (temp > targetTemp) {
			comparisonResult[0] = 2;
			if (dTemp > 10)
				humidity += 5;
		}

		dHumidity = humidity - targetRelativeHumidity;
		dIllumination = illumination - targetIllumination;

		if (humidity < targetRelativeHumidity)
			comparisonResult[1] = 1;
		else if (humidity > targetRelativeHumidity)
			comparisonResult[1] = 2;

		if (illumination < targetIllumination) {
			if (illumination <= 100)
				comparisonResult[2] = 1;
			else
				comparisonResult[2] = 2;
		}

		else if (illumination > targetIllumination) {
			if (illumination >= 8000)
				comparisonResult[2] = 4;
			else
				comparisonResult[2] = 3;
		}





		//========================================================== a fuckton of couts

		cout << "......." << temp << "°C|......." << humidity << "%|.....";
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
		if ((dHumidity < 10) && (dHumidity > -10))
			cout << '.';
		if (dHumidity >= 0)
			cout << '+';

		cout << dHumidity << "%|.";
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

		//=============AVERAGING STUFF=============================
		avgTemp += temp;
		avgHumidity += humidity;
		avgIllumination += illumination;
		avgDTemp += abs(dTemp);
		avgDHumidity += abs(dHumidity);
		avgDIllumination += abs(dIllumination);

		if (i == (iterations - 1)) {
			avgTemp = avgTemp/iterations;
			avgHumidity = avgHumidity/iterations;
			avgIllumination = avgIllumination/iterations;
			avgDTemp = avgDTemp/iterations;
			avgDHumidity = avgDHumidity/iterations;
			avgDIllumination = avgDIllumination/iterations;

			cout << "\nPovprecna temperatura: " << avgTemp << "°C, Povprecno odstopanje: +/-" << avgDTemp << "°C.\n";
			cout << "Povprecna vlaznost: " << avgHumidity << "%, Povprecno odstopanje: +/-" << avgDHumidity << "%.\n";
			cout << "Povprecna osvetljenost " << avgIllumination << "lx, Povprecno odstopanje: +/-" << avgDIllumination << "lx.\n";
			//cout << "\n" << avgTemp << "\n" << avgHumidity << "\n" << avgIllumination << "\n" << avgDTemp << "\n" << avgDHumidity << "\n" << avgDIllumination;
		}

		//=========================================================
		if (delay) {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}

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
