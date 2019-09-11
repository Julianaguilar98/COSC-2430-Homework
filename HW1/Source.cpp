// 8/29/2019 Julian Aguilar COSC 2440 Dr. Rizk
//HW1
#include <string> 
#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;


int main(int argc, char * argv[]) {
	string input;
	string outfile;

//	ifstream DataIn;
	//ofstream DataOut;
	//cout << "Input File: ";
	ArgumentManager am(argc, argv);
	const string inputName = am.get("input");
	const string outputName = am.get("output");
	ifstream DataIn(inputName);
	ofstream DataOut(outputName);

	if (!DataIn.is_open()) { //Data validation
		return 1;
	}	

	int size;
	DataIn >> size;

	int** arr = new int* [size]; // Double pointer initialization

	for (int i = 0; i < size; i++) //Allocation
		arr[i] = new int[size];

	for (int i = 0; i < size; i++) { //Copying Data
		for (int j = 0; j < size; j++) {
			DataIn >> arr[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) { //Output
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	int flag = 0;
	int harv = 0;
	int rotten = 0;
	//inclose all this in a for loop for the 7 days

	for (int days = 0; days < 7; days++)
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {

				if (arr[i][j] >= 6) { //Counts how many ripe kiwis there are
					flag++;
				}
			}

			if (flag >= size / 2) { //If 50%+ , count and replant
				for (int k = 0; k < size; k++) {
					if ((arr[i][k] >= 6) && (arr[i][k] <= 8)) {
						harv++;
					}
					else if (arr[i][k] > 8) { 
						rotten++;
					}
				}
				for (int s = 0; s < size; s++) {
					arr[i][s] = 0;
				}
			}
			else {
				for (int g = 0; g < size; g++) {
					arr[i][g]++;
				}
			}

			flag = 0; //reset flag to 0 for the next day
		}
	}
	//this last bit is just for the final night
	
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {

			if (arr[i][j] >= 6) {
				flag++;
			}
		}


		for (int k = 0; k < size; k++)
		{
			if (flag >= size / 2) {
				for (int k = 0; k < size; k++) {
					if ((arr[i][k] >= 6) && (arr[i][k] <= 8)) {
						harv++;
					}
					else if (arr[i][k] > 8) {
						rotten++;
					}
				}
				for (int s = 0; s < size; s++) {
					arr[i][s] = 0;
				}
			}
		}
		flag = 0;
	}
	
//Print
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	/* myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();*/

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			DataOut << arr[i][j] << " ";
		}
		DataOut << endl;
	}
	
	DataOut << "Harvested kiwis: " << harv << endl;
	DataOut << "Rotten kiwis: " << rotten << endl;
	cout << "Harvested kiwis: " << harv << endl;
	cout << "Rotten kiwis: " << rotten << endl;

	DataIn.close();
	DataOut.close();
}