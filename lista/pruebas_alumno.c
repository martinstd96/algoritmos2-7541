#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define CANTIDAD_PRUEBAS_VOLUMEN 2400
#define MITAD_CANTIDAD_PRUEBAS_VOLUMEN 1200
#define CANTIDAD_PRUEBAS_ITER_INTERNO 30
#define CANTIDAD_PRUEBAS_ITER_EXTERNO 20

// Funcion que enmascara la funcion pila_destruir.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir_wrapper(void* pila){
  pila_destruir(pila);
}

// Pruebas para una lista vacia.
void pruebas_lista_operaciones_invalidas_lista_vacia(){
  printf("INICIO DE PRUEBAS OPERACIONES INVALIDAS CON LISTA VACIA.\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  // Inicio de pruebas.
  print_test("Crear lista",lista!=NULL);
  print_test("La lista esta vacia es true",lista_esta_vacia(lista));
  print_test("Ver primero cunado la lista esta vacia es NULL",!lista_ver_primero(lista));
  print_test("Ver ultimo cuando la lista esta vacia es NULL",!lista_ver_ultimo(lista));
  print_test("Borrar el primero cuando la lista esta vacia es NULL",!lista_borrar_primero(lista));
  print_test("El largo de lista cunado esta vacia es cero",lista_largo(lista)==0);
  // Destruyo la lista.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Pruebas de insertado.
void pruebas_lista_insertar(){
  printf("INICIO DE PREUBAS DE INSERTADO.\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  // Inicio de pruebas.
  print_test("Crear lista",lista!=NULL);
  int valor1=8;
  int valor2=11;
  int valor3=16;
  print_test("Insertar un dato (8) al principio es true",lista_insertar_primero(lista,&valor1));
  print_test("Insertar un dato (11) al final es true",lista_insertar_ultimo(lista,&valor2));
  print_test("Insertar un dato (NULL) al final es true",lista_insertar_ultimo(lista,NULL));
  print_test("Insertar un dato (16) al principio es true",lista_insertar_primero(lista,&valor3));
  print_test("La lista esta vacia es false",!lista_esta_vacia(lista));
  print_test("El largo de la lista es 4",lista_largo(lista)==4);
  print_test("Ver primero es 16",*(int*)lista_ver_primero(lista)==16);
  print_test("Ver ultimo es NULL",lista_ver_ultimo(lista)==NULL);
  print_test("Borrar el primero de la lista es 16",*(int*)lista_borrar_primero(lista)==16);
  print_test("Ver el primero es 8",*(int*)lista_ver_primero(lista)==8);
  print_test("El largo de la lista es 3",lista_largo(lista)==3);
  print_test("Borrar el primero es 8",*(int*)lista_borrar_primero(lista)==8);
  print_test("Ver el primero es 11",*(int*)lista_ver_primero(lista)==11);
  print_test("El largo de la lista es 2",lista_largo(lista)==2);
  print_test("Borrar el primero es 11",*(int*)lista_borrar_primero(lista)==11);
  print_test("Ver el primero es NULL",lista_ver_primero(lista)==NULL);
  print_test("El largo de la lista es 1",lista_largo(lista)==1);
  print_test("Borrar el primero es NULL",lista_borrar_primero(lista)==NULL);
  print_test("La lista esta vacia es true",lista_esta_vacia(lista));
  print_test("El largo de lista cunado esta vacia es cero",lista_largo(lista)==0);
  // Destruyo la lista.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Pruebas de volumen.
void pruebas_lista_volumen(){
  printf("INICIO DE PRUEBAS DE VOLUMEN\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  //Defino la cantidad de elementos a insertar.
  int arreglo[CANTIDAD_PRUEBAS_VOLUMEN];
  // Empiezo a insertar los elementos, primero al principio 500 y luego 500 al final.
  bool ok=true;
  for (int i=0;i<MITAD_CANTIDAD_PRUEBAS_VOLUMEN;i++){
    arreglo[i]=i;
    ok &=lista_insertar_primero(lista,&arreglo[i]);
  }
  for (int i=MITAD_CANTIDAD_PRUEBAS_VOLUMEN;i<CANTIDAD_PRUEBAS_VOLUMEN;i++){
    arreglo[i]=i;
    ok &=lista_insertar_ultimo(lista,&arreglo[i]);
  }
  print_test("Se pudieron insertar todos los elementos",ok);
  print_test("Ver primero es 1199",*(int*)lista_ver_primero(lista)==1199);
  print_test("El ultimo es 2399",*(int*)lista_ver_ultimo(lista)==2399);
  print_test("El largo es 2400",lista_largo(lista)==2400);
  // Compruebo que los primeros 1400 elementos de lo insertado sea correcto.
  ok=true;
  for (int i=MITAD_CANTIDAD_PRUEBAS_VOLUMEN-1;i>=0;i--){
    ok &=*(int*)lista_borrar_primero(lista)==i;
  }
  for (int i=MITAD_CANTIDAD_PRUEBAS_VOLUMEN;i<MITAD_CANTIDAD_PRUEBAS_VOLUMEN+200;i++){
    ok &=*(int*)lista_borrar_primero(lista)==i;
  }
  print_test("Se pudieron verificar los primeros 1400 elementos insertados",ok);
  // Compruebo que la lista no este vacia y que el largo es 1000.
  print_test("La lista no esta vacia",!lista_esta_vacia(lista));
  print_test("El largo es 1000",lista_largo(lista)==1000);
  // Destruyo la lista con los elementos que quedaron.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Pruebas de invariante.
void pruebas_invariante(){
  printf("INICIO DE PRUEBAS DE INVARIANTE\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  print_test("Crear lista",lista!=NULL);
  // Datos a insertar.
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
  ok &=lista_insertar_primero(lista,pila1);
  ok &=lista_insertar_primero(lista,pila2);
  ok &=lista_insertar_primero(lista,pila3);
  ok &=lista_insertar_ultimo(lista,pila4);
  ok &=lista_insertar_ultimo(lista,pila5);
  ok &=lista_insertar_ultimo(lista,pila6);
  print_test("Se pudieron insertar todas las pilas",ok);
  // Destruyo la lista con los pilas y los valores que se apilaron.
  lista_destruir(lista,pila_destruir_wrapper);
  print_test("La lista fue destruida",true);
}

//------------------------------------------------------------------------------

// Imprime todos los datos.
bool imprimir_todos(void* dato,void* extra){
  printf(" %d,",*(int*)dato);
  return true;
}

// Imprime algunos datos hasta que extra llegue a 10.
bool imprimir_algunos(void* dato,void* extra){
  if (*(size_t*)extra>=10){
    return false;
  }
  *(size_t*)extra+=1;
  printf(" %d,",*(int*)dato);
  return true;
}

// Se suman todos los datos a extra.
bool sumar_todos(void* dato,void* extra){
  *(int*)extra+=*(int*)dato;
  return true;
}

// Prueba iterador interno imprimir todos los datos.
void pruebas_lista_iter_interno_imprimir_datos(){
  printf("INICIO DE PRUEBAS ITERADOR INTERNO IMPRIMIR TODOS LOS DATOS\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  //Defino la cantidad de elementos a insertar.
  int arreglo[CANTIDAD_PRUEBAS_ITER_INTERNO];
  // Empiezo a insertar los elementos al final.
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_ITER_INTERNO;i++){
    arreglo[i]=i;
    ok &=lista_insertar_ultimo(lista,&arreglo[i]);
  }
  print_test("Se pudieron insertar todos los elementos",ok);
  lista_iterar(lista,imprimir_todos,NULL);
  // Destruyo la lista.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Prueba iterador interno imprimir algunos datos.
void pruebas_lista_iter_interno_imprimir_algunos_datos(){
  printf("INICIO DE PRUEBAS ITERADOR INTERNO IMPRIMIR ALGUNOS DATOS\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  //Defino la cantidad de elementos a insertar.
  int arreglo[CANTIDAD_PRUEBAS_ITER_INTERNO];
  // Empiezo a insertar los elementos al final.
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_ITER_INTERNO;i++){
    arreglo[i]=i;
    ok &=lista_insertar_ultimo(lista,&arreglo[i]);
  }
  print_test("Se pudieron insertar todos los elementos",ok);
  size_t contador=0;
  lista_iterar(lista,imprimir_algunos,&contador);
  // Destruyo la lista.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Prueba iterador interno sumar datos.
void pruebas_lista_iter_interno_sumar_datos(){
  printf("INICIO DE PRUEBAS ITERADOR INTERNO SUMAR DATOS\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  //Defino la cantidad de elementos a insertar.
  int arreglo[CANTIDAD_PRUEBAS_ITER_INTERNO];
  // Empiezo a insertar los elementos al final.
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_ITER_INTERNO;i++){
    arreglo[i]=i;
    ok &=lista_insertar_ultimo(lista,&arreglo[i]);
  }
  print_test("Se pudieron insertar todos los elementos",ok);
  int suma=0;
  lista_iterar(lista,sumar_todos,&suma);
  printf(" %d\n",suma);
  // Destruyo la lista.
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

//------------------------------------------------------------------------------

// Pruebas de insertado del iterador externo.
void pruebas_lista_iter_externo_insertar(){
  printf("INICIO DE PRUEBAS DE INSERTADO CON ITERADOR EXTERNO\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  print_test("Crear lista",lista!=NULL);
  // Creo un iterador.
  lista_iter_t* iter=lista_iter_crear(lista);
  print_test("Crear iterador externo",iter!=NULL);
  // Inicio de pruebas.
  int valor1=7;
  int valor2=23;
  int valor3=12;
  print_test("Insertar un elemento (7) cuando se creo el iterador es al principio y true",lista_iter_insertar(iter,&valor1));
  print_test("La longitud de la lista es 1",lista_largo(lista)==1);
  print_test("El elemento que se encuentra al principio es 7",*(int*)lista_ver_primero(lista)==valor1);
  print_test("El elemento actual del iterador es 7",*(int*)lista_iter_ver_actual(iter)==valor1);
  int arreglo[CANTIDAD_PRUEBAS_ITER_EXTERNO];
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_ITER_EXTERNO;i++){
    arreglo[i]=i;
    ok &=lista_iter_insertar(iter,&arreglo[i]);
  }
  print_test("El iterador pudo insertar los elementos",ok);
  ok=true;
  for (size_t i=0;i<lista_largo(lista)/2;i++){
    ok &=lista_iter_avanzar(iter);
  }
  print_test("El iterador avanzo correctamente hasta la mitad",ok);
  print_test("Se inserto un elemento (23) en la mitad de la lista",lista_iter_insertar(iter,&valor2));
  ok=true;
  while (!lista_iter_al_final(iter)){
    ok &=lista_iter_avanzar(iter);
  }
  print_test("El iterador avanzo correctamente hasta el final",ok);
  print_test("Insertar un elemento (12) al final es true",lista_iter_insertar(iter,&valor3));
  print_test("El elemento que se encuentra al final es 12",*(int*)lista_ver_ultimo(lista)==valor3);
  print_test("El elemento actual del iterador es 12",*(int*)lista_iter_ver_actual(iter)==12);
  // Destruyo el iterador y la lista.
  lista_iter_destruir(iter);
  print_test("El iterador fue destruido",true);
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Pruebas de borrado del iterador externo.
void pruebas_lista_iter_externo_borrar(){
  printf("INICIO DE PRUEBAS DE BORRADO CON ITERADOR EXTERNO\n");
  // Creo una lista.
  lista_t* lista=lista_crear();
  print_test("Crear lista",lista!=NULL);
  // Creo un iterador.
  lista_iter_t* iter=lista_iter_crear(lista);
  print_test("Crear iterador externo",iter!=NULL);
  // Inicio de pruebas.
  int valor=22;
  int arreglo[CANTIDAD_PRUEBAS_ITER_EXTERNO];
  bool ok=true;
  for (int i=0;i<CANTIDAD_PRUEBAS_ITER_EXTERNO;i++){
    arreglo[i]=i;
    ok &=lista_iter_insertar(iter,&arreglo[i]);
  }
  print_test("El iterador pudo insertar los elementos",ok);
  print_test("El primer elemento de la lista es 19",*(int*)lista_ver_primero(lista)==arreglo[19]);
  print_test("El iterador borro el primer elemento",*(int*)lista_iter_borrar(iter)==arreglo[19]);
  print_test("El actual del iterador es 18",*(int*)lista_iter_ver_actual(iter)==arreglo[18]);
  print_test("El primer elemento de la lista es 18",*(int*)lista_ver_primero(lista)==arreglo[18]);
  ok=true;
  for (size_t i=0;i<lista_largo(lista)/2;i++){
    ok &=lista_iter_avanzar(iter);
  }
  print_test("El iterador avanzo correctamente hasta la mitad",ok);
  print_test("EL iterador borro el elemento del medio",*(int*)lista_iter_borrar(iter)==arreglo[9]);
  ok=true;
  while (!lista_iter_al_final(iter)){
    ok &=lista_iter_avanzar(iter);
  }
  print_test("Se inserto un elemento (22) al final correctamente",lista_iter_insertar(iter,&valor));
  print_test("El ultimo de la lista es 22",*(int*)lista_ver_ultimo(lista)==valor);
  print_test("El iterador borro el ultimo",*(int*)lista_iter_borrar(iter)==valor);
  print_test("El ultimo de la lista es 0",*(int*)lista_ver_ultimo(lista)==arreglo[0]);
  // Destruyo el iterador y la lista.
  lista_iter_destruir(iter);
  print_test("El iterador fue destruido",true);
  lista_destruir(lista,NULL);
  print_test("La lista fue destruida",true);
}

// Ejecucion de pruebas del alumno.
void pruebas_lista_alumno(){
  pruebas_lista_operaciones_invalidas_lista_vacia();
  pruebas_lista_insertar();
  pruebas_lista_volumen();
  pruebas_invariante();
  pruebas_lista_iter_interno_imprimir_datos();
  pruebas_lista_iter_interno_imprimir_algunos_datos();
  pruebas_lista_iter_interno_sumar_datos();
  pruebas_lista_iter_externo_insertar();
  pruebas_lista_iter_externo_borrar();
}
