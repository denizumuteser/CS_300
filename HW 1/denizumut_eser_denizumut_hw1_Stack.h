#pragma once
#include <iostream>
using namespace std;

struct Underflow : public exception {
	const char* what () const throw () {
		return "Exception: trying to access element of empty Stack.";
	}
};

template<class Object>
class Stack
{

public:
	Stack();
	Stack(const Stack & rhs);
	~Stack();

	//utility functions
	bool isEmpty() const; //check if stack is emptly
	bool isFull() const; //check if stack is full
	void makeEmpty(); //make stack empty

	//main functions
	void pop(); //remove element from top
	void push(const Object & x); //add element to top
	Object topAndPop(); //get top element then remove it from stack
	const Object & top() const; //get the element on top of the stack

	//operators
	const Stack& operator=(const Stack& rhs); //deep copy
private:
	struct ListNode
	{
		Object element;
		ListNode* next;

		ListNode(const Object& theElement, ListNode* n = NULL)
			: element(theElement), next(n) {}
	};

	ListNode* topOfStack;
};

#include "denizumut_eser_denizumut_hw1_Stack.cpp"
