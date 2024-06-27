#include "tdas/list.h"
#include "tdas/map.h"
#include "tdas/multimap.h"
#include "prints.h"
#include <ctype.h>
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
  char nombrecCompania[75];
  char direccion[75];
  int numeroCompania;
  int especialidad; // 1-4
  int bomberosDisponibles;
  int emergenciasAtendidas;
} Compania;

int compararCompanias(void *key1, void *key2) {
  return *(int *)key1 - *(int *)key2;
}

int compararEmergencias(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2);
}

void agregarCompania(Map *mapaCompanias, Compania *compania) {
  map_insert(mapaCompanias, &compania->numeroCompania, compania);
}

void crearCompañias() {
  // Crear mapas para compañías y emergencias
  Map *mapaCompanias = sorted_map_create(compararCompanias);

  // Agregar 4 compañías
  Compania compania1 = {"Primera Compañia", "El Sol 421", 1, 1, 12, 0};
  Compania compania2 = {"Segunda Compañia", "Los Aromos 242", 2, 2, 12, 0};
  Compania compania3 = {"Tercero Compañia", "Concepción 3670", 3, 3, 12, 0};
  Compania compania4 = {
      "Cuarta Compañia", "Troncos Viejos 4510", 4, 4, 12, 0};

  agregarCompania(mapaCompanias, &compania1);
  agregarCompania(mapaCompanias, &compania2);
  agregarCompania(mapaCompanias, &compania3);
  agregarCompania(mapaCompanias, &compania4);
}

void crearMapaEmergencias() {
  Map *mapaEmergencias = sorted_map_create(compararEmergencias);
  List *listaEnProceso = list_create();
  List *listaTerminadas = list_create();
  map_insert(mapaEmergencias, "en proceso", listaEnProceso);
  map_insert(mapaEmergencias, "terminadas", listaTerminadas);
}

void agregarEmergencia(Map *mapaEmergencias, Map *mapaCompanias, Emergencia *emergencia) {
    MapPair *pair = map_search(mapaEmergencias, "en proceso");
    if (pair) {
        List *listaEnProceso = pair->value;
        list_pushBack(listaEnProceso, emergencia);

        // Restar 4 bomberos a la compañía correspondiente
        MapPair *pairCompania = map_search(mapaCompanias, &emergencia->numeroCompania);
        if (pairCompania) {
            Compania *compania = pairCompania->value;
            compania->bomberosDisponibles -= 4;
        }
    }
}

void verEmergenciasProceso(Map *mapaEmergencias) {
  MapPair *pair = map_search(mapaEmergencias, "en proceso");
  if (pair) {
    List *listaEnProceso = pair->value;
    printf("---------------------------------------\n");
    printf("|          EMERGENCIAS EN CURSO        |\n");
    printf("---------------------------------------\n");
    Emergencia *emergencia = list_first(listaEnProceso);
    int i = 1;
    while (emergencia != NULL){
      printf("     Emergencia N°%d - Tipo %d\n", i, emergencia->tipoEmergencia);
      printf("     Direccion - %s\n", emergencia->direccion);
      printf("     Compania despachada - N°%d\n", emergencia->numeroCompania);
      printf("     Bomberos Presentes - 4\n");
      printf("     Estado actual - EN CURSO\n");
      printf("---------------------------------------\n");
      emergencia = list_next(listaEnProceso);
      i++;
    }
  }
}

void verEmergenciasTerminadas(Map * mapaEmergencias) {
  MapPair *pair = map_search(mapaEmergencias, "terminadas");
  if (pair) {
    List *listaTerminadas = pair->value;
    printf("---------------------------------------\n");
    printf("|        EMERGENCIAS FINALIZADAS       |\n");
    printf("---------------------------------------\n");
    Emergencia *emergencia = list_first(listaTerminadas);
    int i = 1;
    while (emergencia != NULL){
      printf("     Emergencia N°%d - Tipo %d\n", i, emergencia->tipoEmergencia);
      printf("     Direccion - %s\n", emergencia->direccion);
      printf("     Compania despachada - N°%d\n",
            emergencia->numeroCompania);
      printf("     Bomberos Presentes - 0\n");
      printf("     Estado actual - FINALIZADO\n");
      printf("---------------------------------------\n");
      emergencia = list_next(listaTerminadas);
      i++;
    }
  }
}

