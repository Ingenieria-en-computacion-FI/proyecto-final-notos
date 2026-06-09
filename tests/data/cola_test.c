#include <stdio.h>

#include <data/Queue.h>


void intParser(void* dest, void* src) {
	*(int*) dest = *(int*) src;
}


int main() {
	Queue* q = newQueue(sizeof(int), intParser);
	
	int nums[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

	for(int i = 0; i < 10; i++)
		queueEnqueue(q, nums + i);
	
	while(!queueIsEmpty(q)) {
		int p = 0;
		queueDequeue(q, &p);

		printf("%d, ", p);
	}
	puts("\b\b");

	deleteQueue(q);

	return 0;
}


