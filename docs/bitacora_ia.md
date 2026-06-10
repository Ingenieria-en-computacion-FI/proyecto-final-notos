# Bitácora IA

## Prompts utilizados

<!--	Primer prompt	-->
#### noty (yo)
Vamos a empezar el proyecto. Por ende, la bitácora.
Te iré dando indicaciones, preguntas o comentarios y
necesito que seas muy puntual con tus respuestas, pues tengo que copiar todo.
Quiero respuestas relativamente cortas y concisas
para poder mantener una buena conversación y avanzar rápido. ¿Entendido?

#### ChatGPT
Entendido.

Responderé de forma:
* Puntual.
* Concisa.
* Técnica cuando sea necesario.
* Sin explicaciones largas salvo que las pidas.
* En formato fácil de copiar para la bitácora cuando corresponda.
necesito solo C:
Si quieres una entrada para la bitácora, indícame el contexto y te la redacto directamente.
Si quieres discutir diseño o implementación, responderé breve y luego avanzamos al siguiente punto.


<!--	Segundo prompt	-->
#### noty (yo)
Como debería organizar el OS/simulador, según las especificaciones del documento.
Suponiendo que el OS tiene un header central que agrega en él todas las funcionalidades.

#### ChatGPT

##### Organización propuesta del simulador / MiniOS

###### Estructura general

```text
MiniOS
│
├── OS.h
│
├── Core
│   ├── Process
│   ├── Scheduler
│   ├── Memory
│   └── Simulation
│
├── Structures
│   ├── Queue
│   ├── CircularQueue
│   ├── Stack
│   ├── LinkedList
│   └── DoublyLinkedList
│
├── Algorithms
│   ├── FirstFit
│   ├── BestFit
│   ├── WorstFit
│   └── SJF
│
├── Shell (opcional)
│
└── Benchmark
```

##### Header central

`OS.h` expone toda la API pública del sistema.

```c
#ifndef OS_H
#define OS_H

#include <Process/Process.h>
#include <Scheduler/Scheduler.h>
#include <Memory/Memory.h>
#include <Simulation/Simulation.h>

#endif
```

##### Responsabilidades

###### Process

Representa procesos simulados.

Responsable de:

* PID.
* Estados.
* Prioridad.
* Tiempo restante.
* Memoria requerida.

###### Scheduler

Selecciona el siguiente proceso.

Implementa:

* FIFO.
* Round Robin.
* SJF.

###### Memory

Administra la memoria simulada.

Implementa:

* Asignación.
* Liberación.
* Fragmentación.
* Coalescencia.

##### Simulation

Coordina todo el sistema.

Responsable de:

* Tick de reloj.
* Cambio de estados.
* Ejecución.
* Finalización de procesos.
* Liberación automática de memoria.

##### Estructuras de datos

###### Queue

Uso:

* FIFO.

###### CircularQueue

Uso:

* Round Robin.

###### Stack

Uso:

* Historial.
* Backtracking.

### LinkedList

Uso:

* Procesos terminados.

###### DoublyLinkedList

Uso:

* Bloques de memoria.

##### Algoritmos

###### Administración de memoria

* First Fit.
* Best Fit.
* Worst Fit.

###### Planificación

* FIFO.
* Round Robin.
* Shortest Job First.

##### Punto de entrada

```text
main
 └─ Simulation
      ├─ Scheduler
      ├─ Memory
      └─ Process
```

La simulación debe ser el único módulo que coordina los demás. Ningún módulo debe controlar directamente a otro.


<!--    Tercer prompt   -->
### noty (yo)
Si ya defini:

* Process.
* ProcessState.
* ProcessPriority.

¿Qué debería implementar de procesos para el sistema?

### ChatGPT
# Siguiente paso recomendado

Una vez definidos:

* `Process`
* `ProcessState`
* `ProcessPriority`

debería implementarse el administrador de procesos.

## Funcionalidades mínimas

### Creación

```c
Process* process_create(...);
```

Responsable de:

* Asignar PID.
* Inicializar campos.
* Estado inicial `READY`.

### Destrucción

