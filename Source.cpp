#include <iostream>
#include "HashTable.h"
#include "ChainHashTable.h"
#include "Part.h"
#include "DoubleLinked.h"
#include "Exception.h"
#include <time.h>/* time */
/* initialize random seed: */

Part* partSetup() {
	string SKU;
	string Description;
	double Price;
	string UOM;
	int QOH;

	cout << "Enter the SKU (as an integer):" << endl;
	cin >> SKU;

	cout << "Enter the Description:" << endl;
	cin.ignore();
	getline(cin, Description);

	cout << "Enter Price (as a double):" << endl;
	cin >> Price;

	cout << "Enter Unit of Measure:" << endl;
	cin >> UOM;

	cout << "Enter Quantity on hand (int):" << endl;
	cin >> QOH;

	Part* myPart = new Part(SKU, Description, Price, UOM, QOH);
	return myPart;
}

int main() {

	srand(time(NULL));

	HashTable<Part> PartTable;
	ChainHashTable<Part> ChainedPartTable;

	int sel = 0;
	bool quit = false;
	int numInputs = 50;

	do {
		//////////////////////////////////////////////////////////////////////////////////
		// Commented out Below is the code used for testing inserting 50 data points in different sized tables
		//////////////////////////////////////////////////////////////////////////////////
		/*
			int randNum;
			for (int i = 0; i < numInputs; i++) {
				randNum = rand() % 100 + 1;
				cout << "SKU Number: " << randNum << endl;
				Part* newPart = new Part(to_string(randNum));
				try {
					PartTable.InsertItem(newPart);
					ChainedPartTable.InsertItem(newPart);
				}
				catch (Exception e) {
					e.printError();
				}
				try {
					if (PartTable.GetItem(newPart) != nullptr) {
						cout << "Trial: " << i << " --Successfully Got item from Hash Table.--" << endl;
					}
					else {
						cout << "Trial: " << i << " --Item not found in Linear Hash Table--" << endl;
					}
					if (ChainedPartTable.GetItem(newPart) != nullptr) {
						cout << "Trial: " << i << " --Successfully Got item from Chained Hash Table.--" << endl;
					}
					else {
						cout << "Trial: " << i << " --Item not found in Chained Hash Table--" << endl;
					}
				}
				catch (Exception e) {
					e.printError();
				}

		  cout << "\n --Number of comparisons-- \n" << endl << "Linear Probing: " << PartTable.compCount << endl;
				cout << "Chained Hashing: " << ChainedPartTable.chainCompCount << endl;
			}
			quit = true;
		*/
		do {
			cout << "Main Menu:" << endl
				<< "\t 1 - Add Item" << endl
				<< "\t 2 - Get Item" << endl
				<< "\t 3 - Remove Item" << endl
				<< "\t 4 - Get Length" << endl
				<< "\t 5 - Quit" << endl;

			cout << "Enter your selection: " << endl;
			cin >> sel;
		} while ((sel < 1 || sel > 5));

		if (sel == 1) {
			try {
				Part* newPart = new Part();
				newPart = partSetup();
				PartTable.InsertItem(newPart);
				ChainedPartTable.InsertItem(newPart);
			}
			catch (Exception e) {
				e.printError();
			}
			cout << "--Successfully added item to both tables.--" << endl;
		}

		else if (sel == 2) {
			string sku;
			bool found = false;
			cout << "Enter SKU Number: " << endl;
			cin >> sku;
			Part* getPart = new Part(sku);
			try {
				if (PartTable.GetItem(getPart) != nullptr) {
					cout << "--Successfully Got item from Hash Table.--" << endl;
				}
				else {
					cout << "--Item not found in Linear Hash Table--" << endl;
				}
				if (ChainedPartTable.GetItem(getPart) != nullptr) {
					cout << "--Successfully Got item from Chained Hash Table.--" << endl;
				}
				else {
					cout << "--Item not found in Chained Hash Table--" << endl;
				}
			}
			catch (Exception e) {
				e.printError();
			}
		}
		else if (sel == 3) {
			string sku;
			cout << "Enter SKU Number: " << endl;
			cin >> sku;
			Part* removePart = new Part(sku);
			try {
				if (PartTable.RemoveItem(removePart) != nullptr) {
					cout << "--Successfully Removed item from Hash Table.--" << endl;
				}
				else {
					cout << "--Item not found in Linear Hash Table--" << endl;
				}
				if (ChainedPartTable.RemoveItem(removePart) != nullptr) {
					cout << "--Successfully Removed item from Chained Hash Table.--" << endl;
				}
				else {
					cout << "--Item not found in Chained Hash Table--" << endl;
				}
			}
			catch (Exception e) {
				e.printError();
			}
		}
		else if (sel == 4) {
			try {
				cout << "Hash table length: " << PartTable.GetLength() << endl;
				cout << "Chained Hash table length: " << ChainedPartTable.GetLength() << endl;
			}
			catch (Exception e) {
				e.printError();
			}
		}
		else if (sel == 5) {
			try {
				PartTable.~HashTable();
				ChainedPartTable.~ChainHashTable();
				cout << "Quitting..." << endl;
				quit = true;
				break;
			}
			catch (Exception e) {
				e.printError();
			}
		}
	} while (!quit);

}
