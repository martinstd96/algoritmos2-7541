#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTIDAD_PRUEBAS_VOLUMEN 5000
#define CANTIDAD_PRUEBAS_ARR 9
#define CANTIDAD_PRUEBAS_HEAP_SORT 15

int cmp_cadenas(const void* a, const void* b){
  return strcmp(a, b);
}

int cmp_numeros(const void* a, const void* b){
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int _cmp_numeros(const void* a, const void* b){
  if (*(int*)a < *(int*)b) return -1;
  if (*(int*)a > *(int*)b) return 1;
  return 0;
}

char* obtener_cadena(const char* cadena){
  size_t largo=strlen(cadena);
  char* cadena_copia=malloc(sizeof(char) * largo+1);
  if (!cadena_copia) return NULL;
  strcpy(cadena_copia, cadena);
  return cadena_copia;
}

void pruebas_heap_vacio(){
  printf("INICIO DE PRUEBAS HEAP VACIO.\n");
	heap_t* heap = heap_crear(cmp_cadenas);

	print_test("heap esta vacio", heap_esta_vacio(heap));
	print_test("cantidad 0", heap_cantidad(heap) == 0);
	print_test("desencolar es falso", !heap_desencolar(heap));
	print_test("ver el maximo es falso", !heap_ver_max(heap));

	heap_destruir(heap, NULL);
	print_test("Destruyo el heap", true);
}

void pruebas_heap_encolar_desencolar(){
  printf("INICIO DE PRUEBAS DE ENCOLAR Y DESENCOLAR.\n");
	heap_t* heap = heap_crear(cmp_cadenas);

	char* valor1 = "leonel";
	char* valor2 = "martin";
	char* valor3 = "perro";
	char* valor4 = "gato";
	char* valor5 = "algoritmos";
	char* valor6 = "programacion";

	print_test("heap esta vacio", heap_esta_vacio(heap));
	print_test("cantidad 0", heap_cantidad(heap) == 0);

	bool ok = true;

	ok = heap_encolar(heap,valor1);
	ok = heap_encolar(heap,valor2);
	ok = heap_encolar(heap,valor3);
	ok = heap_encolar(heap,valor4);
	ok = heap_encolar(heap,valor5);
	ok = heap_encolar(heap,valor6);

	print_test("se encolaron los 6 valores correctamente", ok);
	print_test("cantidad de elementos es 6", heap_cantidad(heap) == 6);
  print_test("el heap no esta vacio", !heap_esta_vacio(heap));
  print_test("el maximo es 'programacion' ", heap_ver_max(heap) == valor6);

  ok = heap_desencolar(heap) == valor6;
  ok = heap_desencolar(heap) == valor3;
  ok = heap_desencolar(heap) == valor2;
  ok = heap_desencolar(heap) == valor1;
  ok = heap_desencolar(heap) == valor4;
  ok = heap_desencolar(heap) == valor5;
  print_test("se desencolaron los 6 elementos correctamente", ok);
  print_test("la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("el heap esta vacio", heap_esta_vacio(heap));

	heap_destruir(heap, NULL);
	print_test("Destruyo el heap", true);
}

void pruebas_heap_encolar_datos_dinamicos(){
  printf("INICIO DE PRUEBAS DE ENCOLAR CON DATOS DINAMICOS.\n");
  heap_t* heap = heap_crear(cmp_cadenas);
  char* valor1 = obtener_cadena("juan");
  char* valor2 = obtener_cadena("pepe");
  char* valor3 = obtener_cadena("delfin");
  char* valor4 = obtener_cadena("caballo");
  char* valor5 = obtener_cadena("zorro");
  char* valor6 = obtener_cadena("genesis");
  char* valor7 = obtener_cadena("bills");

  bool ok = true;
  ok = heap_encolar(heap,valor1);
  ok = heap_encolar(heap,valor2);
  ok = heap_encolar(heap,valor3);
  ok = heap_encolar(heap,valor4);
  ok = heap_encolar(heap,valor5);
  ok = heap_encolar(heap,valor6);
  ok = heap_encolar(heap,valor7);
  print_test("se encolaron los 7 valores correctamente", ok);
	print_test("cantidad de elementos es 7", heap_cantidad(heap) == 7);
  print_test("el heap no esta vacio", !heap_esta_vacio(heap));
  print_test("el maximo es 'zorro' ", heap_ver_max(heap) == valor5);

  heap_destruir(heap, free);
  print_test("Destruyo el heap", true);
}

void pruebas_heap_operaciones_crear_arr(){
  printf("INICIO DE PRUEBAS HEAP OPERACIONES CON CREAR CON ARREGLO\n");
  int arr[CANTIDAD_PRUEBAS_ARR]={3,33,10,9,56,4,20,36,47};
  int* _arreglo=malloc(sizeof(int) * CANTIDAD_PRUEBAS_ARR);
  for (int i=0; i<CANTIDAD_PRUEBAS_ARR; i++)_arreglo[i]=arr[i];
  void* arreglo[CANTIDAD_PRUEBAS_ARR];
  for (int i=0; i<CANTIDAD_PRUEBAS_ARR; i++) arreglo[i]=_arreglo+i;

  heap_t* heap = heap_crear_arr(arreglo,CANTIDAD_PRUEBAS_ARR,_cmp_numeros);
  print_test("cantidad de elementos es 9", heap_cantidad(heap) == CANTIDAD_PRUEBAS_ARR);
  print_test("el maximo es 56 ", heap_ver_max(heap) == arreglo[4]);

  bool ok = true;
  ok = heap_desencolar(heap) == arreglo[4];
  ok = heap_desencolar(heap) == arreglo[8];
  ok = heap_desencolar(heap) == arreglo[7];
  ok = heap_desencolar(heap) == arreglo[1];
  ok = heap_desencolar(heap) == arreglo[6];
  ok = heap_desencolar(heap) == arreglo[2];
  ok = heap_desencolar(heap) == arreglo[3];
  ok = heap_desencolar(heap) == arreglo[5];
  ok = heap_desencolar(heap) == arreglo[0];
  print_test("se desencolaron los 9 elementos correctamente", ok);
  print_test("la cantidad de elementos es 0", heap_cantidad(heap) == 0);
  print_test("el heap esta vacio", heap_esta_vacio(heap));

  free(_arreglo);
  heap_destruir(heap,NULL);
  print_test("Destruyo el heap", true);
}

void pruebas_heap_volumen(){
  printf("INICIO DE PRUEBAS DE VOLUMEN\n");
  heap_t* heap = heap_crear(cmp_numeros);

  int arreglo[CANTIDAD_PRUEBAS_VOLUMEN];
  bool ok=true;
  for (int i=0; i<CANTIDAD_PRUEBAS_VOLUMEN; i++){
    arreglo[i] = i;
    ok = heap_encolar(heap,&arreglo[i]);
  }
  print_test("se pudieron encolar todos los elementos", ok);
  print_test("cantidad de elementos es 5000", heap_cantidad(heap) == CANTIDAD_PRUEBAS_VOLUMEN);
  print_test("el maximo es 4999", *(int*)heap_ver_max(heap) == arreglo[CANTIDAD_PRUEBAS_VOLUMEN-1]);

  for (int i=CANTIDAD_PRUEBAS_VOLUMEN-1; i >= CANTIDAD_PRUEBAS_VOLUMEN/2; i--) ok = *(int*)heap_desencolar(heap) == i;
  print_test("se desencolaron la mitad los elementos correctamente", ok);

  heap_destruir(heap, NULL);
	print_test("Destruyo el heap", true);
}

void pruebas_heap_sort(){
  printf("INICIO DE PRUEBAS DE HEAP SORT\n");
  int arr[CANTIDAD_PRUEBAS_HEAP_SORT]={0,33,10,9,56,4,20,36,47,-1,90,73,-31,15,88};
  int* _arreglo=malloc(sizeof(int) * CANTIDAD_PRUEBAS_HEAP_SORT);
  for (int i=0; i<CANTIDAD_PRUEBAS_HEAP_SORT; i++)_arreglo[i]=arr[i];
  void* arreglo[CANTIDAD_PRUEBAS_HEAP_SORT];
  for (int i=0; i<CANTIDAD_PRUEBAS_HEAP_SORT; i++) arreglo[i]=_arreglo+i;

  heap_sort(arreglo,CANTIDAD_PRUEBAS_HEAP_SORT,_cmp_numeros);

  bool ok=true;
  ok = *(int*)arreglo[0]==arr[12];
  ok = *(int*)arreglo[1]==arr[9];
  ok = *(int*)arreglo[2]==arr[0];
  ok = *(int*)arreglo[3]==arr[5];
  ok = *(int*)arreglo[4]==arr[3];
  ok = *(int*)arreglo[5]==arr[2];
  ok = *(int*)arreglo[6]==arr[13];
  ok = *(int*)arreglo[7]==arr[6];
  ok = *(int*)arreglo[8]==arr[1];
  ok = *(int*)arreglo[9]==arr[7];
  ok = *(int*)arreglo[10]==arr[8];
  ok = *(int*)arreglo[11]==arr[4];
  ok = *(int*)arreglo[12]==arr[11];
  ok = *(int*)arreglo[13]==arr[14];
  ok = *(int*)arreglo[14]==arr[10];
  print_test("el arreglo esta ordenado", ok);

  free(_arreglo);
}

void pruebas_heap_alumno() {
	pruebas_heap_vacio();
	pruebas_heap_encolar_desencolar();
  pruebas_heap_encolar_datos_dinamicos();
  pruebas_heap_operaciones_crear_arr();
  pruebas_heap_volumen();
  pruebas_heap_sort();
}
