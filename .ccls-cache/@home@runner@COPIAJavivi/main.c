#include "Funciones/grafos.h"
#include "Funciones/mapasEmergenciasYCompanias.h"
#include "Funciones/prints.h"
#include "Funciones/tablaHashOficiales.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int opcion;
  Map *mapaCompanias = sorted_map_create(compararCompanias);
  Emergencia emergencia;
  crearCompanias(mapaCompanias);
  Map *mapaEmergencias = sorted_map_create(compararEmergencias);
  crearMapaEmergencias(mapaEmergencias);
  TablaHash *oficiales = crear_tabla();
  crear_oficiales(oficiales);

  menuprincipal();
  do {
    limpiarPantalla();
    menuprincipal();
    printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
    printf("|             INGRESE SU OPCION           |\n");
    printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
    printf("      ");
    scanf("%d", &opcion);
    if (opcion > 4 || opcion < 1) {
      printf(
          "Opción fuera de rango. Por favor, ingrese un número entre 1 y 4.\n");
      continue; // Volver a pedir la opción
    }
    switch (opcion) {
    case 1:
      limpiarPantalla();
      submenu1(argc, argv, mapaEmergencias, mapaCompanias);
      break;
    case 2:
      limpiarPantalla();
      validacion(oficiales, mapaEmergencias, mapaCompanias);
      break;
    case 3:
      submenu3(mapaCompanias);
      break;
    }

    limpiarPantalla();
  } while (opcion != 4);
  printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
  printf("|                                         |\n");
  printf("|          H A S T A   L U E G O  !       |\n");
  printf("|                                         |\n");
  printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
  presioneTeclaParaContinuar();
  limpiarPantalla();
  return 0;
}
