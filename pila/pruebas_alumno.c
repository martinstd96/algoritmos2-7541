#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

// Pruebas para una pila vacia.
void pruebas_pila_operaciones_invalidas_pila_vacia(){
  printf("INICIO DE PRUEBAS OPERACIONES INVALIDAS CON PILA VACIA.\n");
  // Creo una pila.
  pila_t* pila=pila_crear();
  // Inicio de pruebas.
  print_test("Crear pila",pila!=NULL);
  print_test("La pila esta vacia es true",pila_esta_vacia(pila));
  print_test("Desapilar cuando la pila esta vacia es NULL",pila_desapilar(pila)==NULL);
  print_test("Ver tope cuando la pila esta vacia es NULL",pila_ver_tope(pila)==NULL);
  // Destruyo la pila.
  pila_destruir(pila);
  print_test("La pila fue destruida.",true);
}

// Pruebas de apilar y despilar datos.
void pruebas_pila_apilar_desapilar(){
  printf("INICIO DE PRUEBAS DE APILAR Y DESAPILAR.\n");
  // Creo una pila.
  pila_t* pila=pila_crear();
  // Datos a apilar.
  int valor1=4;
  // Inicio de pruebas.
  print_test("Crear pila",pila!=NULL);
  print_test("Apilar un dato (4) es true",pila_apilar(pila,&valor1));
  print_test("Ver tope es 4",*(int*)pila_ver_tope(pila)==valor1);
  print_test("Desapilo un dato (4)",*(int*)pila_desapilar(pila)==valor1);
  print_test("La pila esta vacia es true",pila_esta_vacia(pila));
  print_test("Desapilar cuando la pila esta vacia es NULL",pila_desapilar(pila)==NULL);
  print_test("Ver tope cuando la pila esta vacia es NULL",pila_ver_tope(pila)==NULL);
  print_test("Apilar un dato NULL es true",pila_apilar(pila,NULL));
  print_test("Ver tope es NULL",pila_ver_tope(pila)==NULL);
  print_test("Desapilo un dato (NULL)",pila_desapilar(pila)==NULL);
  print_test("La pila esta vacia es true",pila_esta_vacia(pila));
  print_test("Desapilar cuando la pila esta vacia es NULL",pila_desapilar(pila)==NULL);
  print_test("Ver tope cuando la pila esta vacia es NULL",pila_ver_tope(pila)==NULL);
  // Destruyo la pila.
  pila_destruir(pila);
  print_test("La pila fue destruida.",true);
}

