#include <stdlib.h>

#include <notOS/data/List.h>

#define START	list->start
#define END	list->end

#define invalidAddIndex()	( index < 0 || index > listSize(list) )
#define invalidRemoveIndex()	( index < 0 || index > listSize(list) - 1 )

/**
 *	@brief	Obtiene el nodo en la posición ${index} de la lista (por la izquierda).
 *
 *	@param	list	Puntero a la lista en donde buscar.
 *	@param	index	Índice del nodo a buscar (contando de iquierda a derecha).
 *
 *	@return	Puntero al nodo deseado.
*/
Node* getNodeL(List* list, int16_t mov) {
	Node* aux = START;

	//	Moverse por la estructura.
	for(int16_t i = 0; i < mov; i++)
		aux = aux->next;

	return aux;
}

/**
 *	@brief	Obtiene el nodo en la posición ${index} de la lista (por la derecha).
 *
 *	@param	list	Puntero a la lista en donde buscar.
 *	@param	index	Índice del nodo a buscar (contando de derecha a izquierda).
 *
 *	@return	Puntero al nodo deseado.
*/
Node* getNodeR(List* list, int16_t mov){
	Node* aux = END;

	//	Moverse por la estructura.
	for(int16_t i = 0; i < mov; i++)
		aux = aux->prev;

	return aux;
}

/**
 *	@brief	Obtiene el nodo en la posición ${index} de la lista.
 *
 *	Utiliza el camino más corto, ya sea por derecha o por izquierda,
 *	para llegar al nodo deseado.
 *
 *	@param	list	Puntero a la lista en donde buscar.
 *	@param	index	Índice del nodo a buscar (linealmente).
 *
 *	@return	Puntero al nodo deseado.
*/
Node* getNode(List* list, int16_t index) {
	if(index < listSize(list) * 0.5)
		return	getNodeL(list, index);
	
	return	getNodeR(list, listSize(list) - index + 1);
}


List* newList(uint16_t size, void (*cast)(void*, void*)) {
	List* new_list = malloc(sizeof(List));

	//	Crear Nodos Auxiliares (inicio y final).
	Node* start = auxNode();
	Node* end = auxNode();

	start->prev = end->prev = start;
	start->next = end->next = end;

	//	Generar Lista.
	*new_list = (List) {0, size, cast, start, end};

	return new_list;
}

void deleteList(List* list) {
	//	Vaciar lista.
	listClear(list);

	free(START);
	free(END);
	free(list);
}


void listAdd(List* list, int16_t index, void* data) {
	//	Protección contra indice inválido.
	if(invalidAddIndex())	return;
	
	//	Quitar circularidad temporalmente.
	//START->next->prev = START;
	//END->prev->next = END;

	//	Obtener los nodo (${index} - 1) y (${index} + 1).
	Node* prev = getNode(list, index);
	Node* next = prev->next;

	//	Agregar nuevo nodo a la lista.
	Node* new_node = newNode(data, list->type_size);

	new_node->prev = prev;
	new_node->next = next;

	prev->next = new_node;
	next->prev = new_node;

	//	Lineas mágicas para la circularidad.
	//START->next->prev = END->prev;
	//END->prev->next = START->next;

	list->length++;
}
		
void listRemove(List* list, int16_t index, void* dest) {
	//	Protección contra indice inválido.
	if(invalidRemoveIndex()) return;

	//	Obtener los nodo (${index} - 1) y (${index}).
	Node* prev = getNode(list, index);
	Node* node = prev->next;

	//	Almacenar la información.
	list->cast(dest, node->data);

	//	Remover el nodo a la lista.
	//if(list->length == 1) {
        //	START->next = END;
	//	END->prev = START;
	//}else {
		Node* next = node->next;
		
		prev->next = next;
		next->prev = prev;

	//	if(node == START->next)
	//		START->next = next;
		
	//	if(node == END->prev)
	//		END->prev = prev;
	//}
	deleteNode(node);

	list->length--;
}
		
void listFirst(List* list, void* dest) {
	//	Protección contra lista vacía.
	if(listIsEmpty(list))	return;

	list->cast(dest, START->next->data);
}
		
void listLast(List* list, void* dest) {
	//	Protección contra lista vacía.
	if(listIsEmpty(list))	return;

	list->cast(dest, END->prev->data);
}


void listClear(List *list) {
	void* auxBlock = malloc(list->type_size);

	while(!listIsEmpty(list))
		listRemoveFirst(list, auxBlock);

	free(auxBlock);
}


