#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int* readFromFile(int* pNumber) {
	const string expectedLine[6] = { "TEMPERATURA: " ,"VLAZNOST: ","OSVETLJENOST: " , "INTERVAL TEMPERATURE: [", "STOPNJA VLAZNOSTI: [", "INTERVAL OSVETLJENOSTI: [" };
	string line, str;
	//int number[9];
	int i = 0;
	

	ifstream infile("csupp_config.txt");																							//open file
	if (infile.is_open())
	{
		while (getline(infile, line))																								//for each line
		{
			str = line.substr(0, expectedLine[i].length());
			if (str == expectedLine[i]) {																							//if the start of the string is correct
				*pNumber = stoi(line.substr(expectedLine[i].length(), (expectedLine[i].length() + 1)), 0, 10);						//stores the number in the string
				pNumber++;

				if (i > 2) {																										//if we should have two numbers per line
					*pNumber = stoi(line.substr((expectedLine[i].length() + 4), (expectedLine[i].length() + 1)), 0, 10);			//then it stored the second one as well
					pNumber++;
				}
			}
			else {
				cout << "Invalid input file\n";																						//error if the line doesn't match TODO: implement more than just a message
				break;
			}
			i++;
		}
		infile.close();
	}
	else cout << "Unable to open file";
	return 0;
}

int displayHelp() {
	string line;
	ifstream infile("readme.txt");
	if (infile.is_open()) {
		while (getline(infile, line)) {
			cout << line << '\n';
		}
		infile.close();
	}
	else return 1;
	return 0;
}

float tempCtoF(float temp){
	return temp * (9 / 5) + 32;
}

float tempCtoK(float temp) {
	return temp + 273.15;
}

float tempCtoR(float temp) {
	return (temp + 273.15) * 9 / 5;
}

float tempCtoDe(float temp) {
	return (100 - temp) * (3 / 2);
}

float tempCtoN(float temp) {
	return temp * (33 / 100);
}

float tempCtoRe(float temp) {
	return temp * (4 / 5);
}

float tempCtoRo(float temp) {
	return temp * (21 / 40) + 7.5;
}

float tempFtoC(float temp) {
	return (temp - 32) * (5 / 9);
}

float tempFtoK(float temp) {
	return (temp + 459.67) * (5 / 9);
}

float tempFtoR(float temp) {
	return temp + 459.67;
}

float tempFtoDe(float temp) {
	return (212 - temp) * (5 / 6);
}

float tempFtoN(float temp) {
	return (temp - 32) * (11 / 60);
}

float tempFtoRe(float temp) {
	return (temp - 32) * 4 / 9;
}

float tempFtoRo(float temp) {
	return (temp - 32) * (7 / 24) + 7.5;
}

float tempKtoC(float temp) {
	return temp - 273.15;
}

float tempKtoF(float temp) {
	return temp * (9 / 5) - 459.67;
}

float tempKtoR(float temp) {
	return temp * (9 / 5);
}

float tempKtoDe(float temp) {
	return (373.15 - temp) * (3 / 2);
}

float tempKtoN(float temp) {
	return (temp - 273.15) * (33 / 100);
}

float tempKtoRe(float temp) {
	return (temp - 273.15) * (4 / 5);
}

float tempKtoRo(float temp) {
	return (temp - 273.15) * (21 / 40) * 7.5;
}