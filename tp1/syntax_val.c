#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pila.h"

// Imprime el mensaje recibido y devuelve 1.
int imprimir_mensaje(char* mensaje){
  fprintf(stderr, "%s\n", mensaje);
  return 1;
}

// Devuelve true si el caracter se encuentra en el vector, false en caso contrario.
bool esta_en_vector(char* vector, char* caracter){
  for (int i=0; vector[i]; i++){
    if (vector[i]==*caracter) return true;
  }
  return false;
}

// Devuelve la posicion del caracter que esta dentro del vector, si no la encuentra
// devuelve -1.
int obtener_posicion(char* vector, char* caracter){
  for (int i=0; vector[i]; i++){
    if (vector[i]==*caracter) return i;
  }
  return -1;
}

// Indica si la sintaxis es invalida y destruye la pila recibida.
// Pre: la pila fue creada.
bool es_invalida(pila_t* pila){
  pila_destruir(pila);
  return false;
}

// Indica si la sintaxis de un archivo ingresado por la entrada estandar es valida
// o no.
// Pre: linea_actual, vector_cierran y vector_abren fueron creados.
// Post: devulve true en el caso de que la sintaxis sea valida o este
// balanceada, false en caso contrario o en caso de que haya ocurrido algun error.
bool es_valida_sintaxis(char* linea_actual,char* vector_cierran,char* vector_abren){
  bool ok=true;
  pila_t* pila_contenedora=pila_crear();
  if (!pila_contenedora){
    fprintf(stderr, "Ha ocurrido un error\n");
    return false;
  }
  int comilla=0;
  for (int i=0; linea_actual[i]; i++){
    char* caracter=&linea_actual[i];
    if ((esta_en_vector(vector_abren,caracter) || esta_en_vector(vector_cierran,caracter)) && comilla%2==0){
      if (esta_en_vector(vector_abren, caracter)){
        pila_apilar(pila_contenedora, caracter);
      }
      else{
        if (pila_esta_vacia(pila_contenedora)){
          pila_destruir(pila_contenedora);
          return false;
        }
        int posicion=obtener_posicion(vector_cierran, caracter);
        char* caracter_actual=pila_desapilar(pila_contenedora);
        if (vector_abren[posicion]!=*caracter_actual){
          pila_destruir(pila_contenedora);
          return false;
        }
      }
    }
    if (*caracter=='\'') comilla++;
  }
  if (!pila_esta_vacia(pila_contenedora)) return es_invalida(pila_contenedora);
  ok=comilla%2==0;
  pila_destruir(pila_contenedora);
  return ok;
}

// Valida la sintaxis del archivo pasado por entrada estandar.
// Post: devuelve 1 en caso de algun error o 0 en caso de que todo se haya ejecutado
// normalmente.
int validacion_de_sintaxis(){
  int longitud=3;
  char* vector_cierran=malloc(sizeof(char)*longitud+1);
  if (!vector_cierran){
    return imprimir_mensaje("Ha ocurrido un error");
  }
  char* vector_abren=malloc(sizeof(char)*longitud+1);
  if (!vector_abren){
    free(vector_cierran);
    return imprimir_mensaje("Ha ocurrido un error");
  }
  vector_cierran[0]=')'; vector_cierran[1]=']'; vector_cierran[2]='}'; vector_cierran[3]='\0';
  vector_abren[0]='('; vector_abren[1]='['; vector_abren[2]='{'; vector_abren[3]='\0';
  char* linea=NULL;
  size_t capacidad=0;
  ssize_t leidos;
  bool ok;
  while ( (leidos=getline(&linea, &capacidad, stdin)) > 0 ){
    char* linea_actual=linea;
    ok=es_valida_sintaxis(linea_actual,vector_cierran,vector_abren);
    if (!ok) fprintf(stdout,"ERROR\n");
    else fprintf(stdout, "OK\n");
  }
  free(vector_abren);
  free(vector_cierran);
  free(linea);
  return 0;
}

// Funcion principal del programa.
int main(){
  int resultado=validacion_de_sintaxis();
  return resultado;
}
