#include <cstdlib>
#include <iostream>
#include "list.h"

using namespace std;

List::List() {
	head = NULL;
	curr = NULL;
	temp = NULL;
}

void List::AddNode(int addData) {
	nodePtr n = new node; //nodePtr n points to newly allocated node
	n->next = NULL; //the next node doesnt exist, so point to null
	n->data = addData; //all nodes can hold a data value, and a pointer to next node

	if (head != NULL) { //if head points to something (basically if a list exists)
		curr = head; //then current node is pointing to the head of the list

		while (curr->next != NULL) { //while we're not at the end of the list
			curr = curr->next;  //traverse linked list until we are at the end
		}

		curr->next = n; //adding node n to the end of the list
	}
	else
	{
		head = n; //if we dont have a list, then the new node is the head
	}
}

int List::DeleteNode(int delData) {
	nodePtr delPtr = NULL;
	temp = head; //starting from the beginning of the list
	curr = head; // ^^

	while ((curr != NULL) & (curr->data !=delData)) { //while the current node isn't null, and while the current node's data isnt the data we want to delete
		temp = curr; //when the while loop ends, temp is set to the node before the one that is gonna be deleted
		curr = curr->next; //the current node is then shifted over to the node that's to be deleted.
	}
	if (curr == NULL) { //this is if the node to be deleted wasn't found
		//cout << delData << " was not in the list. \n";
		return -1;
		//delete delPtr; //save memory by deleting this, it wasnt found anyway.
	}
	else {
		delPtr = curr; //pointing delPtr to the node thats gonna be deleted
		curr = curr->next; //shifting to the next node in the list (the node after the deleted node)
		temp->next = curr; //temp is already set to the node before the deleted node. temp->next patches up the hole, as it now points to the node AFTER the deleted node.
		delete delPtr; //now we finally delete the node. The linked list is already patched up.

		return delData;
		//cout << "The value " << delData << " was deleted. \n";
	}
}

void List::PrintList() {
	curr = head;
	while (curr != NULL) {
		cout << curr->data << endl;
		curr = curr->next;
	}
}