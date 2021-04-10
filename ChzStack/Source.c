#include <stdio.h>
#include <stdlib.h>
#include "ChzStack.h"

int main()
{
	ChzResult tmp;
	ChzResult_Init(&tmp, sizeof(int));

	ChzStack myStack;
	ChzStack_Init(&myStack, sizeof(int), 4);

	while(1)
	{
		static char bufAct;
		static int bufInput;
		printf("Select Action (0-Exit, 1-Push, 2-Pop, 3-Peek): ");
		scanf_s("%c", &bufAct, 1);
		fseek(stdin, 0, SEEK_END);

		switch (bufAct)
		{
		case '0':
			printf("Program Exited\n");
			break;

		case '1':
			if (ChzStack_isFull(&myStack)) { printf("Stack is full!\n"); }
			else
			{
				printf("Input Value: ");
				scanf_s("%d", &bufInput);
				fseek(stdin, 0, SEEK_END);

				ChzStack_Push(&myStack, &bufInput);
				printf("%d is pushed.\n", bufInput);
			}
			putchar('\n');
			break;

		case '2':
			if (ChzStack_isEmpty(&myStack)) { printf("Stack is empty!\n"); }
			else
			{
				ChzStack_Pop(&myStack, &tmp);
				printf("%d is popped.\n", *(int*)(tmp.pData));
			}
			putchar('\n');
			break;

		case '3':
			if (ChzStack_isEmpty(&myStack)) { printf("Stack is empty!\n"); }
			else
			{
				ChzStack_Peek(&myStack, &tmp);
				printf("%d is on top.\n", *(int*)(tmp.pData));
			}
			putchar('\n');
			break;

		default:
			printf("Wrong Input!\n");
			break;
		}
		if (bufAct == '0') { break; }
		system("pause");
		system("cls");
	}

	ChzResult_Free(&tmp);
	ChzStack_Free(&myStack);
	return 0;
}