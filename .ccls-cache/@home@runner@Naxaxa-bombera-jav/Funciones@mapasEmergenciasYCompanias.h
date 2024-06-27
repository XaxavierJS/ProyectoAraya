#ifndef MAPAS_EMERGENCIAS_Y_COMPANIAS_H
#define MAPAS_EMERGENCIAS_Y_COMPANIAS_H

#include "tdas/list.h"
#include "tdas/map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int tipoEmergencia; // 1-4
  int numeroCompania;
  char direccion[100];
  int estadoEmergencia; // 0-1
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
void agregarEmergencia(Map *mapaEmergencias, Map *mapaCompanias,
                       Emergencia *emergencia);
void verEmergenciasProceso(Map *mapaEmergencias, Map *mapaCompanias);
void verEmergenciasTerminadas(Map *mapaEmergencias, Map *mapaCompanias);
void actualizarEstadoEmergencia(Map *mapaEmergencias, Map *mapaCompanias);
void mostrarEstadoCompanias(Map *mapaCompanias);

#endif // EMERGENCIAS_H
