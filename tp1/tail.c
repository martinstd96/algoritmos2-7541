#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cola.h"

// Destruye una cadena.
// Pre: la cadena fue creada:
void destruir_cadenas(void* cadena){
  free(cadena);
}

// Imprime el mensaje recibido y devuelve 1.
int imprimir_mensaje(char* mensaje){
  fprintf(stderr, "%s\n", mensaje);
  return 1;
}
/*
// Funcion que enmascara la funcion destruir_cadenas.
// Pre: la cadena fue creada.
void destruir_cadenas_wrapper(void* cadena){
  destruir_cadenas(cadena);
}*/

// Funcion que se encarga de la ejecucion del programa.
// Pre: recibe la cantidad de parametros que recibe el ejecutable y un vector
// con los parametros que recibe el ejecutable.
// Post: devuelve 1 en caso de algun error o 0 en caso de que todo se haya ejecutado
// normalmente.
int obtener_tail(size_t imprimir_lineas){
  char* linea=NULL;
  size_t capacidad=0;
  ssize_t leidos;
  cola_t* cola_lineas=cola_crear();
  if (!cola_lineas){
    return imprimir_mensaje("Ha ocurrido un error");
  }
  int contador=0;
  while ( (leidos=getline(&linea, &capacidad, stdin)) > 0 ){
    size_t largo=strlen(linea)+2;
    char* cadena_auxiliar=malloc(sizeof(char)*largo);
    if (!cadena_auxiliar){
      cola_destruir(cola_lineas,destruir_cadenas);
      free(linea);
      return imprimir_mensaje("Ha ocurrido un error");
    }
    memcpy(cadena_auxiliar,&linea[0],largo);
    if (contador<imprimir_lineas){
      cola_encolar(cola_lineas,cadena_auxiliar);
    }
    else{
      char* cadena_desencolar=cola_desencolar(cola_lineas);
      destruir_cadenas(cadena_desencolar);
      cola_encolar(cola_lineas,cadena_auxiliar);
    }
    contador++;
  }
  while (!cola_esta_vacia(cola_lineas)){
    char* cadena_desencolar=cola_desencolar(cola_lineas);
    fprintf(stdout, "%s", cadena_desencolar);
    destruir_cadenas(cadena_desencolar);
  }
  cola_destruir(cola_lineas,NULL);
  free(linea);
  return 0;
}

// Funcion principal del programa.
// Pre: recibe la cantidad de parametros que recibe el ejecutable y un vector
// con los parametros que recibe el ejecutable.
int main(int argc,char* argv[]){
  if (argc != 2){
    return imprimir_mensaje("Cantidad de parametros erronea");
  }
  char* cadena_parametro=argv[1];
  size_t len=strlen(cadena_parametro);
  for (size_t i=0; i<len; i++){
    if (isdigit(cadena_parametro[i])==0){
      return imprimir_mensaje("Tipo de parametro incorrecto");
    }
  }
  size_t imprimir_lineas=(size_t)atoi(argv[1]);
  int resultado=obtener_tail(imprimir_lineas);
  return resultado;
}
