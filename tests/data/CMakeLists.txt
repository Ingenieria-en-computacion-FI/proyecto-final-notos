#	Configuración (CMake) para la compilación de los tests [Data]:
#
#	*pila_test	(probar el funcionamiento de las pilas).
#	*cola_test	(probar el funcionamiento de las colas).
#
set(NOTY_TEST_SUBDIR data)


message('\nGenerando: \"data tests\":')


#	pila_test
add_executable(pila_test pila_test.c)
target_link_libraries(pila_test PRIVATE stack)

set_testConfig(pila_test)

#	cola_test
add_executable(cola_test cola_test.c)
target_link_libraries(cola_test PRIVATE queue)

set_testConfig(cola_test)

#	lista_test
add_executable(lista_test lista_test.c)
target_link_libraries(lista_test PRIVATE list)

set_testConfig(lista_test)


