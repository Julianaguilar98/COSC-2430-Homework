#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
	string pName;
	string pPosition;
	string pJerseyNum;
	Node *next;
};

//function to add a node to the list and all the players info
void append(Node *h, string n, string p, string j) {
	Node *temp = new Node;
	Node *last = h;
	temp->pName = n;
	temp->pPosition = p;
	temp->pJerseyNum = j;

	temp->next = NULL;
	if (h == NULL) {
		h = temp;
		return;
	}
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = temp;
	return;
}

//search functions iterates through the linked list and gets the position
//by seeing how many times it has to iterate to find the name
void search(Node *h, string key) {
	int pos = 0;
	Node *temp = h;
	while (temp != NULL) {
		if (temp->pName == key) {
			cout << pos;
			return;
		}
		++pos;
		temp = temp->next;
	}
	pos = -1;
	cout << pos;
	return;
}

//print list isnt needed, just needed to see if i was getting the input
void printList(Node *n) {
	while (n != NULL) {
		cout << n->pName << " " << n->pJerseyNum << " " << n->pPosition << endl;
		n = n->next;
	}
}


int main() {
	ifstream input("input11.txt");
	ifstream command("command11.txt");
	ofstream output("out1.txt");

	if (input.fail()) {
		cout << "Failed to open input file";
		exit(1);
	}
	if (command.fail()) {
		cout << "Failed to open command file";
		exit(1);
	}
	if (output.fail()) {
		cout << "Failed to open output file";
		exit(1);
	}

	string name, position, jerseyNum, line;
	Node *head = new Node;
	head ->next = NULL;

	cout << "These names are from reading the input" << endl;
	//This while loops separates("Parses") the info into variables and adds each player to the linked list
	while (getline(input, line)) {
		istringstream ss(line);
		getline(ss, name, ',');
		getline(ss, jerseyNum, ',');
		jerseyNum.erase(0, 1);
		getline(ss, position);
		position.erase(0, 1);
		cout << name << " " << jerseyNum << " " << position << " " << endl; //cout all players

		append(head, name, position, jerseyNum); //this function creates the node
	}
	cout << endl;
	cout << "These names are printed from the linked list" << endl;
	printList(head); //cout players through linked list

	cout << endl;
	cout << "This is the answer output" << endl;
	while (getline(command, line)) { //gets the output for final answer
		cout << line << ": ";
		search(head, line);
		cout << endl;
	}


	input.close();
	command.close();
	output.close();
	system("PAUSE");
	return 0;
}