```c
void process_destroy(Process*);
```

### Cambio de estado

```c
void process_set_state(
    Process* process,
    ProcessState state
);
```

### Ejecución

```c
void process_execute(
    Process* process,
    size_t time_slice
);
```

Responsable de:

* Reducir `remaining_time`.
* Detectar finalización.

### Finalización

```c
bool process_finished(
    const Process* process
);
```

## Después

Una vez completado el módulo de procesos, implementar:

1. Cola.
2. Scheduler FIFO.
3. Cola circular.
4. Scheduler Round Robin.
5. Lista doblemente ligada para memoria.

Esto permite comenzar rápidamente la simulación básica del sistema.


<!--	Tercer prompt	-->
#### noty (yo)
¿Que deberia haber en "Memory.h"?

#### CharGPT
Se revisaron los requisitos del proyecto relacionados con administración de memoria. Se identificó que el sistema debe permitir:

* Asignación de memoria.
* Liberación de memoria.
* Detección de fragmentación.
* Coalescencia de bloques libres adyacentes.
* Implementación de las estrategias First Fit, Best Fit y Worst Fit.

También se observó que la memoria debe representarse mediante bloques dinámicos enlazados y que la lista doblemente ligada es obligatoria para esta parte del sistema.

## Decisión

El módulo `Memory` será responsable de administrar toda la memoria simulada del sistema.

La interfaz pública deberá incluir operaciones para:

* Inicializar memoria.
* Asignar memoria a procesos.
* Liberar memoria de procesos.
* Calcular memoria libre y utilizada.
* Detectar fragmentación.
* Ejecutar coalescencia.
* Mostrar el estado actual de la memoria.

Las estrategias de asignación (First Fit, Best Fit y Worst Fit) serán implementadas internamente por el administrador de memoria y seleccionables mediante configuración.

## Justificación

Esta organización concentra toda la lógica relacionada con memoria en un único módulo, facilita las pruebas unitarias y permite reutilizar la misma estructura de datos para todas las estrategias de asignación requeridas por el proyecto.


<!--	Cuarto prompt	-->
#### noty (yo)
¿Qué debería llevar "Scheduler.h"? Para el proyecto.

### ChatGPT
Se revisaron los requisitos del proyecto relacionados con planificación de procesos. El scheduler es el componente encargado de decidir qué proceso utilizará el CPU en cada instante de tiempo.

El proyecto exige la implementación de:

* FIFO.
* Round Robin.
* Shortest Job First (SJF).

Además, Round Robin requiere el manejo de un quantum configurable.

## Decisión

El módulo `Scheduler` será responsable de:

* Mantener los procesos listos para ejecución.
* Seleccionar el siguiente proceso.
* Gestionar cambios de estado relacionados con la ejecución.
* Administrar el quantum en Round Robin.
* Permitir cambiar entre algoritmos de planificación.

La interfaz pública deberá incluir operaciones para:

* Crear y destruir schedulers.
* Agregar procesos listos.
* Obtener el siguiente proceso a ejecutar.
* Configurar el algoritmo de planificación.
* Configurar el quantum.
* Consultar el algoritmo activo.

## Estructuras utilizadas

* Cola para FIFO.
* Cola circular para Round Robin.
* Estructura ordenada o búsqueda para SJF.

## Justificación

Separar la planificación en un módulo independiente permite desacoplar la lógica de ejecución de procesos del mecanismo utilizado para seleccionarlos. Esto facilita implementar y comparar los distintos algoritmos requeridos por el proyecto durante la etapa de benchmarking.




## Errores encontrados

#### Error 1
La siguiente macro genera un error en C:
```c
#define foreach_block() for(uint16_t i = 0, Node* n = FIRST; i < listSize(BLOCKS); i++, n = n->next)
```


## Correcciones realizadas

#### Corrección 1
C solo acepta multiples variables dentro de un `for`
si son del mismo tipo de dato.

Al final la macro queda así:
```c
#define foreach_block() for(uint16_t i = 0, i < listSize(BLOCKS); i++)
```

...

## Validaciones realizadas

...
