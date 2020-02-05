// bTree class.
// Insert functions are heavily inspired by GeeksForGeeks.

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

struct BTreeNode
{
	int* keys; // data within node
	int degree; //how many pointers are in the array 
	BTreeNode** children; //array of pointers pointing to the children nodes
	int n;	// Number of keys in array
	bool leaf; //whether it's a bottom node or not
public:
	BTreeNode(int _degree, bool _leaf)
	{
		degree = _degree;
		leaf = _leaf;
		n = 0;

		// Reason for bigger size is so to make splitting nodes easier.
		keys = new int[degree];
		children = new BTreeNode * [(int)degree + 1];

		for (int i = 0; i < degree + 1; i++)
			children[i] = nullptr;
	}

	// A utility function that returns whether this node if full or not.
	bool isFull()
	{
		return (n == degree - 1);
	}

	// A utility function to determine if the node is overflowed. If so, you need to split the node.
	bool isSuperFull()
	{
		return (n == degree);
	}

	// A utility function to insert a new key in this node 
	// The assumption is, the node must be non-full when this 
	// function is called 
	void insertNonFull(int k)
	{
		// Initialize index as index of rightmost element.
		int i = n - 1;

		// If this is a leaf node...
		if (leaf == true)
		{
			// If there is a duplicate key, exit out of the insertion functions and don't do anything.
			for (int j = 0; j < n; j++)
				if (keys[j] == k)
					return;

			// Places value k in the correct place within the key array.
			while (i >= 0 && keys[i] >= k)
			{
				keys[i + 1] = keys[i];
				i--;
			}

			// Insert the new key at found location.
			keys[i + 1] = k;
			n = n + 1;
		}
		else
		{
			// Find the child which is going to have the new key.
			while (i >= 0 && keys[i] >= k)
			{
				// If there is a duplicate key, exit out of the insertion functions and don't do anything.
				if (keys[i] == k)
					return;

				i--;
			}

			children[i + 1]->insertNonFull(k);

			if (children[i + 1]->isSuperFull())
				splitChild(i + 1);

		}
	}

	// A utility function to split the child y of this node 
	// Note that children[y] must be full when this function is called 
	void splitChild(int y)
	{
		BTreeNode* toBeSplit = children[y];
		BTreeNode* left = new BTreeNode(degree, toBeSplit->leaf);
		BTreeNode* right = new BTreeNode(degree, toBeSplit->leaf);
		int i, midpoint, keyPushedUp;

		// Set the midpoint of the array. Midpoint calculations differ whether degree is even or odd.
		midpoint = (degree % 2 == 0) ? (degree / 2) - 1 : degree / 2;
		keyPushedUp = toBeSplit->keys[midpoint];

		// Copy left side of node y's keys to left node.
		for (i = 0; i < midpoint; i++)
			left->keys[i] = toBeSplit->keys[i];

		// Copy right side of node y's keys to right node.
		for (i = midpoint + 1; i < degree; i++)
			right->keys[i - (midpoint + 1)] = toBeSplit->keys[i];

		// Copy left side of node y's children to left node.
		for (i = 0; i < midpoint + 1; i++)
			left->children[i] = toBeSplit->children[i];

		// Copy right side of node y's children to right node.
		for (i = midpoint + 1; i < degree + 1; i++)
			right->children[i - (midpoint + 1)] = toBeSplit->children[i];


		// Find index to place key and left and right nodes in.
		i = n - 1;
		while (i >= 0 && keyPushedUp < keys[i])
		{
			keys[i + 1] = keys[i];
			children[i + 2] = children[i + 1];
			i--;
		}

		// Set keys and children in the right locations.
		keys[i + 1] = keyPushedUp;
		children[i + 1] = left;
		children[i + 2] = right;

		// Update node sizes for left node, right node, and this node.
		left->n = midpoint;
		right->n = degree / 2;
		n += 1;
	}

	// Prints the data of the node sequentially.
	void print()
	{
		for (int i = 0; i < n; i++)
			cout << keys[i] << " ";
		cout << endl;
	}
};

class BTree
{
private:
	BTreeNode* root;
	int maxDegree, maxLevel;
public:
	BTree(int degree)
	{
		root = nullptr;
		maxDegree = degree;
		maxLevel = 0;
	}

