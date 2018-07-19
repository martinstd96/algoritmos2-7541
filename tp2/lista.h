#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

// La lista esta planteada como una lista enlazada de punteros genericos.
typedef struct lista lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacia.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos insertados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t* lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de
// error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al principio de la lista, dato se encuentra
// al principio de la misma.
bool lista_insertar_primero(lista_t* lista,void* dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de
// error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, dato se encuentra
// al final de la misma.
bool lista_insertar_ultimo(lista_t* lista,void* dato);

// Borra al primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la misma y se devuelve su valor, sí está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista contiene un
// elemento menos, si ella no estaba vacía.
void* lista_borrar_primero(lista_t* lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t* lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos se devuelve el valor del ulltimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Obtiene el largo de la lista, es decir la cantidad de elementos que contiene.
// Pre: la lista fue creada.
// Post: se devolvió el valor del largo de la misma.
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t* lista,void destruir_dato(void*));

/* ******************************************************************
 *                 PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

 // Primitiva de la lista para iterar sobre ella. La funcion visitar recibida
 // especifica lo que se va a hacer con los datos que viven en la lista. Además
 // recibe un puntero extra que puede ser usado para mantener una memoria entre
 // las sucesivas llamdas.
 // Pre: la lista fue creada.
 void lista_iterar(lista_t *lista, bool visitar(void* dato, void* extra), void* extra);

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// El iterador de la lista está planteado como una forma de abstraerse para
// recorrer dicha estrucura.
typedef struct lista_iter lista_iter_t;

//  Crea un iterador de la lista.
// Pre: la lista fue creada.
// Post: devuelve un iterador que esta parado sobre el primer elemento de la lista.
lista_iter_t* lista_iter_crear(lista_t* lista);

// Avanza sobre la lista, devuelve falso en caso de que la lista esté vacía o
// esté al final de ella.
// Pre: la lista y el iterador fueron creados.
bool lista_iter_avanzar(lista_iter_t* iter);

// Obtiene el valor del elemento actual de la lista, en caso de que la lista esté
// vacía o esté al final de la misma devuelve NULL.
// Pre: la lista y el iterador fueron creados.
// Post: se devolvió el elemento actual de la lista o NULL en caso de que la misma
// se encuentre vacía o el iterador esté al final.
void* lista_iter_ver_actual(const lista_iter_t* iter);

// Devuelve verdadero o falso según si se encuentra al final de la lista o no.
// Pre: la lista y el iterador fueron creados.
bool lista_iter_al_final(const lista_iter_t* iter);

// Inserta un dato en la posición actual del iterador. Devuelve falso en caso de error.
// Pre: la lista y el iterador fueron creados.
// Post: se insertó el dato en la lista, en la posición actual del iterador.
bool lista_iter_insertar(lista_iter_t* iter,void* dato);

// Elimina al elemento que está en la posición actual del iteador. Devuelve NULL
// en el caso de que la lista esté vacía o el iterador esté al final de la misma.
// Pre: la lista y el iterador fueron creados.
// Post: se devolvió el elemento actual de la lista o NULL en caso de que la lista
// esté vacía o el iterador se encuentre al final de la misma.
void* lista_iter_borrar(lista_iter_t* iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se eliminó el iterador.
void lista_iter_destruir(lista_iter_t* iter);

/* *****************************************************************
 *                   PRUEBAS PARA LA LISTA
 * *****************************************************************/

// Realiza pruebas sobre la implementación de la lista del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista ni
// al struct lista_iter).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H
