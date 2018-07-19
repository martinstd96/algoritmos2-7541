/*
	La idea es subir contenido despues fusionamos todo el contenido en un solo archivo
	(leo)
*/

typedef struct nodo abb_nodo_t;

struct nodo {
    char *clave; // recien estube leyendo arboles B, B+, B*
    void *dato;
    abb_nodo_t *izq;
    abb_nodo_t *der;
};

abb_nodo_t* nodo_crear(const char* clave, void* dato ){
  abb_nodo_t* nodo = malloc( sizeof(abb_nodo_t) );

  if (!nodo) return NULL;

  char* clave_copia = malloc(sizeof(char) * (strlen(clave) + 1) );

  if (!clave_copia){
    free(nodo);
    return NULL;
  }

  //copio la clave
  strcopy(clave_copia,clave);

  nodo->dato = dato;
  nodo->clave = clave_copia;
  nodo->izquierda = NULL;
  nodo->derecha = NULL;

  return nodo;
}

void nodo_destruir(abb_nodo_t* nodo,abb_destruir_dato_t destruir_dato){
  if (destruir_dato) destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

// estube viendo las primitivas .h es tipo el hash

struct abb {

    //punteros a funciones
    abb_comparar_clave_t comparar_clave;
    abb_destruir_dato_t destruir_dato;

    //data
    abb_nodo_t* raiz;
    size_t cantidad;
};

struct abb_iter{
  pila_t* pila;
};
