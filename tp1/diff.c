#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Imprime el mensaje recibido y devuelve 1.
int imprimir_mensaje(char* mensaje){
  fprintf(stderr, "%s\n", mensaje);
  return 1;
}

// Funcion que se encarga de la ejecucion del programa.
// Pre: recibe la cantidad de parametros que recibe el ejecutable y un vector
// con los parametros que recibe el ejecutable.
// Post: devuelve 1 en caso de algun error o 0 en caso de que todo se haya ejecutado
// normalmente.
int obtener_diff(const char* nombre_archivo1,const char* nombre_archivo2){
  FILE* archivo1=fopen(nombre_archivo1,"r");
  if (!archivo1){
    return imprimir_mensaje("Archivo erroneo");
  }
  FILE* archivo2=fopen(nombre_archivo2,"r");
  if (!archivo2){
    fclose(archivo1);
    return imprimir_mensaje("Archivo erroneo");
  }
  char* linea1=NULL;
  size_t capacidad1=0;
  ssize_t leidos1;

  char* linea2=NULL;
  size_t capacidad2=0;
  ssize_t leidos2;
  for (int i=1; 1; i++){
    leidos1=getline(&linea1, &capacidad1, archivo1);
    leidos2=getline(&linea2, &capacidad2, archivo2);
    if (leidos1==EOF && leidos2==EOF) break;
    if (leidos1==EOF || leidos2==EOF){
      if (leidos1>EOF) fprintf(stdout,"Diferencia en linea %d\n" "< %s" "---\n" "> \n",i,linea1);
      else fprintf(stdout,"Diferencia en linea %d\n" "< \n" "---\n" "> %s",i,linea2);
      continue;
    }
    if (strcmp(linea1,linea2)!=0) fprintf(stdout,"Diferencia en linea %d\n" "< %s" "---\n" "> %s",i,linea1,linea2);
  }
  free(linea1);
  free(linea2);
  fclose(archivo1);
  fclose(archivo2);
  return 0;
}

// Funcion principal del programa.
// Pre: recibe la cantidad de parametros que recibe el ejecutable y un vector.
// con los parametros que recibe el ejecutable.
int main(int argc,char* argv[]){
  if (argc != 3){
    return imprimir_mensaje("Cantidad de parametros erronea");
  }
  int resultado=obtener_diff(argv[1],argv[2]);
  return resultado;
}
