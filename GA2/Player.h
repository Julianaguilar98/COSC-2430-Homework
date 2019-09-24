#include <iostream>
#include <cstdlib>
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player {
private:
	int number;
	int age;
	int minutes;
public:
	Player();
	Player(int num, int a);
	void setNumber(int num);
	void setAge(int a);
	void setMinutes(int min);
	virtual int getNumber();
	virtual int getAge();
	virtual int getMinutes();
};

Player::Player() {
	number = rand() % 100;
	age = rand() % 25 + 15;
	minutes = 0;
}
Player::Player(int num, int a) {
	number = num;
	age = a;
	minutes = 0;
}

void Player::setNumber(int num) {
	number = num;
}

void Player::setAge(int a) {
	age = a;
}

void Player::setMinutes(int min) {
	minutes += min;
}

int Player::getNumber() {
	return number;
}

int Player::getAge() {
	return age;
}

int Player::getMinutes() {
	return minutes;
}
#endif