#ifndef CAMPO_ARCHIVO_H
#define CAMPO_ARCHIVO_H

typedef struct campo_archivo campo_archivo_t;

campo_archivo_t* campo_archivo_crear(const char* linea, FILE* archivo);

char* campo_archivo_obtener_registro(const campo_archivo_t* campo_archivo);

FILE* campo_archivo_obtener_archivo(const campo_archivo_t* campo_archivo);

void campo_archivo_destruir(campo_archivo_t* campo_archivo);

#endif // CAMPO_ARCHIVO_H
