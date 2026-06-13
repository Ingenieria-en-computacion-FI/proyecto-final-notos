# Scheduler

El módulo Scheduler administra la ejecución de los procesos listos para correr.
Internamente mantiene una cola de procesos y utiliza un callback para seleccionar el algoritmo de planificación configurado
(FIFO, Round Robin o SJF).

En cada actualización, el scheduler obtiene el proceso que debe ejecutarse,
reduce su tiempo restante según el quantum definido y determina si debe continuar en ejecución,
regresar a la cola o finalizar.

De esta forma, la política de planificación queda desacoplada de la estructura interna del scheduler.
