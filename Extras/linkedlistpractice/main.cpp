#include <iostream>
#include <cstdlib>
#include "list.h"

using namespace std;

int main(int argc, char** argv) {
	List Paul;
	Paul.AddNode(3);
	Paul.AddNode(5);
	Paul.AddNode(7);
	Paul.AddNode(9);
	Paul.AddNode(11);
	Paul.PrintList();

	cout << endl;

	cout << Paul.DeleteNode(6) << " was removed from the linked list. \n" << endl;

	Paul.PrintList();

	return 0;
}