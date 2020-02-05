#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class Type>
struct node
{
	Type data;
	node* next;
};

template <class Type>
class Stack
{
private:
	node<Type>* top;
	int size;
public:
	Stack() { top = nullptr; size = 0; }
	Type pop()
	{
		if (isEmpty())
			return 0;
		node<Type>* cu = top;
		top = top->next;
		size -= 1;

		return cu->data;
	}
	void push(Type data)
	{
		node<Type>* temp = new node<Type>;
		temp->data = data;
		temp->next = top;
		top = temp;

		size += 1;
	}
	Type peek() 
	{
		if (isEmpty())
			return 0;
		return top->data;
	}
	int getSize()
	{
		return size;
	}
	bool isEmpty()
	{
		if (top == nullptr)
			return true;
		return false;
	}
	void reverse()
	{
		Stack* reversed = new Stack();

		while (!isEmpty())
			reversed->push(pop());

		top = reversed->top;
		size = reversed->size;
	}
	void print()
	{
		node<Type>* cu = top;

		while (cu != nullptr)
		{
			cout << cu->data << endl;
			cu = cu->next;
		}
		cout << endl;
	}
};

template <class Type>
class Queue
{
private:
	Type *arr;
	int maxSize, currSize;
public:
	Queue(int size)
	{
		if (size <= 0)
			size = 100;

		arr = new Type[size];
		maxSize = size;
		currSize = 0;
	}
	~Queue()
	{
		delete[] arr;
	}
	Queue(const Queue<Type> &old_obj)
	{
		maxSize = old_obj.maxSize;
		currSize = old_obj.currSize;
		arr = new Type[maxSize];

		for (int i = 0; i < currSize; i++)
			arr[i] = old_obj.arr[i];
	}
	Queue& operator=(const Queue<Type> &rhs) {

		// Only do assignment if RHS is a different object from this.
		if (this != &rhs) {
			// Deallocate, allocate new space, copy values...
			maxSize = rhs.maxSize;
			currSize = rhs.currSize;

			for (int i = 0; i < currSize; i++)
				arr[i] = rhs.arr[i];
		}

		return *this;
	}
	void enqueue(Type data)
	{
		if (isFull())
			return;

		arr[currSize] = data;
		currSize += 1;
 	}
	Type dequeue()
	{
		if (isEmpty())
			return 0;
		
		Type temp = arr[0];

		for (int i = 1; i < currSize; i++)
			arr[i - 1] = arr[i];

		currSize -= 1;
		return temp;
	}
	bool isEmpty()
	{
		if (currSize == 0)
			return true;
		return false;
	}
	bool isFull()
	{
		if (currSize == maxSize)
			return true; 
		return false;
	}
	Type getFront()
	{
		if (isEmpty())
			return 0;
		return arr[0];
	}
	Type getBack()
	{
		if (isEmpty())
			return 0;
		return arr[currSize - 1];
	}
	int getSize()
	{
		return currSize;
	}
	void print()
	{
		for (int i = 0; i < currSize; i++)
			cout << arr[i] << endl;
		cout << endl;
	}
};

bool areParenthesisBalanced(string input)
{
	Stack<char> *stack = new Stack<char>();

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '{' || input[i] == '[' || input[i] == '(')
			stack->push(input[i]);
		else if (input[i] == '}' || input[i] == ']' || input[i] == ')') 
		{
			if (stack->peek() == '{' && input[i] == '}' ||
				stack->peek() == '[' && input[i] == ']' ||
				stack->peek() == '(' && input[i] == ')')
				stack->pop();
			else
				return false;
		}
	}

	return true;
}

int priority(char x)
{
	if (x == '^')
		return 3;
	else if (x == '*' || x == '/')
		return 2;
	else if (x == '+' || x == '-')
		return 1;

	return 0;
}

