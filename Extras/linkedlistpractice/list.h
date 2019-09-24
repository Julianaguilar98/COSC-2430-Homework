#pragma once
#ifndef LIST_H
#define LIST_H
#include <cstdlib>
#include <iostream>
using namespace std;

class List {
private:
	//creating struct for node (struct by default is public)
	typedef struct node {
		int data;
		node* next;
	} *nodePtr;

	nodePtr head; //first item in list
	nodePtr curr; //current item in list
	nodePtr temp;

public: //putting functions here
	List();
	void AddNode(int addData);
	int DeleteNode(int delData);
	void PrintList();
};

#endif