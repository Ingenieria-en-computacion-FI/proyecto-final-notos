#include <data/Queue.h>

#define FRONT	queue->front
#define REAR	queue->rear


Queue* newQueue(uint16_t size, void (*cast)(void*, void*)) {
	Queue* new_queue = memblockCreate(sizeof(Queue));

	//	Crear Nodos Auxiliares (frente y final).
	Node* front = auxNode();
	Node* rear = auxNode();

	front->next = rear;
	rear->next = front;

	//	Generar Cola.
	*new_queue = (Queue) {0, size, cast, front, rear};

	return new_queue;
}

void  deleteQueue(Queue* queue) {
	//	Vaciar Cola (si no lo está ya).
	queueClear(queue);

	deleteNode(FRONT);
	deleteNode(REAR);
	memblockDelete(queue);
}


void queueEnqueue(Queue* queue, void* data) {
	Node* new_node = newNode(data, queue->type_size);

	//	Agregando el nuevo nodo a la cola.
	REAR->next->next = new_node;
	REAR->next = new_node;

	//	Linea mágica para mantener la cola circular.
	new_node->next = FRONT->next;

	//	Aumentar el contador.
	queue->length++;
}

void queueDequeue(Queue* queue, void* dest) {
	//	Protección para cola vacía.
	if(queueIsEmpty(queue))	return;

	Node* first = FRONT->next;	//	Primer elemento de la cola.
	Node* last = REAR->next;	//	Último elemento de la cola.
	
	//	Obtener dato.
	queue->cast(dest, first->data);
		

	/*	Algoritmo mágico para eliminar nodos
	 *	(Sin condicionales de por medio).
	*/
		last->next = REAR;		//	(1) Quitar la circularidad (temporalmente).

		FRONT->next	= first->next;	//	(2) Mover el frente una posición a la derecha.
		first->next	= FRONT;	//	(3) Que el primero apunte a ${front}, por conveniencia.
		REAR->next	= last->next;	//	(4) Mover el final una posición a la derecha.
		first->next	= last;		//	(5) Que el primero apunte al último.

		last->next = FRONT;		//	(6) Que el último apunte a ${front}.
		REAR->next = first->next;	//	(7) Que ${rear} apunte al siguiente del primero.
		last->next = FRONT->next;	//	(8) Devolver la circularidad.

		deleteNode(first);		//	(9) Eliminar el nodo.
	//	Fin del algoritmo mágico :p
	
	
	//	Disminuir el contador.
	queue->length--;
}

void queueFront(Queue* queue, void* dest) {
	//	Protección para cola vacía.
	if(queueIsEmpty(queue))	return;

	queue->cast(dest, FRONT->next->data);
}

void queueRear(Queue* queue, void* dest) {
	//	Protección para cola vacía.
	if(queueIsEmpty(queue))	return;

	queue->cast(dest, REAR->next->data);
}


