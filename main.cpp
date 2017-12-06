#include "stack.h"

int main()
{
	int i = 0;
	int data;
	pNode pStack = NULL;

	Stack* stack = new Stack(pStack, 0);

	while (i != 999){
		std::cin >> data;
		stack->Push(pStack, data);
	}

	stack->visit();

	stack->ClearStack();

	stack->DestroyStack();
	stack->visit();

	getchar();
}