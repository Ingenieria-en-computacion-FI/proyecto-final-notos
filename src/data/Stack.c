#include <stdlib.h>

#include <notyOS/data/Stack.h>


Stack* newStack(uint16_t size, void (*cast)(void*, void*)) {
	Stack* new_stack = malloc( sizeof(Stack) );

	//	Crear Nodo Auxiliar (tope).
	Node* top = auxNode();
	top->next = top;

	//	Generar Pila.
	*new_stack = (Stack) {0, size, cast, top};

	return new_stack;
}

void  deleteStack(Stack* stack) {
	//	Vaciar Pila (si no lo está ya).
	stackClear(stack);

	deleteNode(stack->top);
	free(stack);
}


void stackPush(Stack* stack, void* data) {
	Node* new_node = newNode(data, stack->type_size);

	//	Agregando el nuevo nodo a la pila.
	new_node->next = stack->top->next;
	stack->top->next = new_node;

	//	Aumentar el contador
	stack->length++;
}

void stackPop(Stack* stack, void* dest) {
	//	Protección para pila vacía.
	if(stackIsEmpty(stack))	return;

	//	Obtener y almacenar dato.
	Node* tmp = stack->top->next;
	void* src = tmp->data;
	stack->cast(dest, src);
	
	//	Eliminar nodo en el tope.
	stack->top->next = tmp->next;
	deleteNode(tmp);

	//	Disminuir el contador
	stack->length--;
}

void stackTop(Stack* stack, void* dest) {
	//	Protección para pila vacía.
	if(stackIsEmpty(stack))	return;

	stack->cast(dest, stack->top->next->data);
}


void stackClear(Stack *stack) {
	void* auxBlock = malloc(stack->type_size);

	while(!stackIsEmpty(stack))
		stackPop(stack, auxBlock);

	free(auxBlock);
}


