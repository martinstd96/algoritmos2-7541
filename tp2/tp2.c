#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE
#define TIME_FORMAT "%FT%T%z"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "strutil.h"
#include "heap.h"
#include "hash.h"
#include "abb.h"
#include "lista.h"
#include "campo_archivo.h"

struct campo_archivo{
  char* registro;
  FILE* archivo;
};

campo_archivo_t* campo_archivo_crear(const char* linea, FILE* archivo){
  campo_archivo_t* campo_archivo = malloc(sizeof(campo_archivo_t));

  if (!campo_archivo) return NULL;

  size_t largo1 = strlen(linea);
  char* linea_copia = malloc(sizeof(char*) * largo1 + 2);

  if (!linea_copia){
    free(campo_archivo);
    return NULL;
  }

  strcpy(linea_copia, linea);
  campo_archivo->registro = linea_copia;
  campo_archivo->archivo = archivo;
  return campo_archivo;
}

char* campo_archivo_obtener_registro(const campo_archivo_t* campo_archivo){
  return campo_archivo->registro;
}

FILE* campo_archivo_obtener_archivo(const campo_archivo_t* campo_archivo){
  return campo_archivo->archivo;
}

void campo_archivo_destruir(campo_archivo_t* campo_archivo){
  free(campo_archivo->registro);
  free(campo_archivo);
}

time_t iso8601_to_time(const char* iso8601){
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}

int imprimir_mensaje(char* mensaje){
  fprintf(stderr, "%s\n", mensaje);
  return 0;
}

int imprimir_error_comando(char* comando){
  fprintf(stderr, "Error en comando %s\n", comando);
  return 1;
}

int cmp_numeros_i(const int a, const int b){
	if (a < b) return 1;
	if (a > b) return -1;
	return 0;
}

int cmp_ip_i(const void* ip1,const void* ip2){
	char** vector_ip1 = split(ip1, '.');
	char** vector_ip2 = split(ip2, '.');

	int res = 0;

	for( int i=0; i<4 ; i++){
		res = cmp_numeros_i( atoi(vector_ip1[i]), atoi(vector_ip2[i]) );
		if (res) break;
	}

	free_strv(vector_ip1);
	free_strv(vector_ip2);

	return res;
}

int cmp_cadenas(const char* a, const char* b){
  return -1 * ( strcmp(a, b) );
}

int cmp_numeros(const int a, const int b){
	if (a < b) return 1;

  if (a > b) return -1;

  return 0;
}

int cmp_ip(const char* ip1,const char* ip2){
	char** vector_ip1 = split(ip1, '.');
	char** vector_ip2 = split(ip2, '.');

	int res = 0;

	for( int i=0; i<4 ; i++){
		res = cmp_numeros( atoi(vector_ip1[i]), atoi(vector_ip2[i]) );
		if (res) break;
	}

	free_strv(vector_ip1);
	free_strv(vector_ip2);

	return -1 * (res);
}

int cmp_ips(char* ip1, char* ip2){
	char** vector_ip1 = split(ip1, '.');
	char** vector_ip2 = split(ip2, '.');

	for (int i = 0; i < 4; i++){
		int resultado = cmp_numeros( atoi(vector_ip1[i]), atoi(vector_ip2[i]) );

		if (resultado != 0){
      free_strv(vector_ip1);
      free_strv(vector_ip2);
      return resultado;
    }

	}

  free_strv(vector_ip1);
  free_strv(vector_ip2);
  return 0;
}

int cmp_tiempos(const char* a, const char* b){
	time_t t1 = iso8601_to_time(a);
	time_t t2 = iso8601_to_time(b);
	double res = difftime(t1,t2);

	if (res == 0.0) return 0;

	return res > 0.0 ? -1 : 1;
}

int cmp(char** arr, char **arr2){
	char* tiempo1 = arr[1];
	char* tiempo2 = arr2[1];

	int res = cmp_tiempos(tiempo1,tiempo2);

	if ( res == 0 ){
		int pos[] = {0,3};
		for (int i = 0; i<2; i++){
			int resultado;
			if (i == 0) resultado = cmp_ips(arr[ pos[i] ],arr2[ pos[i] ]);
			else resultado = cmp_cadenas( arr[ pos[i] ], arr2[ pos[i] ]);
			if ( resultado != 0) return resultado;
		}
	}
	return res;
}

