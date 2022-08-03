#ifndef _STACK_H
#define _STACK_H
//Berk Sezer

#include <iostream>
#include "Stack.h"
#include <string>

using namespace std;

//template <class itemType>
//struct TreeNode
//{
//  itemType value;
//  TreeNode *left;
//  TreeNode *right;
//
//  TreeNode(){
//    left = nullptr;
//    right = nullptr;
//  }
//};

template <class Comparable>
struct BinaryNode {
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;
	string title;

	BinaryNode(const Comparable & theElement, BinaryNode* lt, BinaryNode *rt, string t){
		element = theElement;
		left = lt;
		right = rt;
		title = t;
	
	}

};

template <class itemType>
struct StackNode
{
  BinaryNode<itemType>* value;
  StackNode *next;
};

template <class itemType>
class Stack
{
private:
  StackNode<itemType> *top;
  StackNode<itemType>* GetTopPointer(Stack<itemType> myStack);
  
public:
  Stack(void);
  void push(BinaryNode<itemType>* );
  BinaryNode<itemType>* pop();
  bool isEmpty();
};

template<class itemType>
Stack<itemType>::Stack()
{
	top=nullptr;
}

template<class itemType>
StackNode<itemType>* Stack<itemType>::GetTopPointer(Stack<itemType> myStack)
{
	return myStack.top;
}

//Push back elements to the stack
template<class itemType>
void Stack<itemType>::push(BinaryNode<itemType>* elmt)
{
	StackNode<itemType> *newNode;

	newNode = new StackNode<itemType>;
	newNode->value = elmt;

	if(isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}
//Pop up elements from the stack

template<class itemType>
BinaryNode<itemType>* Stack<itemType>::pop()
{
	StackNode<itemType> *temp;

	if(!isEmpty())
	{
		BinaryNode<itemType>* elmt = top->value;
		temp = top->next;
		delete top;
		top = temp;
		return elmt;
	}
	return nullptr;
}

//If the stack is empty check function
template<class itemType>
bool Stack<itemType>::isEmpty()
{
	return (top==nullptr);
}


#endif

