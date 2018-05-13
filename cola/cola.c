#include "cola.h"
#include <stdlib.h>

// El nodo esta planteado como un nodo generico.
typedef struct nodo{
  void* dato;
  struct nodo* proximo;
} nodo_t;

// Crea un nodo.
// Post: devuelve un nodo que contiene el valor pasado por parametro y el proximo
// es NULL.
nodo_t* nodo_crear(void* valor){
  nodo_t* nodo=malloc(sizeof(nodo_t));
  if (!nodo){
    return NULL;
  }
  nodo->dato=valor;
  nodo->proximo=NULL;
  return nodo;
}

// Destruye al nodo.
// Pre: el nodo fue creado.
// Post: se eliminó el valor que almacenaba el nodo.
void nodo_destruir(nodo_t* nodo){
  free(nodo);
}

struct cola{
  nodo_t* primero;
  nodo_t* ultimo;
};

cola_t* cola_crear(){
  cola_t* cola=malloc(sizeof(cola_t));
  if (!cola){
    return NULL;
  }
  cola->primero=NULL;
  cola->ultimo=NULL;
  return cola;
}

bool cola_esta_vacia(const cola_t* cola){
  return !cola->primero;
}

bool cola_encolar(cola_t* cola,void* valor){
  nodo_t* nodo_nuevo=nodo_crear(valor);
  if (!nodo_nuevo){
    return false;
  }
  if (!cola_esta_vacia(cola)){
    cola->ultimo->proximo=nodo_nuevo;
  }
  else{
    cola->primero=nodo_nuevo;
  }
  cola->ultimo=nodo_nuevo;
  return true;
}

void* cola_ver_primero(const cola_t* cola){
  if (cola_esta_vacia(cola)){
    return NULL;
  }
  return cola->primero->dato;
}

void* cola_desencolar(cola_t* cola){
  if (cola_esta_vacia(cola)){
    return NULL;
  }
  void* valor=cola->primero->dato;
  nodo_t* nodo_actual=cola->primero;
  cola->primero=cola->primero->proximo;
  if (cola_esta_vacia(cola)){
    cola->ultimo=NULL;
  }
  nodo_destruir(nodo_actual);
  return valor;
}

void cola_destruir(cola_t* cola, void destruir_dato(void*)){
  while (!cola_esta_vacia(cola)){
    void* dato=cola_desencolar(cola);
    if (destruir_dato){
      destruir_dato(dato);
    }
  }
  free(cola);
}
