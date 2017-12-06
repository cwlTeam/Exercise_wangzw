#include "stack.h"

using std::cout;
using std::cin;
using std::endl;


//构造函数，初始化栈
Stack::Stack(pNode node, Item data){
	node = new Node;
	if (node == 0){
		cout << "Fail to new a Node" << endl;
		return;
	}

	this->Top = node;
	this->Buttom = node;
	this->size = 1;
	node->pNext = NULL;
	node->data = data;
	return;
}

//进栈操作
bool Stack::Push(pNode node, Item data){
	node = new Node;
	if (node == 0){
		cout << "Fail to new a Node" << endl;
		return false;
	}

	node->pNext = this->Top;
	node->data = data;
	this->size++;
	this->Top = node;

	return true;
}


//出栈操作
Item Stack::Pop(pNode node){
	if (!this->size){
		cout << "There is not a valid node" << endl;
		this->Top = NULL;

		return false;
	}

	//pNode node;
	Item data;
	data = this->Top->data;
	node = this->Top;
	this->size--;
	this->Top = this->Top->pNext;

	delete node;
	return data;
}

//遍历栈内元素
bool Stack::visit(){
	int size = this->size;
	if (size == 0){
		cout << "It is an empty stack!" << endl;
	}

	pNode node = this->Top;

	while (size--){
		cout << node->data << endl;
		node = node->pNext;
	}

	return true;
}

//获取栈的大小
int Stack::Stack_size(){
	return this->size;
}

//栈判空
bool Stack::IsEmpty(){
	if (this->size == 0)
		return true;
	else
		return false;
}

//取栈顶元素
Item Stack::GetTopData(){
	return this->Top->data;
}

//清除栈内元素
bool Stack::ClearStack(){
	while (this->IsEmpty() == false){
		this->Pop(this->Top);
	}

	return true;
}

//销毁栈
bool Stack::DestroyStack(){
	pNode node = NULL;
	if (this->IsEmpty() == false){
		node = this->Top;
		this->Top = this->Top->pNext;
		delete node;
	}

	cout << "Stack is destroyed" << endl;
	return true;
}