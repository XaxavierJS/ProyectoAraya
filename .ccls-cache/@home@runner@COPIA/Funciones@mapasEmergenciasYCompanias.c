#include "mapasEmergenciasYCompanias.h"
#include "prints.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función de comparación para compañías (por número de compañía)
int compararCompanias(void *key1, void *key2) {
  return *(int *)key1 - *(int *)key2;
}

// Función de comparación para emergencias (por dirección)
int compararEmergencias(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2);
}

// Agregar una compañía al mapa de compañías
void agregarCompania(Map *mapaCompanias, Compania *compania) {
  int *key = malloc(sizeof(int));
  *key = compania->numeroCompania;
  map_insert(mapaCompanias, key, compania);
}

// Crear y agregar compañías al mapa de compañías
void crearCompanias(Map *mapaCompanias) {
  Compania *compania1 = malloc(sizeof(Compania));
  strcpy(compania1->nombreCompania, "Primera Compañia");
  strcpy(compania1->direccion, "Avenida Argentina 234");
  compania1->numeroCompania = 1;
  compania1->bomberosDisponibles = 12;
  compania1->emergenciasAtendidas = 0;

  Compania *compania2 = malloc(sizeof(Compania));
  strcpy(compania2->nombreCompania, "Segunda Compañia");
  strcpy(compania2->direccion, "Calle Falsa 123");
  compania2->numeroCompania = 2;
  compania2->bomberosDisponibles = 12;
  compania2->emergenciasAtendidas = 0;

  Compania *compania3 = malloc(sizeof(Compania));
  strcpy(compania3->nombreCompania, "Tercera Compañia");
  strcpy(compania3->direccion, "Santiago 234");
  compania3->numeroCompania = 3;
  compania3->bomberosDisponibles = 12;
  compania3->emergenciasAtendidas = 0;

  Compania *compania4 = malloc(sizeof(Compania));
  strcpy(compania4->nombreCompania, "Cuarta Compañia");
  strcpy(compania4->direccion, "Aborto 23445");
  compania4->numeroCompania = 4;
  compania4->bomberosDisponibles = 12;
  compania4->emergenciasAtendidas = 0;

  agregarCompania(mapaCompanias, compania1);
  agregarCompania(mapaCompanias, compania2);
  agregarCompania(mapaCompanias, compania3);
  agregarCompania(mapaCompanias, compania4);
}

// Agregar una emergencia al mapa de emergencias
void agregarEmergencia(Map *mapaEmergencias, Map *mapaCompanias,
                       Emergencia *emergencia) {
  Emergencia *emergenciaCopy = malloc(sizeof(Emergencia));
  *emergenciaCopy = *emergencia; // Crear una copia de la emergencia

  MapPair *pair = map_search(mapaEmergencias, "en proceso");
  if (pair) {
    List *listaEnProceso = pair->value;
    list_pushBack(listaEnProceso,
                  emergenciaCopy); // Agregar la copia a la lista

    // Restar 4 bomberos a la compañía correspondiente
    MapPair *pairCompania =
        map_search(mapaCompanias, &emergencia->numeroCompania);
    if (pairCompania) {
      Compania *compania = pairCompania->value;
      if (compania->bomberosDisponibles >= 4) {
        compania->bomberosDisponibles -= 4;
        compania->emergenciasAtendidas +=
            1; // Incrementar emergencias atendidas
        printf("   Bomberos en %s: %d\n", compania->nombreCompania,
               compania->bomberosDisponibles); // Debug line
      } else {
        printf(
            "| No hay suficientes bomberos disponibles\n| en la compañía %d.\n",
            emergencia->numeroCompania); // Debug line
      }
    } else {
      printf("Compañía no encontrada: %d\n",
             emergencia->numeroCompania); // Debug line
    }
  } else {
    printf("Lista de emergencias en proceso no encontrada.\n"); // Debug line
  }
}

// Crear el mapa de emergencias con listas de emergencias en proceso y
// terminadas
void crearMapaEmergencias(Map *mapaEmergencias) {
  List *listaEnProceso = list_create();
  List *listaTerminadas = list_create();
  map_insert(mapaEmergencias, "en proceso", listaEnProceso);
  map_insert(mapaEmergencias, "terminadas", listaTerminadas);
}

// Mostrar emergencias en proceso
void verEmergenciasProceso(Map *mapaEmergencias, Map *mapaCompanias) {

  MapPair *pair = map_search(mapaEmergencias, "en proceso");
  if (pair) {
    List *listaEnProceso = pair->value;
    Emergencia *emergencia = list_first(listaEnProceso);
    if (emergencia == NULL) {
      printf("No hay emergencias en proceso.\n");
    }
    int i = 1;
    while (emergencia != NULL) {
      MapPair *pairCompania =
          map_search(mapaCompanias, &emergencia->numeroCompania);
      int bomberosDisponibles = 0;
      if (pairCompania) {
        Compania *compania = pairCompania->value;
        bomberosDisponibles = compania->bomberosDisponibles;
      }
      printf("     Emergencia N°%d - Tipo %d\n", i, emergencia->tipoEmergencia);
      printf("     Direccion - %s\n", emergencia->direccion);
      printf("     Compania despachada - N°%d\n", emergencia->numeroCompania);
      printf("     Bomberos Disponibles en la compañía - %d\n",
             bomberosDisponibles);
      printf("     Estado actual - EN CURSO\n");
      printf("---------------------------------------\n");
      emergencia = list_next(listaEnProceso);
      i++;
    }
  }
  presioneTeclaParaContinuar();
  limpiarPantalla();
}

