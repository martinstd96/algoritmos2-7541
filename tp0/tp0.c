/*Nombre: Carlos Martin Stefanelli D'Elias.
 *Padron: 100488.
 */

#include "tp0.h"

/* swap() intercambia dos valores enteros.
 */
void swap(int *x,int *y){
  int auxiliar=*x;
  *x=*y;
  *y=auxiliar;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[],int n){
  if(n==0){
    return -1;
  }
  int posicion_maxima=0;
  for(int i=1;i<n;i++){
    if(vector[posicion_maxima]<vector[i]){
      posicion_maxima=i;
    }
  }
  return posicion_maxima;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2){
  for(int i=0;i<n1 && i<n2;i++){
    if(vector1[i]!=vector2[i]){
      return vector1[i]<vector2[i]? -1:1;
    }
  }
  if(n1!=n2){
    return n1<n2? -1:1;
  }
  return 0;
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n){
  for(int i=0;i<n;i++){
    int posicion_maxima=maximo(vector,n-i);
    swap(&vector[posicion_maxima],&vector[n-1-i]);
  }
}
