#include <iostream>
#include "List.h"
using namespace std;

void List::addToBeg(node* temp)
{
	if (size == 0)
		head = tail = temp;
	else
	{
		temp->next = head;
		head = temp;
	}
	
	size += 1;
}

void List::addToEnd(node* temp)
{
	if (size == 0)
		head = tail = temp;
	else
	{
		tail->next = temp;
		tail = temp;
	}

	size += 1;
}

void List::insertAtPos(node* temp, int pos)
{
	if (size == 0)
		addToBeg(temp);
	else if (pos == size)
		addToEnd(temp);
	else if (pos >= 1 && pos <= size - 1)
	{
		node* cu = head;
		node* pcu = 0;
		for (int i = 0; i < pos; i++)
		{
			pcu = cu;
			cu = cu->next;
		}
		
		pcu->next = temp;
		temp->next = cu;

		size += 1;
	}
}

void List::delAtBeg()
{
	if (size == 0)
		return;
	else if (size == 1)
	{
		delete head;
		head = tail = 0;
	}
	else
	{
		node* cu = head;
		head = head->next;
		delete cu;
	}

	size -= 1;
}

void List::delAtEnd()
{
	if (size == 0)
		return;
	else if (size == 1)
	{
		delete tail;
		head = tail = 0;
	}
	else
	{
		node* cu = head;
		for (int i = 0; i < size - 1; i++)
			cu = cu->next;

		delete tail;
		tail = cu;
	}

	size -= 1;
}

void List::delAtPos(int pos)
{
	if (pos == 0)
		delAtBeg();
	else if (pos == size - 1)
		delAtEnd();
	else if (pos >= 1 && pos <= size - 2)
	{
		node* cu = head;
		node* pcu = 0;
		for (int i = 0; i < pos; i++)
		{
			pcu = cu;
			cu = cu->next;
		}
		
		pcu->next = cu->next;
		delete cu;

		size -= 1;
	}

	size -= 1;
}

int List::getSize()
{
	return size;
}

node* List::getNthNode(int n)
{
	if (n < 0 || n >= size)
		return nullptr;

	node* cu = head;
	for (int i = 0; i < n; i++)
		cu = cu->next;

	return cu;
}

void List::print()
{
	node* cu = head;
	for (int i = 0; i < size; i++)
	{
		cout << cu->sentence << endl;
		cout << cu->firstWord << " " << cu->lastWord << endl;
		cu = cu->next;
	}
	cout << endl;
}

void List::swap(int a, int b)
{

	// If a or b is out of bounds then don't do anything.
	if (a == b || a < 0 || a >= size || b < 0 || b >= size)
		return;

	node* apcu = nullptr;
	node* acu = head;
	node* bpcu = nullptr;
	node* bcu = head;

	// Get node at a'th position
	for (int i = 0; i < a; i++)
	{
		apcu = acu;
		acu = acu->next;
	}

	// Get node at b'th position
	for (int i = 0; i < b; i++)
	{
		bpcu = bcu;
		bcu = bcu->next;
	}

	// If a'th position is head, set head to b, else normal swap.
	if (apcu == nullptr)
		head = bcu;
	else
		apcu->next = bcu;

	// If b'th position is head, set head to a, else normal swap.
	if (bpcu == nullptr)
		head = acu;
	else
		bpcu->next = acu;

	// Swap forward nodes.
	node* temp = nullptr;
	temp = acu->next;
	acu->next = bcu->next;
	bcu->next = temp;
}
