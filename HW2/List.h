#pragma once
#include <string>
using namespace std;

struct node
{
	string firstWord;
	string lastWord;
	string sentence;
	node* next;
};

class List
{
private:
	node* head;
	node* tail;
	int size;
public:
	List() { head = tail = 0; size = 0; }

	void addToBeg(node* temp);
	void addToEnd(node* temp);
	void insertAtPos(node* temp, int pos);
	void delAtBeg();
	void delAtEnd();
	void delAtPos(int pos);

	int getSize();
	node* getNthNode(int n);
	void swap(int a, int b);
	void print();
};