Queue<string>* infixToPostfix(string s)
{
	string temp;
	Stack<char>* stack = new Stack<char>();
	Queue<string>* output = new Queue<string>(s.size());
	char prev;
	int i = 1;

	// process??
	// If int move to output
	// If char compare pr(char) vs top of stack
		// if pr(char) <= pr(top)
			// pop from stack, move to output
			// push new operator
		// if pr(char) > pr(top)
			// push char onto stack

	// Account for first element.
	if (s[0] == '-')
		temp += ",";
	else if (s[0] == '+' || isdigit(s[0]))
		temp += s[0];
	else if (s[0] == '(')
		stack->push(s[0]);

	while (i < s.size())
	{
		prev = s[i - 1];

		// Checking for if it's a digit or whether it is a negative or positive sign.
		if (isdigit(s[i]) ||
			((s[i] == '-' || s[i] == '+') && (prev == '(' || prev == '[' || prev == '{' ||
				prev == '-' || prev == '+' || prev == '*')))
		{
			if (s[i] == '-')
				temp += ',';
			else
				temp += s[i];
		}
		// Getting rid of all empty spaces.
		else if (s[i] == ' ')
		{
			continue;
		}
		// All other instances.
		else
		{
			// Push temp string onto output and reset number string.
			if (temp != "")
			{
				output->enqueue(temp);
				temp = "";
			}
			if (stack->isEmpty() || s[i] == '(')
			{
				stack->push(s[i]);
			}
			else if (s[i] == ')')
			{
				while (stack->peek() != '(')
				{
					temp = "";
					temp += stack->pop();
					output->enqueue(temp);
				}

				stack->pop();
			}
			else if (priority(s[i]) <= priority(stack->peek()))
			{
				temp = "";
				temp += stack->pop();
				output->enqueue(temp);
				stack->push(s[i]);
			}
			else if (priority(s[i]) > priority(stack->peek()))
			{
				stack->push(s[i]);
			}

			temp = "";
		}

		i += 1;
	}

	// Last number.
	if (temp != "")
		output->enqueue(temp);

	while (!stack->isEmpty())
	{
		temp = "";
		temp += stack->pop();
		output->enqueue(temp);
	}

	// Fixes the output queue's negative signs.
	Queue<string>* outputFixedNeg = new Queue<string>(s.size());
	string prevOutput = "";
	temp = "";
	int negCounter = 0;
	i = 0;
	int size = output->getSize();

	while (i < size)
	{
		temp = output->dequeue();

		if (temp == ",")
		{
			negCounter += 1;
		}
		else if (negCounter > 0)
		{
			if (temp[0] == ',')
				temp[0] = '-';

			if (negCounter % 2 == 1)
				outputFixedNeg->enqueue(to_string(stoi(temp) * -1));
			else
				outputFixedNeg->enqueue(temp);

			negCounter = 0;
		}
		else if (temp[0] == ',')
		{
			temp[0] = '-';
			outputFixedNeg->enqueue(temp);
		}
		else
		{
			outputFixedNeg->enqueue(temp);
		}
		
		i += 1;
	}

	return outputFixedNeg;
}

// If the postfix equation given is solvable.
bool isPostfixSolvable(Queue<string>* postfix)
{
	Queue<string> postfixTemp = *postfix;
	Stack<string>* numbers = new Stack<string>();

	while (!postfixTemp.isEmpty())
	{
		if (postfixTemp.getFront() == "+" || postfixTemp.getFront() == "-" || postfixTemp.getFront() == "*" || postfixTemp.getFront() == "/")
		{
			if (numbers->getSize() < 2)
				return false;

			numbers->pop();
		}
		else
			numbers->push("");

		postfixTemp.dequeue();
	}
	
	return true;
}

long long solveEquation(long long a, long long b, string oper)
{
	if (oper == "+")
		return a + b;
	if (oper == "-")
		return a - b;
	if (oper == "/")
		return a / b;
	if (oper == "*")
		return a * b;
	if (oper == "^")
		return pow(a, b);

	return 0;
}

// Solves the given postfix equation.
long long solvePostfix(Queue<string>* postfix)
{	
	Queue<string> postfixTemp = *postfix;
	Stack<string>* numbers = new Stack<string>();
	long long a, b;
	string oper;

	while (!postfixTemp.isEmpty())
	{
		if (postfixTemp.getFront() == "+" || postfixTemp.getFront() == "-" || 
			postfixTemp.getFront() == "*" || postfixTemp.getFront() == "/" || postfixTemp.getFront() == "^")
		{
			a = stoll(numbers->pop());
			b = stoll(numbers->pop());
			oper = postfixTemp.dequeue();

			numbers->push(to_string(solveEquation(b, a, oper)));
		}
		else
			numbers->push(postfixTemp.dequeue());
	}

	return stoll(numbers->pop());
}

int main()
{
	ifstream infile("input31.txt");
	ofstream outfile("output.txt");
	string line;

	while (!infile.eof())
	{
		getline(infile, line);

		if (!areParenthesisBalanced(line))
		{
			outfile << "error" << endl;
		}
		else
		{
			Queue<string>* postfix = infixToPostfix(line);

			postfix->print();

			if (isPostfixSolvable(postfix))
				outfile << line << "=" << solvePostfix(postfix) << endl;
			else
				outfile << "error" << endl;
		}
	}
}
