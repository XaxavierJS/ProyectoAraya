#ifndef EMERGENCIAS_H
#define EMERGENCIAS_H

#include "tdas/list.h"
#include "tdas/map.h"
#include "tdas/multimap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int tipoEmergencia; // 1-4
  char direccion[75];
  int estadoEmergencia; // 0-1
  int numeroCompania;
} Emergencia;

typedef struct {
  char nombreCompania[75];
  char direccion[75];
  int numeroCompania;
  int especialidad; // 1-4
  int bomberosDisponibles;
  int emergenciasAtendidas;
} Compania;

int compararCompanias(void *key1, void *key2);
int compararEmergencias(void *key1, void *key2);

void agregarCompania(Map *mapaCompanias, Compania *compania);
void crearCompanias();
void crearMapaEmergencias();
void agregarEmergencia(Map *mapaEmergencias, Map *mapaCompanias, Emergencia *emergencia);
void verEmergenciasProceso(Map *mapaEmergencias);
void verEmergenciasTerminadas(Map *mapaEmergencias);
void actualizarEstadoEmergencia(Map *mapaEmergencias, Map *mapaCompanias);
void mostrarEstadoCompanias(Map *mapaCompanias);

#endif // EMERGENCIAS_H
