#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Funcion privada de split que genera palabras de str a partir de sep.
// Pre: str existe e inicio y fin son posiciones validas de str.
// Post: devuelve un vector con las letras de str que estan entre inicio y fin.
char* _split(const char* str,int inicio,size_t fin){
  int longitud=(int)fin - inicio;
  char* vector_slice=malloc(sizeof(char)*longitud+1);
  if (!vector_slice) return NULL;
  memcpy(vector_slice,&str[inicio],(size_t)longitud);
  vector_slice[longitud]='\0';
  return vector_slice;
}

// Pre: recibe un cadena str y un caracter sep y cuenta la cantidad de veces que
// se repite el mismo.
// Post: devuelve la cantidad de apariciones de sep en str.
int obtener_apariciones(const char* str,char sep){
  int apariciones=0;
  for (int i=0; str[i]; i++){
    if (str[i]==sep) apariciones++;
  }
  return apariciones;
}

char** split(const char* str,char sep){
  if (!str || !sep) return NULL;
  int apariciones=obtener_apariciones(str,sep);
  int longitud=apariciones+2;
  char** vector_split=malloc(sizeof(char*)*longitud);
  if (!vector_split) return NULL;
  vector_split[longitud-1]=NULL;
  size_t longitud_str=strlen(str);
  if (!apariciones){
    vector_split[0]=_split(str,0,longitud_str);
    return vector_split;
  }
  int inicio=0;
  int j=0;
  for (int i=0; i<longitud_str+1; i++){
    if (str[i]==sep || !str[i]){
      vector_split[j]=_split(str,inicio,i);
      int nuevo_inicio=i+1;
      inicio=nuevo_inicio;
      j++;
    }
  }
  return vector_split;
}

// Funcion privada de join que concatena las palabras de strv.
// Pre: strv y vector_join fueron creados.
// Post: se agregrego la cadena pasada a vector_join.
void _join(char* vector_join,char* cadena){
  strcpy(vector_join,cadena);
}

char* join(char** strv,char sep){
  if (!strv || !sep) return NULL;
  size_t cantidad=0;
  size_t largo=0;
  for (int i=0; strv[i]; i++){
    largo+=strlen(strv[i]);
    cantidad++;
  }
  size_t longitud=largo+cantidad;
  if (!longitud) longitud=1;
  char* vector_join=malloc(sizeof(char)*longitud);
  if (!vector_join) return NULL;
  if (!cantidad){
    vector_join[0]='\0';
    return vector_join;
  }
  size_t largo1=strlen(strv[0]);
  _join(vector_join,strv[0]);
  for (int i=1; strv[i]; i++){
    vector_join[largo1]=sep;
    size_t largo2=strlen(strv[i])+1;
    _join(&vector_join[largo1+1],strv[i]);
    largo1+=largo2;
  }
  return vector_join;
}

void free_strv(char* strv[]){
  for (int i=0; strv[i]; i++){
    free(strv[i]);
  }
  free(strv);
}
