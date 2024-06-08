#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funciones/prints.h"

int main() {
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
      submenu1();
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
