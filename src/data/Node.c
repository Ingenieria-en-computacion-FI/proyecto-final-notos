#include <stdlib.h>
#include <string.h>

#include <notOS/data/Node.h>


Node* newNode(void* src, uint16_t size) {
	Node* new_node = auxNode();

	//	Copiar memoria al contenedor.
	void* dat = malloc(size);
	memcpy(dat, src, size);

	//	Meter al nodo :p
	new_node->data = dat;

	return new_node;
}

Node* auxNode() {
	Node* new_node = malloc(sizeof(Node));

	//	Generar el nodo
	*new_node = (Node) {NULL, NULL, NULL};

	return new_node;
}

void deleteNode(Node* node) {
	free(node->data);
	free(node);
}


