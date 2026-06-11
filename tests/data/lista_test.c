#include <stdio.h>

#include <notOS/notOS.h>


void intParser(void* dest, void* src) {
	*(int*) dest = *(int*) src;
}


int main() {
	List* l = newList(sizeof(int), intParser);
	
	int nums[] = {1, 3, 5, 7, 9, 10, 8, 6, 4, 2};

	for(int i = 0; i < 5; i++) {
		listAddFirst(l, nums + i);
		listAddFirst(l, nums + 9 - i);
	}
	
	printf("START->");
	while(!listIsEmpty(l)) {
		int p = 0;
		listRemoveLast(l, &p);

		printf("%d->", p);
		fflush(stdout);
	}
	puts("END");

	deleteList(l);

	return 0;
}


