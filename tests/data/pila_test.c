#include <stdio.h>

#include <data/Stack.h>


void charParser(void* dest, void* src) {
	*(int*) dest = *(int*) src;
}


int main() {
	Stack* s = newStack(sizeof(int), charParser);
	
	int nums[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

	for(int i = 0; i < 10; i++)
		stackPush(s, nums + i);

	while(!stackIsEmpty(s)){
		int p = 0;
		stackPop(s, &p);

		printf("%d, ", p);
	}
	printf("\b\b\n");

	deleteStack(s);

	return 0;
}


