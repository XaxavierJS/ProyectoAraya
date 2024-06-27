#include "Funciones/grafos.h"
#include "Funciones/prints.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char opcion;
  menuprincipal();

  do {
    limpiarPantalla();
    menuprincipal();
    printf("  ------------------------------------\n");
    printf("  |         Ingrese su opcion...       |\n");
    printf("  ------------------------------------\n");
    printf("      ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      limpiarPantalla();
      grafo_main(argc, argv);
      break;
    case '2':
      limpiarPantalla();
      validacion();
      break;
    case '3':
      submenu3();
      break;
    }

    limpiarPantalla();
  } while (opcion != '4');
  printf("------------------------------------\n");
  printf("|                                    |\n");
  printf("|       H A S T A   L U E G O  !     |\n");
  printf("|                                    |\n");
  printf("------------------------------------\n");
  presioneTeclaParaContinuar();
  limpiarPantalla();
  return 0;
}
