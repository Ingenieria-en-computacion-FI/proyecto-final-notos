# Memoria

El módulo Memory simula la memoria RAM del sistema mediante una lista de bloques de memoria.
Cada bloque almacena su dirección inicial, tamaño, memoria utilizada y el PID del proceso propietario.

La asignación de memoria se realiza mediante un callback configurable que implementa los algoritmos
First Fit, Best Fit o Worst Fit.

Cuando un proceso termina, el bloque asociado se libera y puede reutilizarse posteriormente.
Además, el módulo permite fusionar bloques libres contiguos para reducir la fragmentación externa
y mejorar la disponibilidad de memoria.
