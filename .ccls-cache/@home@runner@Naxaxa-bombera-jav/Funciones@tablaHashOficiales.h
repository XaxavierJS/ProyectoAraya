#ifndef TABLA_HASH_OFICIALES_H
#define TABLA_HASH_OFICIALES_H

#include "tdas/map.h"

#define TAM_TABLA 50

typedef struct Oficial {
  char nombre[100];
  char RUT[10];
  char clave[5];
  struct Oficial *siguiente;
} Oficial;

typedef struct {
  Oficial *tabla[TAM_TABLA];
} TablaHash;

TablaHash *crear_tabla();
int rut_a_ascii(char RUT[10]);
int funcion_hash(char RUT[10]);
void insertar_oficial(TablaHash *oficiales, char *nombre, char RUT[10],
                      char clave[5]);
void crear_oficiales(TablaHash *oficiales);
int es_rut_valido(const char *rut);
void anadir_oficial(TablaHash *oficiales);
Oficial *buscar_oficial(TablaHash *oficiales, char RUT[10], char clave[5]);
void validacion(TablaHash *oficiales, Map *mapaEmergencias, Map *mapaCompanias);

#endif // TABLA_HASH_OFICIALES_H
