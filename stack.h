#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

typedef int Item;

typedef struct node{
	Item data;
	struct node *pNext;
}Node, *pNode;

class Stack{
public:
	int size;
	pNode Top;
	pNode Buttom;

public:
	Stack(pNode node, Item data);

public:
	bool Push(pNode node, Item data);
	Item Pop(pNode node);
	bool visit();
	bool IsEmpty();
	int Stack_size();
	Item GetTopData();
	bool ClearStack();
	bool DestroyStack();
};


#endif