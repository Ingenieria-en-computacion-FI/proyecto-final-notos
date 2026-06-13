# Estructuras de datos

El proyecto implementa sus propias estructuras de datos genéricas basadas en nodos doblemente enlazados.
Cada nodo almacena un bloque de memoria dinámico (void*) y enlaces al nodo anterior y siguiente.
Sobre esta base se construyen:

* List: estructura lineal doblemente enlazada con acceso por índice, inserción y eliminación en cualquier posición.
* Queue: implementación FIFO construida sobre la lista, utilizada para almacenar procesos pendientes y procesos listos para ejecución.
* Stack: implementación LIFO construida sobre la lista, disponible para algoritmos o tareas auxiliares.

Las estructuras son genéricas gracias al uso de callbacks de casting,
lo que permite reutilizarlas para almacenar distintos tipos de datos sin duplicar código.