// Función para actualizar el estado de una emergencia
void actualizarEstadoEmergencia(Map *mapaEmergencias, Map *mapaCompanias) {
    int opcion;
    int nuevoEstado;
    printf("---------------------------------------\n");
    printf("|           EMERGENCIAS ACTUALES       |\n");
    printf("---------------------------------------\n");

    MapPair *pairEnProceso = map_search(mapaEmergencias, "en proceso");
    if (!pairEnProceso) return;

    List *listaEnProceso = pairEnProceso->value;
    verEmergenciasProceso(mapaEmergencias);
    // Solicitar la emergencia a actualizar
    printf("Ingrese el numero de la emergencia a actualizar: ");
    scanf("%d", &opcion);

    // Solicitar el nuevo estado de la emergencia
    printf("Ingrese el nuevo estado de la emergencia:\n");
    printf("1) FINALIZADO\n");
    printf("2) EN CURSO\n");
    printf("3) VOLVER AL MENU\n");
    scanf("%d", &nuevoEstado);

    // Validar la opción seleccionada
    if (nuevoEstado == 1 || nuevoEstado == 2) {
        int j = 1;
        for (Emergencia *emergencia = list_first(listaEnProceso); emergencia != NULL; emergencia = list_next(listaEnProceso), j++) {
            if (j == opcion) {
                emergencia->estadoEmergencia = nuevoEstado;

                if (nuevoEstado == 1) { // FINALIZADO
                    MapPair *pairTerminadas = map_search(mapaEmergencias, "terminadas");
                    if (!pairTerminadas) return;
                    List *listaTerminadas = pairTerminadas->value;

                    list_pushBack(listaTerminadas, emergencia);
                    list_popCurrent(listaEnProceso);

                    // Devolver 4 bomberos a la compañía correspondiente
                    MapPair *pairCompania = map_search(mapaCompanias, &emergencia->numeroCompania);
                    if (pairCompania) {
                        Compania *compania = pairCompania->value;
                        compania->bomberosDisponibles += 4;
                    }

                    printf("\nEstado de la emergencia actualizado a FINALIZADO\n");
                } else if (nuevoEstado == 2) {
                    printf("\nLa emergencia sigue en curso\n");
                }
                break;
            }
        }
    } else if (nuevoEstado == 3) {
        printf("\n\nRegresando al menu...\n");
    } else {
        printf("Error en la seleccion del nuevo estado.\n");
        printf("Cancelando cambio... Intente nuevamente.\n");
    }
}

// Función para mostrar el estado de las compañías
void mostrarEstadoCompanias(Map *mapaCompanias) {
    MapPair *pair = map_first(mapaCompanias);
    while (pair != NULL) {
        Compania *compania = pair->value;
        printf("\n");
        printf("--------------------------------------------\n");
        printf("|       INFORMACION DE LA COMPANIA NO. %d    |\n", compania->numeroCompania);
        printf("--------------------------------------------\n");
        printf("Nombre de la compania y numero:    %s, No. %d\n", compania->nombrecCompania, compania->numeroCompania);
        printf("Direccion de la compania:          %s\n", compania->direccion);
        printf("Cantidad de bomberos disponibles:  %d\n", compania->bomberosDisponibles);
        printf("Cantidad de emergencias atendidas: %d\n", compania->emergenciasAtendidas);
        printf("--------------------------------------------\n");

        pair = map_next(mapaCompanias);
    }
}