#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define CANTIDAD_PRUEBAS_VOLUMEN 2400

// Funcion que enmascara la funcion pila_destruir.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir_wrapper(void* pila){
  pila_destruir(pila);
}

// Pruebas para una cola vacia.
void pruebas_cola_operaciones_invalidas_cola_vacia(){
  printf("INICIO DE PRUEBAS OPERACIONES INVALIDAS CON COLA VACIA.\n");
  // Creo una cola.
  cola_t* cola=cola_crear();
  // Inicio de pruebas.
  print_test("Crear cola",cola!=NULL);
  print_test("La cola esta vacia es true",cola_esta_vacia(cola));
  print_test("Desencolar cuando la cola esta vacia es NULL",cola_desencolar(cola)==NULL);
  print_test("Ver primero cuando la cola esta vacia es NULL",cola_ver_primero(cola)==NULL);
  // Destruyo la cola.
  cola_destruir(cola,NULL);
  print_test("La cola fue destruida",true);
}

// Pruebas de encolar y desencolar.
void pruebas_cola_encolar_desencolar(){
  printf("INICIO DE PRUEBAS DE DESENCOLAR Y ENCOLAR\n");
  // Creo una cola.
  cola_t* cola=cola_crear();
  // Dato a encolar.
  int valor=8;
  // Inicio de pruebas.
  print_test("Crear cola",cola!=NULL);
  print_test("Encolar un dato (8) es true",cola_encolar(cola,&valor));
  print_test("Ver primero es 8",*(int*)cola_ver_primero(cola)==valor);
  print_test("Desencolo un dato (8)",*(int*)cola_desencolar(cola)==valor);
  print_test("La cola esta vacia es true",cola_esta_vacia(cola));
  // Destruyo la cola.
  cola_destruir(cola,NULL);
  print_test("La cola fue destruida",true);
}

// Pruebas con NULL.
void pruebas_cola_null(){
  printf("INICIO DE PRUEBAS CON NULL.\n");
  // Creo una cola.
  cola_t* cola=cola_crear();
  // Inicio de pruebas.
  print_test("Encolar un dato (NULL) es true",cola_encolar(cola,NULL));
  print_test("Ver primero es NULL",cola_ver_primero(cola)==NULL);
  print_test("Desencolo un dato (NULL)",cola_desencolar(cola)==NULL);
  print_test("La cola esta vacia es true",cola_esta_vacia(cola));
  print_test("Desencolar cuando la cola esta vacia es NULL",cola_desencolar(cola)==NULL);
  print_test("Ver primero cuando la cola esta vacia es NULL",cola_ver_primero(cola)==NULL);
  // Destruyo la cola.
  cola_destruir(cola,NULL);
  print_test("La cola fue destruida",true);
}

// Pruebas de volumen.
void pruebas_cola_volumen(){
  printf("INICIO DE PRUEBAS DE VOLUMEN.\n");
  // Creo una cola.
  cola_t* cola=cola_crear();
  print_test("Crear cola",cola!=NULL);
  //Defino la cantidad de elementos a encolar.;
  int arreglo[CANTIDAD_PRUEBAS_VOLUMEN];
  // Empiezo a encolar los elementos.
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_VOLUMEN;i++){
    arreglo[i]=i;
    ok &=cola_encolar(cola,&arreglo[i]);
  }
  print_test("Se pudieron encolar todos los elementos",ok);
  print_test("Ver primero es 0",*(int*)cola_ver_primero(cola)==arreglo[0]);
  // Compruebo que la mitad de lo encolado sea correcto mientras se desencolan los elementos.
  int mitad_cantidad=CANTIDAD_PRUEBAS_VOLUMEN/2;
  ok=true;
  for (int i=0;i<mitad_cantidad;i++){
    ok &=*(int*)cola_desencolar(cola)==i;
  }
  print_test("Se pudieron verificar la mitad de los elementos",ok);
  // Compruebo que la cola no este vacia y que el primero no sea NULL.
  print_test("La cola no esta vacia",!cola_esta_vacia(cola));
  print_test("El primero no es NULL",cola_ver_primero(cola)!=NULL);
  // Destruyo la cola con los elementos que quedaron.
  cola_destruir(cola,NULL);
  print_test("La cola fue destruida",true);
}

// Pruebas de invariante.
void pruebas_cola_invariante(){
  printf("INICIO DE PRUEBAS DE INVARIANTE.\n");
  // Creo una cola.
  cola_t* cola=cola_crear();
  print_test("Crear cola",cola!=NULL);
  // Datos a encolar.
  // Creo varias pilas.
  pila_t* pila1=pila_crear();
  print_test("Crear pila1",pila1!=NULL);
  pila_t* pila2=pila_crear();
  print_test("Crear pila2",pila2!=NULL);
  pila_t* pila3=pila_crear();
  print_test("Crear pila3",pila3!=NULL);
  pila_t* pila4=pila_crear();
  print_test("Crear pila4",pila4!=NULL);
  pila_t* pila5=pila_crear();
  print_test("Crear pila5",pila5!=NULL);
  pila_t* pila6=pila_crear();
  print_test("Crear pila6",pila6!=NULL);
  int valor1=3;
  int valor2=0;
  int valor3=10;
  int valor4=-33;
  int valor5=7;
  int valor6=20;
  bool ok=true;
  ok &=pila_apilar(pila1,&valor1);
  ok &=pila_apilar(pila1,"Hola");
  ok &=pila_apilar(pila2,&valor2);
  ok &=pila_apilar(pila2,"Algoritmos");
  ok &=pila_apilar(pila3,&valor3);
  ok &=pila_apilar(pila3,"Teorema");
  ok &=pila_apilar(pila4,&valor4);
  ok &=pila_apilar(pila4,"Futbol");
  ok &=pila_apilar(pila5,&valor5);
  ok &=pila_apilar(pila5,"SSD");
  ok &=pila_apilar(pila6,&valor6);
  ok &=pila_apilar(pila6,"HDD");
  print_test("Se puedieron apilar todos los elementos",ok);
  ok &=cola_encolar(cola,pila1);
  ok &=cola_encolar(cola,pila2);
  ok &=cola_encolar(cola,pila3);
  ok &=cola_encolar(cola,pila4);
  ok &=cola_encolar(cola,pila5);
  ok &=cola_encolar(cola,pila6);
  print_test("Se pudieron encolar todas las pilas",ok);
  // Destruyo la cola con los pilas y los valores que se apilaron.
  cola_destruir(cola,pila_destruir_wrapper);
  print_test("La cola fue destruida",true);
}

// Ejecucion de pruebas del alumno.
void pruebas_cola_alumno(){
  pruebas_cola_operaciones_invalidas_cola_vacia();
  pruebas_cola_encolar_desencolar();
  pruebas_cola_null();
  pruebas_cola_volumen();
  pruebas_cola_invariante();
}