int cmp_registros(const void* a, const void* b){
	char** vector_a = split((char*)a, '\t');
	char** vector_b = split((char*)b, '\t');
	int resultado = cmp(vector_a, vector_b);
	free_strv(vector_a);
	free_strv(vector_b);
	return resultado;
}

int cmp_campo_archivo(const void* a, const void* b){
	char* registro_a = campo_archivo_obtener_registro(a);
	char* registro_b = campo_archivo_obtener_registro(b);
	return cmp_registros(registro_a, registro_b);
}

void fclose_wrapper(void* archivo){
  fclose(archivo);
}

void campo_archivo_destruir_wrapper(void* campo_archivo){
  campo_archivo_destruir(campo_archivo);
}

size_t len(char** vector){
  size_t cantidad=0;

  for (int i=0; vector[i]; i++) cantidad++;

  return cantidad;
}

int liberar_con_temporal(FILE* temporal, heap_t* heap, lista_t* lista_registros, char* linea, FILE* archivo1){
  fclose(temporal);
  heap_destruir(heap, free);
  lista_destruir(lista_registros, free);
  free(linea);
  fclose(archivo1);
  return imprimir_error_comando("ordenar_archivo");
}

int liberar_sin_temporal(heap_t* heap, lista_t* lista_registros, char* linea, FILE* archivo1){
  heap_destruir(heap, free);
  lista_destruir(lista_registros, free);
  free(linea);
  fclose(archivo1);
  return imprimir_error_comando("ordenar_archivo");
}

char* copiar_linea(char* linea){
  size_t largo = strlen(linea) + 2;
  char* cadena_auxiliar = malloc(sizeof(char) * largo);

  if (!cadena_auxiliar) return NULL;

  strcpy(cadena_auxiliar, linea);
  return cadena_auxiliar;
}

char* obtener_nombre(int n){
  char* nombre = malloc(sizeof(char) * 20 + 1);// 20 por si se generan hasta un millon de particiones.

  if (!nombre) return NULL;

  sprintf(nombre, "temporal%d.log", n)  ;
  return nombre;
}

