#include <stdlib.h>

#include <notOS/core/Memory.h>

#define BLOCKS	ram->blocks
#define FIRST	BLOCKS->start->next
#define LAST	BLOCKS->end->prev

#define foreach_block()	for(uint16_t i = 0; i < listSize(BLOCKS); i++)


void memoryCast(void* dest, void* src) {
	*(MemoryBlock*) dest = *(MemoryBlock*) src;
}


Memory* initRAM(uint16_t size, MemoryBlock* (*fitAlgorithm)(Memory*, uint16_t)) {
	Memory* ram = malloc(sizeof(Memory));

	*ram = (Memory) {
		newList(sizeof(MemoryBlock), memoryCast),
		fitAlgorithm,
		size,
		size
	};

	return ram;
}

void denitRAM(Memory* ram) {
	deleteList(ram->blocks);

	free(ram);
}
	

bool allocateMemory(Memory* ram, uint16_t pid, uint16_t size) {
	MemoryBlock* block;

	if(!(block = ram->fitAlgorithm(ram, size)))	return false;

	//	Actualizar contador de memoria libre.
	ram->free_memory -= size;

	block->used_mem = size;
	block->pid = pid;

	return true;
}

void freeMemory(Memory* ram, uint16_t pid) {
	Node* n = FIRST;

	foreach_block() {
		MemoryBlock* block = (MemoryBlock*) n->data;

		if(block->pid == pid) {
			ram->free_memory += block->used_mem;

			block->used_mem = 0;
			block->pid = 0;
		}

		n = n->next;
	}
}


void memoryAddBlock(Memory *ram, uint16_t size) {
	if(getBlocksUse(ram) == ram->size)	return;

	MemoryBlock last_block = (MemoryBlock) {0, 0, size, 0};
	listLast(ram->blocks, &last_block);

	MemoryBlock new_block = (MemoryBlock) {
		last_block.start + last_block.size,
		0,
		size,
		0
	};

	listAddLast(BLOCKS, &new_block);
}

void memoryCoalesce(Memory* ram) {
	Node* n = FIRST;

	while(n != LAST) {
		MemoryBlock* mem_l = (MemoryBlock*) n->data;
		MemoryBlock* mem_r = (MemoryBlock*) n->next->data;

		if(memoryBlockIsFree(mem_l) && memoryBlockIsFree(mem_r)) {
			mem_l->size = mem_l->size + mem_r->size;

			Node* tmp = n->next;

			n->next = tmp->next;
			tmp->next->prev = n;

			deleteNode(tmp);
		}

		n = n->next;
	}
}


MemoryBlock* memoryFirstFit(Memory* ram, uint16_t size) {
	Node* n = FIRST;

	foreach_block() {
		MemoryBlock* block = (MemoryBlock*) n->data;

		if(memoryBlockIsFree(block) && block->size >= size)	return block;
		n = n->next;
	}

	return NULL;
}

MemoryBlock* memoryBestFit(Memory* ram, uint16_t size) {
	MemoryBlock* best = NULL;
	Node* n = FIRST;

	foreach_block() {
		MemoryBlock* block = (MemoryBlock*) n->data;

		n = n->next;

		if(!memoryBlockIsFree(block))	continue;

		if(block->size < size)	continue;

		if(!best || block->size < best->size)	best = block;
	}

	return best;
}


MemoryBlock* memoryWorstFit(Memory* ram, uint16_t size) {
	MemoryBlock* worst = NULL;
	Node* n = FIRST;

	foreach_block() {
		MemoryBlock* block = (MemoryBlock*) n->data;

		n = n->next;

		if(!memoryBlockIsFree(block))	continue;

		if(block->size < size)	continue;

		if(!worst || block->size > worst->size)	worst = block;
	}

	return worst;
}


