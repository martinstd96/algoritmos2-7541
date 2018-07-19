#include "lista.h"
#include <stdlib.h>

#define TAMANIO_INICIAL 0
#define ESTA_VACIA NULL
#define NO_HAY_ACTUAL NULL

// El nodo esta planteado como un nodo generico.
typedef struct nodo{
  void* dato;
  struct nodo* proximo;
} nodo_lista_t;

// Crea un nodo.
// Post: devuelve un nodo que contiene el valor pasado por parametro y el proximo
// es NULL.
nodo_lista_t* nodo_lista_crear(void* valor){
  nodo_lista_t* nodo=malloc(sizeof(nodo_lista_t));
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
void nodo_lista_destruir(nodo_lista_t* nodo){
  free(nodo);
}

//------------------------------------------------------------------------------

struct lista{
  nodo_lista_t* primero;
  nodo_lista_t* ultimo;
  size_t largo;
};

lista_t* lista_crear(){
  lista_t* lista=malloc(sizeof(lista_t));
  if (!lista){
    return NULL;
  }
  lista->primero=NULL;
  lista->ultimo=NULL;
  lista->largo=TAMANIO_INICIAL;
  return lista;
}

size_t lista_largo(const lista_t* lista){
  return lista->largo;
}

bool lista_esta_vacia(const lista_t* lista){
  return !lista->primero;
}

bool lista_insertar_primero(lista_t* lista,void* dato){
  nodo_lista_t* nodo_nuevo=nodo_lista_crear(dato);
  if (!nodo_nuevo){
    return false;
  }
  if (!lista_esta_vacia(lista)){
    nodo_nuevo->proximo=lista->primero;
  }
  else{
    lista->ultimo=nodo_nuevo;
  }
  lista->primero=nodo_nuevo;
  lista->largo++;
  return true;
}

bool lista_insertar_ultimo(lista_t* lista,void* dato){
  nodo_lista_t* nodo_nuevo=nodo_lista_crear(dato);
  if (!nodo_nuevo){
    return false;
  }
  if (!lista_esta_vacia(lista)){
    lista->ultimo->proximo=nodo_nuevo;
  }
  else{
    lista->primero=nodo_nuevo;
  }
  lista->ultimo=nodo_nuevo;
  lista->largo++;
  return true;
}

void* lista_ver_primero(const lista_t* lista){
  return lista_esta_vacia(lista)? ESTA_VACIA:lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
  return lista_esta_vacia(lista)? ESTA_VACIA:lista->ultimo->dato;
}

void* lista_borrar_primero(lista_t* lista){
  if (lista_esta_vacia(lista)){
    return ESTA_VACIA;
  }
  void* valor=lista->primero->dato;
  nodo_lista_t* nodo_actual=lista->primero;
  lista->primero=nodo_actual->proximo;
  if (!lista->primero){
    lista->ultimo=NULL;
  }
  nodo_lista_destruir(nodo_actual);
  lista->largo--;
  return valor;
}

void lista_destruir(lista_t* lista,void destruir_dato(void*)){
  while (!lista_esta_vacia(lista)){
    void* dato=lista_borrar_primero(lista);
    if (destruir_dato){
      destruir_dato(dato);
    }
  }
  free(lista);
}

//------------------------------------------------------------------------------

void lista_iterar(lista_t* lista,bool visitar(void* dato,void* extra),void* extra){
  nodo_lista_t* nodo_actual=lista->primero;
  while (nodo_actual){
    bool seguir=visitar(nodo_actual->dato,extra);
    if (!seguir){
      break;
    }
    nodo_actual=nodo_actual->proximo;
  }
}

//------------------------------------------------------------------------------

struct lista_iter{
  nodo_lista_t* actual;
  nodo_lista_t* anterior;
  lista_t* lista;
};

lista_iter_t* lista_iter_crear(lista_t* lista){
  lista_iter_t* iter=malloc(sizeof(lista_iter_t));
  if (!iter){
    return NULL;
  }
  iter->actual=lista->primero;
  iter->anterior=NULL;
  iter->lista=lista;
  return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
  if (!iter->actual){
    return false;
  }
  iter->anterior=iter->actual;
  iter->actual=iter->actual->proximo;
  return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
  return !iter->actual? NO_HAY_ACTUAL:iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter){
  return !iter->actual;
}

bool lista_iter_insertar(lista_iter_t* iter,void* dato){
  nodo_lista_t* nodo_nuevo=nodo_lista_crear(dato);
  if (!nodo_nuevo){
    return false;
  }
  nodo_nuevo->proximo=iter->actual;
  if (!iter->actual){
    if (iter->anterior){
      iter->anterior->proximo=nodo_nuevo;
    }
    iter->lista->ultimo=nodo_nuevo;
  }
  if (!iter->anterior){
    iter->lista->primero=nodo_nuevo;
  }
  else{
    iter->anterior->proximo=nodo_nuevo;
  }
  iter->actual=nodo_nuevo;
  iter->lista->largo++;
  return true;
}

void* lista_iter_borrar(lista_iter_t* iter){
  if (!iter->actual){
    return NO_HAY_ACTUAL;
  }
  nodo_lista_t* nodo_actual=iter->actual;
  void* valor=nodo_actual->dato;
  iter->actual=nodo_actual->proximo;
  if (!iter->actual){
    iter->lista->ultimo=iter->anterior;
  }
  if (!iter->anterior){
    iter->lista->primero=iter->actual;
  }
  else{
  iter->anterior->proximo=iter->actual;
  }
  nodo_lista_destruir(nodo_actual);
  iter->lista->largo--;
  return valor;
}

void lista_iter_destruir(lista_iter_t* iter){
  free(iter);
}
