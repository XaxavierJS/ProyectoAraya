#include "Funciones/prints.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABLA 50

typedef struct Oficial {
  char nombre[100];
  int RUT;
  int clave;
  struct Oficial *siguiente;
} Oficial;

typedef struct {
  Oficial *tabla[TAM_TABLA];
} TablaHash;

TablaHash *crear_tabla() {
  TablaHash *nuevaTabla = malloc(sizeof(TablaHash));
  for (int i = 0; i < TAM_TABLA; i++) {
    nuevaTabla->tabla[i] = NULL;
  }
  return nuevaTabla;
}

int funcion_hash(int RUT) { return RUT % TAM_TABLA; }

void insertar_oficial(TablaHash *tabla, char *nombre, int RUT, int clave) {
  int indice = funcion_hash(RUT);
  Oficial *nuevoOficial = malloc(sizeof(Oficial));
  strcpy(nuevoOficial->nombre, nombre);
  nuevoOficial->RUT = RUT;
  nuevoOficial->clave = clave;
  nuevoOficial->siguiente = tabla->tabla[indice];
  tabla->tabla[indice] = nuevoOficial;
}

Oficial *buscar_oficial(TablaHash *tabla, int RUT, int clave) {
  int indice = funcion_hash(RUT);
  Oficial *actual = tabla->tabla[indice];
  while (actual != NULL) {
    if (actual->RUT == RUT && actual->clave == clave) {
      return actual;
    }
    actual = actual->siguiente;
  }
  return NULL;
}

void crear_oficiales(TablaHash *tabla) {
  insertar_oficial(tabla, "Ignacio Araya", 154891382, 1382);
  insertar_oficial(tabla, "Javier Retamal", 216104625, 4625);
  insertar_oficial(tabla, "Ignacia Brahim", 212751863, 1863);
  insertar_oficial(tabla, "Eva Ponce", 216434889, 4889);
  insertar_oficial(tabla, "Vicente Palma", 217521041, 1041);
}

void validacion(TablaHash *tabla) {
  char RUT[10];
  char clave[5];
  bool valido = false;
  int opcionError;

  printf("Por favor, ingrese su usuario y contraseña.\n");
  printf("Usuario: ");
  scanf("%s", RUT);
  printf("Contraseña: ");
  scanf("%s", clave);

  Oficial *of = buscar_oficial(tabla, atoi(RUT), atoi(clave));
  if (of != NULL) {
    valido = true;
  }

  if (!valido) {
    printf("--------------------------------------\n");
    printf("Ha ocurrido un error.\n");
    printf("1) Volver a intentar.\n");
    printf("2) Volver al menú.\n");
    scanf("%d", &opcionError);
    if (opcionError == 1)
      validacion(tabla);
    else
      return;
  } else {
    submenu2();
  }
  presioneTeclaParaContinuar();
}