// Mostrar emergencias terminadas
void verEmergenciasTerminadas(Map *mapaEmergencias, Map *mapaCompanias) {
  MapPair *pair = map_search(mapaEmergencias, "terminadas");
  if (pair) {
    List *listaTerminadas = pair->value;
    Emergencia *emergencia = list_first(listaTerminadas);
    int i = 1;
    if (emergencia == NULL) {
      printf("No hay emergencias finalizadas.\n");
    }
    while (emergencia != NULL) {
      MapPair *pairCompania =
          map_search(mapaCompanias, &emergencia->numeroCompania);
      int bomberosDisponibles = 0;
      if (pairCompania) {
        Compania *compania = pairCompania->value;
        bomberosDisponibles = compania->bomberosDisponibles;
      }
      printf("   Emergencia N°%d - Tipo %d\n", i, emergencia->tipoEmergencia);
      printf("   Direccion - %s\n", emergencia->direccion);
      printf("   Compania despachada - N°%d\n", emergencia->numeroCompania);
      printf("   Bomberos Presentes - 0\n");
      printf("   Bomberos Disponibles en la compañía - %d\n",
             bomberosDisponibles);
      printf("   Estado actual - FINALIZADO\n");
      printf("---------------------------------------\n");
      emergencia = list_next(listaTerminadas);
      i++;
    }
  }
  presioneTeclaParaContinuar();
  limpiarPantalla();
}

// Actualizar el estado de una emergencia
void actualizarEstadoEmergencia(Map *mapaEmergencias, Map *mapaCompanias) {
  int opcion;
  int nuevoEstado;
  printf("---------------------------------------\n");
  printf("|           EMERGENCIAS ACTUALES       |\n");
  printf("---------------------------------------\n");

  MapPair *pairEnProceso = map_search(mapaEmergencias, "en proceso");

  if (!pairEnProceso)
    return;

  List *listaEnProceso = pairEnProceso->value;
  Emergencia *emergenciaPr = list_first(listaEnProceso);

  if (emergenciaPr == NULL) {
    printf("No hay emergencias para actualizar.\n");
    presioneTeclaParaContinuar();
    limpiarPantalla();
    return;
  }
  verEmergenciasProceso(mapaEmergencias, mapaCompanias);

  printf("\n- > Ingrese el numero de la emergencia a actualizar: ");
  scanf("%d", &opcion);

  printf("  Ingrese el nuevo estado de la emergencia:\n");
  printf("  1) FINALIZADO\n");
  printf("  2) EN CURSO\n");
  printf("  3) VOLVER AL MENU\n");
  printf("  ");
  scanf("%d", &nuevoEstado);

  if (nuevoEstado == 1 || nuevoEstado == 2) {
    int j = 1;
    for (Emergencia *emergencia = list_first(listaEnProceso);
         emergencia != NULL; emergencia = list_next(listaEnProceso), j++) {
      if (j == opcion) {
        emergencia->estadoEmergencia = nuevoEstado;

        if (nuevoEstado == 1) {
          MapPair *pairTerminadas = map_search(mapaEmergencias, "terminadas");
          if (!pairTerminadas)
            return;
          List *listaTerminadas = pairTerminadas->value;

          list_pushBack(listaTerminadas, emergencia);
          list_popCurrent(listaEnProceso);

          MapPair *pairCompania =
              map_search(mapaCompanias, &emergencia->numeroCompania);
          if (pairCompania) {
            Compania *compania = pairCompania->value;
            compania->bomberosDisponibles += 4;
          }

          printf("\nEstado de la emergencia actualizado a FINALIZADO\n");
        } else if (nuevoEstado == 2) {
          printf("\nLa emergencia sigue en curso.\n");
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
  presioneTeclaParaContinuar();
  limpiarPantalla();
}

// Mostrar el estado de las compañías
void mostrarEstadoCompanias(Map *mapaCompanias) {
  MapPair *pair = map_first(mapaCompanias);
  while (pair != NULL) {
    Compania *compania = pair->value;
    printf("\n");
    printf("+ - - - - - - - - - - - - - - - - - - - - - - +\n");
    printf("|       INFORMACION DE LA COMPANIA NO.  %d     |\n",
           compania->numeroCompania);
    printf("+ - - - - - - - - - - - - - - - - - - - - - - +\n");
    printf("Compañía:              %s, No. %d\n", compania->nombreCompania,
           compania->numeroCompania);
    printf("Direccion:             %s\n", compania->direccion);
    printf("Bomberos disponibles:  %d\n", compania->bomberosDisponibles);
    printf("Emergencias atendidas: %d\n", compania->emergenciasAtendidas);
    printf("- - - - - - - - - - - - - - - - - - - - - - - -\n");

    pair = map_next(mapaCompanias);
  }
  presioneTeclaParaContinuar();
  limpiarPantalla();
}