	void traversal(ofstream& outFile) { traversal(outFile, root); outFile << endl; }
	BTreeNode* search(int k) { return search(root, k); }
	void printLevel(ofstream& outFile, int desiredLevel) { printLevel(outFile, root, desiredLevel); outFile << endl; }
	int getLevel() { return maxLevel; }

	void traversal(ofstream& outFile, BTreeNode* node)
	{
		if (node == nullptr)
			return;

		int i;
		for (i = 0; i < node->n; i++)
		{
			traversal(outFile, node->children[i]);
			outFile << node->keys[i] << " ";
		}

		traversal(outFile, node->children[i]);
	}

	BTreeNode* search(BTreeNode* base, int k)
	{
		int i = 0;
		while (i < base->n && k < base->keys[i])
			i++;

		if (base->keys[i] == k)
			return base;

		if (base->leaf == true)
			return nullptr;

		return search(base->children[i], k);
	}

	void insert(int k)
	{
		// If the tree is empty...
		if (root == nullptr)
		{
			root = new BTreeNode(maxDegree, true);	// Create new node.
			root->keys[0] = k;	// Insert k to root node.
			root->n = 1;	// Increment n by one.
			maxLevel = 1;	// Set the max level of tree to one.
		}
		// If tree not empty...
		else
		{
			// If root is full and is a leaf...
			if (root->isFull() && root->leaf)
			{
				// Create a the new root.
				BTreeNode* newRoot = new BTreeNode(maxDegree, false);
				newRoot->children[0] = root;

				// Insert value k into root.
				int i = root->n - 1;
				while (i >= 0 && k < root->keys[i])
				{
					root->keys[i + 1] = root->keys[i];
					i--;
				}
				root->keys[i + 1] = k;
				root->n += 1;

				// Set the root and update size.
				root = newRoot;

				// Split the old root to two nodes.
				root->splitChild(0);

				// Tree grows upwards, gaining an extra level.
				maxLevel += 1;
			}
			// If root not full...
			else
			{
				root->insertNonFull(k);

				// If the root gets full, split the root and extend the tree upward.
				if (root->isSuperFull())
				{
					BTreeNode* newRoot = new BTreeNode(maxDegree, false);
					newRoot->children[0] = root;
					root = newRoot;

					// Split the old root to two nodes.
					root->splitChild(0);

					// Tree grows upwards, gaining an extra level.
					maxLevel += 1;
				}
			}
		}
	}

	void printLevel(ofstream& outFile, BTreeNode* base, int desiredLevel, int level = 1)
	{
		if (base == nullptr)
		{
			return;
		}

		int i;
		if (level == desiredLevel)
		{
			for (i = 0; i < base->n; i++)
				outFile << base->keys[i] << " ";
		}

		else
		{
			level += 1;
			for (i = 0; i < maxDegree; i++)
				printLevel(outFile, base->children[i], desiredLevel, level);
		}
	}

	void printAll(ofstream& outFile)
	{
		for (int i = 1; i <= maxLevel; i++)
		{
			outFile << "Level " << i << ": ";
			printLevel(outFile, i);
		}
	}

};

int getDigitsFromString(string str)
{
	string temp;

	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]))
			temp += str[i];

	return stoi(temp);
}

int main(int argc, char* argv[])
{
	ArgumentManager am(argc, argv);

	const string in = am.get("input");
	const string com = am.get("command");
	const string out = am.get("output");

	int val, opt, degree;
	string temp, temp2;
	char c;

	ifstream inFileInput(in);
	ifstream inFileCom(com);
	ofstream outFile(out);

	// Get the degrees of the b-Tree.
	getline(inFileCom, temp);
	val = getDigitsFromString(temp);

	BTree* bTree = new BTree(val);

	while (!inFileInput.eof())
	{
		inFileInput >> val;
		bTree->insert(val);
	}

	while (getline(inFileCom, temp))
	{
		if (temp[0] == 'I')
		{
			bTree->traversal(outFile);
		}
		else if (temp[0] == 'L')
		{
			val = getDigitsFromString(temp);

			if (val > bTree->getLevel())
				outFile << "empty";

			bTree->printLevel(outFile, val);
		}
	}
}
