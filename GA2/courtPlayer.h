#include <iostream>
#include "Player.h"
#ifndef courtPLAYER_H
#define courtPLAYER_H

struct court {
	int number;
	int age;
	int minutes;
	struct court *next;
}*last;

class courtPlayer : public Player {
public:
	char status;
	courtPlayer();
	void printList2();
	void printList3();
	void createNode(int num, int a, int min);
	void addBegin(int num, int a, int min);
	void addAfter(int num, int a, int min, int pos);
	void deleteElement(int num);
	void searchElement(int num);
	void sort();
	void updateMinutes();
};

courtPlayer::courtPlayer() {
	status = 'C';
	last = NULL;
}

void courtPlayer::createNode(int num, int a, int min) {
	struct court *temp;
	temp = new court;
	temp->number = num;
	temp->age = a;
	temp->minutes = min;
	if (last == NULL) {
		last = temp;
		temp->next = last;
	}
	else {
		temp->next = last->next;
		last->next = temp;
		last = temp;
	}
}

void courtPlayer::addBegin(int num, int a, int min) {
	if (last == NULL) {
		cout << "First create the list" << endl;
		return;
	}
	struct court *temp = new court;
	temp->number = num;
	temp->age = a;
	temp->minutes = min;
	temp->next = last->next;
	last->next = temp;
}

void courtPlayer::addAfter(int num, int a, int min, int pos) {
	if (last == NULL) {
		cout << "First create the list" << endl;
		return;
	}
	struct court *temp, *s;
	s = last->next;
	for (int i = 0; i < pos - 1; i++){
		s = s->next;
		if (s == last->next){
			cout << "There are less than ";
			cout << pos << " in the list" << endl;
			return;
		}
	}
	temp = new court;
	temp->next = s->next;
	temp->number = num;
	temp->age = a;
	temp->minutes = min;
	s->next = temp;
	if (s == last) {
		last = temp;
	}
}

void courtPlayer::deleteElement(int num) {
	struct court *temp, *s;
	s = last->next;
	if (last->next == last && last->number == num){
		temp = last;
		last = NULL;
		free(temp);
		return;
	}
	if (s->number == num){
		temp = s;
		last->next = s->next;
		free(temp);
		return;
	}
	while (s->next != last){
		if (s->next->number == num){
			temp = s->next;
			s->next = temp->next;
			free(temp);
			return;
		}
		s = s->next;
	}
	if (s->next->number == num){
		temp = s->next;
		s->next = last->next;
		free(temp);
		last = s;
		return;
	}
	cout << "Element " << num << " not found in the list" << endl;
}

void courtPlayer::searchElement(int num) {
	struct court *s;
	int counter = 0;
	s = last->next;
	while (s != last){
		counter++;
		if (s->number == num)
		{
			cout << "Element " << num;
			cout << " found at position " << counter << endl;
			return;
		}
		s = s->next;
	}
	if (s->number == num)
	{
		counter++;
		cout << "Element " << num;
		cout << " found at position " << counter << endl;
		return;
	}
	cout << "Element " << num << " not found in the list" << endl;
}

void courtPlayer::printList2() {
	struct court *s;
	if (last == NULL)
	{
		cout << "List is empty, nothing to display" << endl;
		return;
	}
	s = last->next;
	cout << "Age  Number" << endl;
	while (s != last)
	{
		cout << s->number << "       " << s->minutes << endl;
		s = s->next;
	}
	cout << s->number << "       " << s->minutes << endl;
}

void courtPlayer::printList3() {
	struct court *s;
	if (last == NULL)
	{
		cout << "List is empty, nothing to display" << endl;
		return;
	}
	s = last->next;
	cout << "Age  Number  Minutesplayed " << endl;
	while (s != last)
	{
		cout << s->age << "        " << s->number << "               " << s->minutes << endl;
		s = s->next;
	}
	cout << s->age << "        " << s->number << "               " << s->minutes << endl;
}

void courtPlayer::sort() {
	struct court *s, *ptr;
	int tempN, tempA, tempM;
	if (last == NULL)
	{
		cout << "List is empty, nothing to sort" << endl;
		return;
	}
	s = last->next;
	while (s != last)
	{
		ptr = s->next;
		while (ptr != last->next)
		{
			if (ptr != last->next)
			{
				if (s->number > ptr->number)
				{
					tempN = s->number;
					tempA = s->age;
					tempM = s->minutes;
					s->number = ptr->number;
					s->age = ptr->age;
					s->minutes = ptr->minutes;
					ptr->number = tempN;
					ptr->age = tempA;
					ptr->minutes = tempM;
				}
			}
			else
			{
				break;
			}
			ptr = ptr->next;
		}
		s = s->next;
	}
}

void courtPlayer::updateMinutes() {
	struct court *s;
	if (last == NULL)
	{
		cout << "List is empty, nothing to display" << endl;
		return;
	}
	s = last->next;
	while (s != last)
	{
		s->minutes += 1;
		s = s->next;
	}
	s->minutes += 1;
}
#endif