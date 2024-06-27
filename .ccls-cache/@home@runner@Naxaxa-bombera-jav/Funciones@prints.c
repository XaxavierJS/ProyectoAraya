#include "prints.h"
#include "grafos.h"
#include "mapasEmergenciasYCompanias.h"
#include "tablaHashOficiales.h"
#include "tdas/map.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar();
  getchar();
}

void menuprincipal() {
  printf("\n");
  printf("--------------------------------------------\n");
  printf("|             MENU PRINCIPAL               |\n");
  printf("--------------------------------------------\n");
  printf("1) Notificar una emergencia.\n");
  printf("2) Entrar como oficial.\n");
  printf("3) Solicitar estado de companias.\n");
  printf("4) Salir.\n");
  printf("--------------------------------------------\n");
}

void submenu1(int argc, char *argv[], Map *mapaEmergencias,
              Map *mapaCompanias) {
  char direccion[100];
  int tipoEmergencia;
  Emergencia emergencia;
  printf("--------------------------------------\n");
  printf("|     Que tipo de emergencia es ?       |\n");
  printf("--------------------------------------\n");
  printf("1) Incendio en zona vegetal.\n");
  printf("2) Incendio en estructura.\n");
  printf("3) Rescate.\n");
  printf("4) Material toxico/peligroso.\n");
  printf("--------------------------------------\n\n");
  printf("Seleccione el tipo de emergencia: ");
  scanf(" %d", &tipoEmergencia);
  if (tipoEmergencia != 1 && tipoEmergencia != 2 && tipoEmergencia != 3 &&
      tipoEmergencia != 4) {
    printf("Error en la seleccion del tipo de emergencia.\n");
    printf("Cancelando aviso... Intente nuevamente.\n");
    presioneTeclaParaContinuar();
    return;
  }
  emergencia.tipoEmergencia = tipoEmergencia;

  grafo_main(argc, argv, mapaEmergencias, mapaCompanias, &emergencia);
}

void submenu2(TablaHash *oficiales, Map *mapaCompanias, Map *mapaEmergencias) {
  char opcionMenuOf;

  do {
    printf("--------------------------------------------\n");
    printf("|            MENU OFICIALES                |\n");
    printf("--------------------------------------------\n");
    printf("1) Ver emergencias en proceso\n");
    printf("2) Ver emergencias terminadas\n");
    printf("3) Actualizar estado de emergencia\n");
    printf("4) Anadir nuevo oficial\n");
    printf("5) Volver al menu inicial\n");
    printf("--------------------------------------------\n");
    scanf(" %c", &opcionMenuOf);
    switch (opcionMenuOf) {
    case '1':
      limpiarPantalla();
      verEmergenciasProceso(mapaEmergencias, mapaCompanias);
      break;
    case '2':
      limpiarPantalla();
      verEmergenciasTerminadas(mapaEmergencias, mapaCompanias);
      break;
    case '3':
      limpiarPantalla();
      actualizarEstadoEmergencia(mapaEmergencias, mapaCompanias);
      break;
    case '4':
      limpiarPantalla();
      anadir_oficial(oficiales);
      break;
    case '5':
      return;
    default:
      limpiarPantalla();
      printf("Opcion no valida, por favor intenta nuevamente.\n");
      break;
    }
  } while (opcionMenuOf != '5');
}

void submenu3(Map *mapaCompanias) {
  limpiarPantalla();
  mostrarEstadoCompanias(mapaCompanias);
  presioneTeclaParaContinuar();
}
