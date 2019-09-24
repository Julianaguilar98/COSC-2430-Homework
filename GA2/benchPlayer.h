#include <iostream>
#include "Player.h"
#ifndef benchPLAYER_H
#define benchPLAYER_H

struct bench {
	int number;
	int age;
	int minutes;
	struct bench* next;		//pointer to next node
	struct bench* prev;		//pointer to previous node
}*first; //first == start

class benchPlayer : public Player {
public:
	benchPlayer();
	char status = 'B';
	void createList(int num, int a, int min);
	void addBegin(int num, int a, int min);
	void addAfter(int num, int a, int min, int pos);
	void deleteElement(int num);
	void printList();
};

benchPlayer::benchPlayer() {
	first = NULL;
}

void benchPlayer::createList(int num, int a, int min){
	struct bench *s, *temp;
	temp = new bench;
	temp->number = num;
	temp->age = a;
	temp->minutes = min;
	temp->next = NULL;
	if (first == NULL){
		temp->prev = NULL;
		first = temp;
	}
	else{
		s = first;
		while (s->next != NULL) {
			s = s->next;
		}
		s->next = temp;
		temp->prev = s;
	}
}

void benchPlayer::addBegin(int num, int a, int min) {
	if (first == NULL)
	{
		cout << "First Create the list." << endl;
		return;
	}
	struct bench *temp;
	temp = new bench;
	temp->prev = NULL;
	temp->number = num;
	temp->age = a;
	temp->minutes = min;
	temp->next = first;
	first->prev = temp;
	first = temp;
	cout << "Element Inserted" << endl;
}

void benchPlayer::addAfter(int num, int a, int min, int pos) {
	if (first == NULL)
	{
		cout << "First Create the list." << endl;
		return;
	}
	struct bench *tmp, *q;
	int i;
	q = first;
	for (i = 0; i < pos - 1; i++)
	{
		q = q->next;
		if (q == NULL)
		{
			cout << "There are less than ";
			cout << pos << " elements." << endl;
			return;
		}
	}
	tmp = new bench;
	tmp->number = num;
	tmp->age = a;
	tmp->minutes = min;
	if (q->next == NULL)
	{
		q->next = tmp;
		tmp->next = NULL;
		tmp->prev = q;
	}
	else
	{
		tmp->next = q->next;
		tmp->next->prev = tmp;
		q->next = tmp;
		tmp->prev = q;
	}
	cout << "Element Inserted" << endl;
}

void benchPlayer::deleteElement(int num) {
	struct bench *tmp, *q;
	/*first element deletion*/
	if (first->number == num)
	{
		tmp = first;
		first = first->next;
		first->prev = NULL;
		cout << "Element Deleted" << endl;
		free(tmp);
		return;
	}
	q = first;
	while (q->next->next != NULL)
	{
		/*Element deleted in between*/
		if (q->next->number == num)
		{
			tmp = q->next;
			q->next = tmp->next;
			tmp->next->prev = q;
			cout << "Element Deleted" << endl;
			free(tmp);
			return;
		}
		q = q->next;
	}
	/*last element deleted*/
	if (q->next->number == num)
	{
		tmp = q->next;
		free(tmp);
		q->next = NULL;
		cout << "Element Deleted" << endl;
		return;
	}
	cout << "Element " << num << " not found" << endl;
}

void benchPlayer::printList() {
	struct bench *q;
	if (first == NULL)
	{
		cout << "List empty,nothing to display" << endl;
		return;
	}
	q = first;
	cout << "The Doubly Link List is :" << endl;
	while (q != NULL)
	{
		cout << q->number << " <-> ";
		q = q->next;
	}
	cout << "NULL" << endl;
}

#endif