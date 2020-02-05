#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"
#include "List.h"
using namespace std;

string verify(string sToVerify);
List* readIntoList(ifstream& infile);

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);
	const string inputName = am.get("input");
	const string outputName = am.get("output");

	ifstream infile(inputName);
	ofstream outfile(outputName);

	List* foo = readIntoList(infile);
	node* cu;
	node* temp;
	bool found = false;
	int i, j;

	// Find the first sentence.
	for (i = 0; i < foo->getSize(); i++)
	{
		cu = foo->getNthNode(0);
		temp = foo->getNthNode(i);

		for (j = 0; j < foo->getSize(); j++)
		{
			if (temp->firstWord == cu->lastWord)
			{
				found = true;
				break;
			}
			cu = cu->next;
		}

		if (!found)
		{
			foo->swap(0, i);
			break;
		}
			
		found = false;
		temp = temp->next;
	}

	// Find the next sentence.
	for (i = 0; i < foo->getSize() - 1; i++)
	{
		cu = foo->getNthNode(i);

		for (j = i + 1; j < foo->getSize(); j++)
		{
			temp = foo->getNthNode(j);

			if (cu->lastWord == temp->firstWord)
			{
				foo->swap(i + 1, j);
				break;
			}
		}
	}

	cu = foo->getNthNode(0);
	// Write sentences into outfile.
	for (i = 0; i < foo->getSize(); i++)
	{
		outfile << cu->sentence << "\n";
		cu = cu->next;
	}

	infile.close();
	outfile.close();

	system("PAUSE");
	return 0;
}

string verify(string sToVerify)
{
	string temp;

	for (int i = 0; i < sToVerify.length(); i++)
	{
		if (isalpha(sToVerify[i]))
		{
			sToVerify[i] = tolower(sToVerify[i]);
			temp += sToVerify[i];
		}
	}

	return temp;
}

List* readIntoList(ifstream& infile)
{
	List* var = new List;
	node* newNode;
	string temp;

	while (getline(infile, temp))
	{
		newNode = new node;
		istringstream iss(temp);

		// Load temp variable into sentence.
		newNode->sentence = temp;

		// Load first word into node variable.
		iss >> temp;
		temp = verify(temp);
		newNode->firstWord = temp;

		// Get last word, then load into node variable.
		while (!iss.eof())
			iss >> temp;

		temp = verify(temp);
		newNode->lastWord = temp;

		var->addToBeg(newNode);
	}

	return var;
}
