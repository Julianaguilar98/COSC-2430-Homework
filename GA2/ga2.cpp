#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "courtPlayer.h"
#include "benchPlayer.h"

using namespace std;

int main() {
	//x = (condition) ? (value_if_true) : (value_if_false);

	Player lockerRoom[12]; //array of Player objects ||| Each object is created using random numbers
	courtPlayer c;
	benchPlayer b;

	int a[5]; //This array holds the jersey number of the players on the court ||  NOT USED, JUST IN CASE
	float aa[5]; //This array holds the player age on the court || NOT USED, JUST IN CASE
	int n = 0, numb, ag;

	/*This array holds the position of the first 5 players that go into the court. Each number will be distinct*/
	int x = 0;
	int ind[5];
	srand(12);
	for (int i = 0; i < 5; i++) {
		x = rand() % 12;
		for (int d = 0; d < 5; d++) {
			if (x == ind[d]) {
				x = rand() % 12;
				break;
			}
		}
		ind[i] = x;
	}
	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/


	//This is supposed to make the court linked list by adding random players from the locker room
	int tem;
	for (int j = 0; j < 5; j++) {
		tem = ind[j]; // holds the first random player position

		numb = lockerRoom[tem].getNumber(); //gets player number
		ag = lockerRoom[tem].getAge(); //gets player age

		a[j] = numb;
		aa[j] = ag;

		cout << numb << "  " << ag << endl; //prints the info of the 5 court players
		c.createNode(numb, ag, 0);
	}

	/* Make a for loop that checks the number of the player.
	If the number is of a player on the court, then ignore and
	add the players whose number isnt in the array to the bench linked list*/
	for (int u = 0; u < 12; u++) {
		if (u == ind[0]) {
			continue;
		}
		else if (u == ind[1]) {
			continue;
		}
		else if (u == ind[2]) {
			continue;
		}
		else if (u == ind[3]) {
			continue;
		}
		else if (u == ind[4]) {
			continue;
		}
		else {
			b.createList(lockerRoom[u].getNumber(), lockerRoom[u].getAge(), 0);
		}
	}
	c.printList();
	c.sort();
	c.printList();

	int max = 0, pos = 0, maxNum, maxMin;
	int tNum, tAge, tMin;
	for (int f = 0; f < 48; f++) {
		c.updateMinutes();

		//finds max age
		pos = 0;
		court *t = new court;
		t = last->next;
		while (t != last) {
			if (t->age > max) {
				max = t->age;
				maxNum = t->number;
				maxMin = t->minutes;
			}
			else {
				t = t->next;
				pos++;
			}
		}
		if (t->age >= max) {
			max = t->age;
			maxNum = t->number;
			maxMin = t->minutes;
		}
		cout << pos << " ";
		cout << max << " " << maxNum << " " << maxMin << endl;

		bench *bb = new bench;
		bb = first;
		if (f >= max) {
			tNum = bb->next->number;
			tAge = bb->next->age;
			tMin = bb->next->minutes;
			c.createNode(tNum, tAge, tMin);
			b.createList(maxNum, max, maxMin);
			c.deleteElement(maxNum);
			b.deleteElement(tNum);
		}
	}

	/*court *s = new court;
	s = last->next;
	while (s != last)
	{
		cout << s->number << endl;
		s = s->next;
	}
	cout << s->number;*/


	system("PAUSE");
	return 0;
}
//References
//geeksforgeeks.com
//sanfoundry.com