#include <stdlib.h>
#include <string.h>

#include <data/Node.h>


Node* newNode(void* src, uint16_t size) {
	Node* new_node = auxNode();

	//	Copiar memoria al contenedor.
	void* dat = memblockCreate(size);
	memcpy(dat, src, size);

	//	Meter al nodo :p
	new_node->data = dat;

	return new_node;
}


Node* auxNode() {
	Node* new_node = memblockCreate(sizeof(Node));

	//	Generar el nodo
	*new_node = (Node) {NULL, NULL, NULL};

	return new_node;
}


void deleteNode(Node* node) {
	memblockDelete(node->data);
	memblockDelete(node);
}



void* memblockCreate(uint16_t memblock_size) {
	return malloc(memblock_size);
}


void memblockDelete(void* memblock_addr) {
	free(memblock_addr);
}