int particionar_archivo(char* nombre_archivo, lista_t* lista_nombres, ssize_t bytes){
  FILE* archivo1 = fopen(nombre_archivo, "r");

  if (!archivo1) return imprimir_error_comando("ordenar_archivo");

  heap_t* heap_registros = heap_crear(cmp_registros);

  if (!heap_registros){
    fclose(archivo1);
    return imprimir_error_comando("ordenar_archivo");
  }

  lista_t* lista_registros = lista_crear();

  if (!lista_registros){
    fclose(archivo1);
    heap_destruir(heap_registros, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  int n = 0;
  char* nombre_temporal = obtener_nombre(n);

  if (!nombre_temporal){
    fclose(archivo1);
    heap_destruir(heap_registros, NULL);
    lista_destruir(lista_registros, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }
  FILE* temporal = fopen(nombre_temporal, "w");

  if (!temporal){
    fclose(archivo1);
    heap_destruir(heap_registros, NULL);
    lista_destruir(lista_registros, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  lista_insertar_ultimo(lista_nombres, nombre_temporal);
  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;
  ssize_t cota_memoria = 0;

  while ( (leidos = getline(&linea, &capacidad, archivo1)) > EOF ){

    if (cota_memoria < bytes){
      cota_memoria += leidos;
      char* linea_copia = copiar_linea(linea);

      if (!linea_copia) return liberar_con_temporal(temporal, heap_registros, lista_registros, linea, archivo1);

      heap_encolar(heap_registros, linea_copia);
      continue;
    }

    if (cota_memoria >= bytes && !heap_esta_vacio(heap_registros)){
      char* registro = heap_desencolar(heap_registros);
      fprintf(temporal, "%s", registro);
      char* linea_copia = copiar_linea(linea);

      if (!linea_copia) return liberar_con_temporal(temporal, heap_registros, lista_registros, linea, archivo1);

      if (cmp_registros(linea, registro) <= 0) heap_encolar(heap_registros, linea_copia); /* <= 0 por la funcion de comparacion que es la
                                                                                   que usamos para modelar un heap de minimos*/
      else lista_insertar_ultimo(lista_registros, linea_copia);

      free(registro);
      continue;
    }

    if (heap_esta_vacio(heap_registros)) fclose(temporal);

    n++;
    nombre_temporal = obtener_nombre(n);

    if (!nombre_temporal) return liberar_sin_temporal(heap_registros, lista_registros, linea, archivo1);

    temporal = fopen(nombre_temporal, "w");

    if (!temporal) return liberar_sin_temporal(heap_registros, lista_registros, linea, archivo1);

    size_t memoria = 0;
    lista_insertar_ultimo(lista_nombres, nombre_temporal);
    while (!lista_esta_vacia(lista_registros)){
      char* registro = lista_borrar_primero(lista_registros);
      size_t bytes = strlen(registro) + 1;
      memoria += bytes;
      heap_encolar(heap_registros, registro);
    }

    cota_memoria = (ssize_t)memoria;
    cota_memoria += leidos;
    char* linea_copia = copiar_linea(linea);

    if (!linea_copia) return liberar_con_temporal(temporal, heap_registros, lista_registros, linea, archivo1);

    heap_encolar(heap_registros, linea_copia);
  }

  free(linea);
  fclose(archivo1);

  while (!heap_esta_vacio(heap_registros)){
    char* registro = heap_desencolar(heap_registros);
    fprintf(temporal, "%s", registro);
    free(registro);
  }

  if (!lista_esta_vacia(lista_registros)){
    fclose(temporal);
    n++;
    nombre_temporal = obtener_nombre(n);

    if (!nombre_temporal) return liberar_sin_temporal(heap_registros, lista_registros, linea, archivo1);

    temporal = fopen(nombre_temporal, "w");

    if (!temporal) return liberar_sin_temporal(heap_registros, lista_registros, linea, archivo1);

    while (!lista_esta_vacia(lista_registros)){
      char* registro = lista_borrar_primero(lista_registros);
      heap_encolar(heap_registros, registro);
    }
    lista_insertar_ultimo(lista_nombres, nombre_temporal);

    while (!heap_esta_vacio(heap_registros)){
      char* registro = heap_desencolar(heap_registros);
      fprintf(temporal, "%s", registro);
      free(registro);
    }

  }

  fclose(temporal);
  lista_destruir(lista_registros, NULL);
  heap_destruir(heap_registros, NULL);
  return 0;
}

int juntar_particiones(char* nombre_salida, lista_t* lista_nombres){
  lista_t* lista_archivos = lista_crear();

  if (!lista_archivos) return imprimir_error_comando("ordenar_archivo");

  heap_t* heap_ordenar = heap_crear(cmp_campo_archivo);

  if (!heap_ordenar){
    lista_destruir(lista_archivos, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  FILE* archivo2 = fopen(nombre_salida, "w");

  if (!archivo2){
    lista_destruir(lista_archivos, NULL);
    heap_destruir(heap_ordenar, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  lista_iter_t* iter = lista_iter_crear(lista_nombres);

  if (!iter){
    fclose(archivo2);
    lista_destruir(lista_archivos, NULL);
    heap_destruir(heap_ordenar, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  FILE* particion;

  while (!lista_iter_al_final(iter)){
    char* archivo_actual = lista_iter_ver_actual(iter);
    particion = fopen(archivo_actual, "r");
    lista_insertar_ultimo(lista_archivos, particion);
    lista_iter_avanzar(iter);
  }

  lista_iter_destruir(iter);
  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;
  iter = lista_iter_crear(lista_archivos);

  if (!iter){
    fclose(archivo2);
    lista_destruir(lista_archivos, fclose_wrapper);
    heap_destruir(heap_ordenar, NULL);
    return imprimir_error_comando("ordenar_archivo");
  }

  while (!lista_iter_al_final(iter)){
    particion = lista_iter_ver_actual(iter);
    leidos = getline(&linea, &capacidad, particion);
    campo_archivo_t* campo_archivo = campo_archivo_crear(linea, particion);

    if (!campo_archivo){
      fclose(archivo2);
      lista_destruir(lista_archivos, fclose_wrapper);
      lista_iter_destruir(iter);
      heap_destruir(heap_ordenar, campo_archivo_destruir_wrapper);
      free(linea);
      fclose(particion);
      return imprimir_error_comando("ordenar_archivo");
    }

    heap_encolar(heap_ordenar, campo_archivo);
    lista_iter_avanzar(iter);
  }

  lista_iter_destruir(iter);

  while (!heap_esta_vacio(heap_ordenar)){
    campo_archivo_t* actual = heap_desencolar(heap_ordenar);
    char* registro = campo_archivo_obtener_registro(actual);
    fprintf(archivo2, "%s", registro);
    particion = campo_archivo_obtener_archivo(actual);
    leidos = getline(&linea, &capacidad, particion);
    campo_archivo_destruir(actual);

    if (leidos == EOF){
      fclose(particion);
      continue;
    }

    campo_archivo_t* campo_archivo = campo_archivo_crear(linea, particion);

    if (!campo_archivo){
      fclose(archivo2);
      lista_destruir(lista_archivos, fclose_wrapper);
      lista_destruir(lista_nombres, free);
      heap_destruir(heap_ordenar, campo_archivo_destruir_wrapper);
      free(linea);
      fclose(particion);
      return imprimir_error_comando("ordenar_archivo");
    }

    heap_encolar(heap_ordenar, campo_archivo);
  }

  heap_destruir(heap_ordenar, NULL);
  free(linea);
  fclose(archivo2);

  while (!lista_esta_vacia(lista_archivos)) lista_borrar_primero(lista_archivos);

  lista_destruir(lista_archivos, NULL);
  return 0;
}

int ordenar_archivo(char* nombre_archivo, char* nombre_salida, ssize_t bytes){
  lista_t* lista_nombres = lista_crear();

  if (!lista_nombres) return imprimir_error_comando("ordenar_archivo");

  int resultado = particionar_archivo(nombre_archivo, lista_nombres, bytes);

  if (resultado == 1){
    lista_destruir(lista_nombres, free);
    return 1;
  }

  resultado = juntar_particiones(nombre_salida, lista_nombres);

  if (resultado == 1){
    lista_destruir(lista_nombres, free);
    return 1;
  }

  while (!lista_esta_vacia(lista_nombres)){
    char* nombre = lista_borrar_primero(lista_nombres);
    remove(nombre);
    free(nombre);
  }

  lista_destruir(lista_nombres, NULL);
  fprintf(stdout, "OK\n");
  return 0;
}

void eliminar_tiempo(void* lista){
	lista_destruir(lista, free);
}

void cargar_tiempo(hash_t* hash_ips, char* ip, char* tiempo){

	bool esta = hash_pertenece(hash_ips, ip);

	if (esta){
		lista_t* lista = hash_obtener(hash_ips, ip);
		lista_insertar_ultimo(lista, tiempo);
	}
	else{
		lista_t* lista = lista_crear();

		if (!lista) return;

		lista_insertar_ultimo(lista, tiempo);
		hash_guardar(hash_ips, ip, lista);
	}

}

bool tiempo_sospechoso(char* inicio, char* fin){
	time_t i = iso8601_to_time(inicio);
	time_t f = iso8601_to_time(fin);
	return ( difftime(f, i) < 2.0 );
}


bool dos_attack(lista_t* lista_tiempo){
	if ( lista_esta_vacia(lista_tiempo) || lista_largo(lista_tiempo) < 5 ) return false;

	lista_iter_t* primero = lista_iter_crear(lista_tiempo);

	if (!primero) return false;

	lista_iter_t* ultimo = lista_iter_crear(lista_tiempo);

	if (!ultimo){
		lista_iter_destruir(primero);
		return false;
	}

	bool es_DOS = false;

	for (int i = 1; i < 5; i++) lista_iter_avanzar(ultimo);

	while ( !lista_iter_al_final(ultimo) ){
		char* inicio = lista_iter_ver_actual(primero);
		char* fin = lista_iter_ver_actual(ultimo);
		es_DOS = tiempo_sospechoso(inicio, fin);

		if (es_DOS) break;

		lista_iter_avanzar(primero);
		lista_iter_avanzar(ultimo);
	}

	lista_iter_destruir(primero);
	lista_iter_destruir(ultimo);
	return es_DOS;
}

void DOS(hash_t* hash_ips){
	heap_t* heap = heap_crear(cmp_ip_i);

	if(!heap) return;

	hash_iter_t* iter = hash_iter_crear(hash_ips);

	if (!iter) return ;

	while ( !hash_iter_al_final(iter) ){
		const char* ip = hash_iter_ver_actual(iter);
		lista_t* lista_tiempos = hash_obtener(hash_ips, ip);

		if ( dos_attack(lista_tiempos) ) {
			char* copy_ip = malloc( sizeof(char) * ( strlen(ip) + 1 ) );

			if (!copy_ip){
				hash_iter_destruir(iter);
        heap_destruir(heap, free);
				return;
			}

			strcpy(copy_ip,ip);

			heap_encolar(heap, copy_ip);

		}
		hash_iter_avanzar(iter);
	}

	while ( !heap_esta_vacio(heap) ){
		char* ip = heap_desencolar(heap);
		fprintf(stdout, "DoS: %s\n", ip);
		free(ip);
	}

	heap_destruir(heap, NULL);
	hash_iter_destruir(iter);
}

int agregar_archivo(char* nombre_archivo, abb_t* visitantes){
  FILE* archivo = fopen(nombre_archivo,"r");

  if (!archivo) return imprimir_error_comando("agregar_archivo");

  char *linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;

	hash_t* hash_ips = hash_crear(eliminar_tiempo);

	if (!hash_ips){
		fclose(archivo);
		return imprimir_error_comando("agregar_archivo");;
	}

  while ( ( leidos = getline(&linea, &capacidad, archivo) ) != -1 ){

    char** datos = split(linea, '\t');

    if(!datos){
      fclose(archivo);
      hash_destruir(hash_ips);
      free(linea);
      return imprimir_error_comando("agregar_archivo");
    }

    size_t tam = strlen(datos[0]);
    char* ip_dos = malloc(sizeof(char) * ( tam + 1 ) );

    if (!ip_dos){
      fclose(archivo);
      free_strv(datos);
      hash_destruir(hash_ips);
      free(linea);
      return imprimir_error_comando("agregar_archivo");
    }

    char* ip_visitantes = malloc(sizeof(char) * ( tam + 1 ) );

    if (!ip_visitantes){
      fclose(archivo);
      free_strv(datos);
      free(linea);
      hash_destruir(hash_ips);
      free(ip_dos);
      return imprimir_error_comando("agregar_archivo");
    }

    char* tiempo = malloc(sizeof(char) * ( strlen(datos[1]) + 1) );

    if (!tiempo){
      fclose(archivo);
      free_strv(datos);
      free(linea);
      hash_destruir(hash_ips);
      free(ip_dos);
      free(ip_visitantes);
      return false;
    }

    strcpy(ip_dos, datos[0]);
    strcpy(ip_visitantes, datos[0]);
    strcpy(tiempo, datos[1]);
    cargar_tiempo(hash_ips, ip_dos, tiempo);
    abb_guardar(visitantes, ip_visitantes, NULL);
    free(ip_visitantes);
    free(ip_dos);
    free_strv(datos);
  }

  DOS(hash_ips);
	fprintf(stdout, "OK\n");
	fclose(archivo);
	free(linea);
	hash_destruir(hash_ips);
  return 0;
}

int ver_visitantes(abb_t* visitantes, const char* inicio, const char* fin){
	abb_iter_t* iter = abb_iter_in_crear(visitantes, inicio, fin);

	if (!iter) imprimir_error_comando("ver_visitantes");

	fprintf(stdout, "%s:\n", "Visitantes");
	while ( !abb_iter_in_al_final(iter) ){
		const char* ip = abb_iter_in_ver_actual(iter);
		fprintf(stdout, "\t%s\n", ip);

		abb_iter_in_avanzar(visitantes, iter);
	}

	abb_iter_in_destruir(iter);
  fprintf(stdout, "OK\n");
  return 0;
}

int ejecutar_comandos(char** vector_comandos, char** comandos_validos, ssize_t bytes, abb_t* visitantes){
  char* comando = vector_comandos[0];

  if (strcmp(comando, comandos_validos[0]) == 0) return ordenar_archivo(vector_comandos[1], vector_comandos[2], bytes);

  if (strcmp(comando, comandos_validos[1]) == 0) return agregar_archivo(vector_comandos[1], visitantes);

  else return ver_visitantes(visitantes, vector_comandos[1], vector_comandos[2]);

  return 0;
}

bool pertenece(char* comando, char** comandos_validos){
  for (int i = 0; i < 3; i++){

    if (strcmp(comando, comandos_validos[i]) == 0) return true;

  }

  return false;
}

bool es_invalido(char* comando){
  imprimir_error_comando(comando);
  return false;
}

bool es_valido(char** vector_comandos){
  if (strcmp("ordenar_archivo", vector_comandos[0]) == 0 && len(vector_comandos) != 3) return es_invalido("ordenar_archivo");

  if (strcmp("agregar_archivo", vector_comandos[0]) == 0 && len(vector_comandos) != 2) return es_invalido("agregar_archivo");

  if (strcmp("ver_visitantes", vector_comandos[0]) == 0 && len(vector_comandos) != 3) return es_invalido("ver_visitantes");

  return true;
}

int consola(ssize_t bytes){
  char** comandos_validos = malloc(sizeof(char*) * 3);

  if (!comandos_validos) return imprimir_mensaje("Ha ocurrido un error");

  abb_t* visitantes = abb_crear(cmp_ip, NULL);

  if (!visitantes){
    free(comandos_validos);
    return imprimir_mensaje("Ha ocurrido un error");
  }

  comandos_validos[0] = "ordenar_archivo";
  comandos_validos[1] = "agregar_archivo";
  comandos_validos[2] = "ver_visitantes";
  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;

  while ( (leidos = getline(&linea, &capacidad, stdin)) > 0 ){
    linea[strlen(linea) - 1] = '\0';
    char** vector_comandos = split(linea,' ');
    char* comando = vector_comandos[0];

    if (!pertenece(comando, comandos_validos)){
      free_strv(vector_comandos);
      abb_destruir(visitantes);
      free(comandos_validos);
      free(linea);
      return imprimir_error_comando(comando);;
    }

    if (!es_valido(vector_comandos)){
      free_strv(vector_comandos);
      abb_destruir(visitantes);
      free(comandos_validos);
      free(linea);
      return 1;
    }

    int resultado = ejecutar_comandos(vector_comandos, comandos_validos, bytes, visitantes);
    free_strv(vector_comandos);

    if (resultado == 1){
      free(linea);
      free(comandos_validos);
      abb_destruir(visitantes);
      return resultado;
    }
  }

  free(linea);
  free(comandos_validos);
  abb_destruir(visitantes);
  return 0;
}

int main(int argc,char* argv[]){

  if (argc != 2) return imprimir_mensaje("Cantidad de parametros erronea");

  char* cadena_parametro = argv[1];
  size_t len = strlen(cadena_parametro);

  for (size_t i = 0; i < len; i++){

    if (isdigit(cadena_parametro[i]) == 0) return imprimir_mensaje("Tipo de parametro incorrecto");

  }

  ssize_t bytes = (ssize_t)atoi(argv[1]) * 1000;
  consola(bytes);
  return 0;
}