// Pruebas de volumen version 1 para un valor mayor al establecido en la pila.
void pruebas_pila_volumen_v1(){
  printf("INICIO DE PRUEBAS DE VOLUMEN VERSION 1\n");
  // Creo una pila.
  pila_t* pila=pila_crear();
  // Datos a apilar.
  int valor1=3;
  int valor2=0;
  int valor3=10;
  int valor4=-33;
  int valor5=7;
  int valor6=20;
  char* cadena1="Hola";
  char* cadena2="Algoritmos";
  char* cadena3="Teorema";
  char* cadena4="Futbol";
  char* cadena5="SSD";
  char* cadena6="HDD";
  // Inicio de pruebas.
  // Comienzo a apilar.
  print_test("Crear pila",pila!=NULL);
  print_test("Apilar un dato (3) es true",pila_apilar(pila,&valor1));
  print_test("Apilar un dato (0) es true",pila_apilar(pila,&valor2));
  print_test("Apilar un dato (10) es true",pila_apilar(pila,&valor3));
  print_test("Apilar un dato (33) es true",pila_apilar(pila,&valor4));
  print_test("Apilar un dato (7) es true",pila_apilar(pila,&valor5));
  print_test("Apilar un dato (20) es true",pila_apilar(pila,&valor6));
  print_test("Apilar un dato (Hola) es true",pila_apilar(pila,"Hola"));
  print_test("Apilar un dato (Algoritmos) es true",pila_apilar(pila,"Algoritmos"));
  print_test("Apilar un dato (Teorema) es true",pila_apilar(pila,"Teorema"));
  print_test("Apilar un dato (Futbol) es true",pila_apilar(pila,"Futbol"));
  print_test("Apilar un dato (SSD) es true",pila_apilar(pila,"SSD"));
  print_test("Apilar un dato (HDD) es true",pila_apilar(pila,"HDD"));
  print_test("Apilar un dato (NULL) es true",pila_apilar(pila,NULL));
  // Comienzo a desapilar.
  print_test("Ver tope es NULL",pila_ver_tope(pila)==NULL);
  print_test("Desapilo un dato (NULL)",pila_desapilar(pila)==NULL);
  print_test("Ver tope es HDD",pila_ver_tope(pila)==cadena6);
  print_test("Desapilo un dato (HDD)",pila_desapilar(pila)==cadena6);
  print_test("Ver tope es SSD",pila_ver_tope(pila)==cadena5);
  print_test("Desapilo un dato (SSD)",pila_desapilar(pila)==cadena5);
  print_test("Ver tope es Futbol",pila_ver_tope(pila)==cadena4);
  print_test("Desapilo un dato (Futbol)",pila_desapilar(pila)==cadena4);
  print_test("Ver tope es Teorema",pila_ver_tope(pila)==cadena3);
  print_test("Desapilo un dato (Teorema)",pila_desapilar(pila)==cadena3);
  print_test("Ver tope es Algoritmos",pila_ver_tope(pila)==cadena2);
  print_test("Desapilo un dato (Algoritmos)",pila_desapilar(pila)==cadena2);
  print_test("Ver tope es Hola",pila_ver_tope(pila)==cadena1);
  print_test("Desapilo un dato (Hola)",pila_desapilar(pila)==cadena1);
  print_test("Ver tope es 20",*(int*)pila_ver_tope(pila)==valor6);
  print_test("Desapilo un dato (20)",*(int*)pila_desapilar(pila)==valor6);
  print_test("Ver tope es 7",*(int*)pila_ver_tope(pila)==valor5);
  print_test("Desapilo un dato (7)",*(int*)pila_desapilar(pila)==valor5);
  print_test("Ver tope es 33",*(int*)pila_ver_tope(pila)==valor4);
  print_test("Desapilo un dato (33)",*(int*)pila_desapilar(pila)==valor4);
  print_test("Ver tope es 10",*(int*)pila_ver_tope(pila)==valor3);
  print_test("Desapilo un dato (10)",*(int*)pila_desapilar(pila)==valor3);
  print_test("Ver tope es 0",*(int*)pila_ver_tope(pila)==valor2);
  print_test("Desapilo un dato (0)",*(int*)pila_desapilar(pila)==valor2);
  print_test("Ver tope es 3",*(int*)pila_ver_tope(pila)==valor1);
  print_test("Desapilo un dato (3)",*(int*)pila_desapilar(pila)==valor1);
  print_test("La pila esta vacia es true",pila_esta_vacia(pila));
  print_test("Desapilar cuando la pila esta vacia es NULL",pila_desapilar(pila)==NULL);
  print_test("Ver tope cuando la pila esta vacia es NULL",pila_ver_tope(pila)==NULL);
  // Destruyo la pila.
  pila_destruir(pila);
  print_test("La pila fue destruida.",true);
}

// Pruebas de volumen version 2 para un valor mayor al establecido en la pila.
void pruebas_pila_volumen_v2(){
  printf("INICIO DE PRUEBAS DE VOLUMEN VERSION 2\n");
  // Creo una pila.
  pila_t* pila=pila_crear();
  // Defino la cantidad de elementos a apilar.
  int cantidad=500;
  int arreglo[cantidad];
  // Empiezo a apilar los elementos.
  bool ok=true;
  for (int i=0;i<=cantidad;i++){
    arreglo[i]=i;
    ok &=pila_apilar(pila,&arreglo[i]);
  }
  print_test("Se puedieron apilar todos los elementos",ok);
  // Compruebo que todo lo apilado sea correcto mientras se desapilan los elementos.
  ok=true;
  for (int i=cantidad;i>=0;i--){
    ok &=*(int*)pila_desapilar(pila)==i;
  }
  print_test("Se pudieron verificar todos los elementos",ok);
  // Compruebo que la pila este vacia y que el tope sea NULL.
  print_test("La pila esta vacia",pila_esta_vacia(pila));
  print_test("El tope es NULL",!pila_ver_tope(pila));
  // Destruyo la pila.
  pila_destruir(pila);
  print_test("La pila fue destruida",true);
}

// Ejecucion de pruebas del alumno.
void pruebas_pila_alumno(){
  printf("INICIANDO PRUEBAS PILA APUNANDO A NULL\n");
  pila_t* ejemplo = NULL;
  print_test("Puntero inicializado a NULL",ejemplo==NULL);
  pruebas_pila_operaciones_invalidas_pila_vacia();
  pruebas_pila_apilar_desapilar();
  pruebas_pila_volumen_v1();
  pruebas_pila_volumen_v2();
}
