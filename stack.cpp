#include "stack.h"

using std::cout;
using std::cin;
using std::endl;


//���캯������ʼ��ջ
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

//��ջ����
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


//��ջ����
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

//����ջ��Ԫ��
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

//��ȡջ�Ĵ�С
int Stack::Stack_size(){
	return this->size;
}

//ջ�п�
bool Stack::IsEmpty(){
	if (this->size == 0)
		return true;
	else
		return false;
}

//ȡջ��Ԫ��
Item Stack::GetTopData(){
	return this->Top->data;
}

//���ջ��Ԫ��
bool Stack::ClearStack(){
	while (this->IsEmpty() == false){
		this->Pop(this->Top);
	}

	return true;
}

//����ջ
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