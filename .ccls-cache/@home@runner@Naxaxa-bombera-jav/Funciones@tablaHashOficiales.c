#include "tablaHashOficiales.h"
#include "prints.h"
#include "tdas/map.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TablaHash *crear_tabla() {
  TablaHash *nuevaTabla = malloc(sizeof(TablaHash));
  for (int i = 0; i < TAM_TABLA; i++) {
    nuevaTabla->tabla[i] = NULL;
  }
  return nuevaTabla;
}

int rut_a_ascii(char RUT[10]) {
  int val[10];
  int suma = 0;
  for (int i = 0; i < 9; i++) {
    val[i] = (int)RUT[i];
    suma += val[i];
  }
  return suma;
}

int funcion_hash(char RUT[10]) { return rut_a_ascii(RUT) % TAM_TABLA; }

void insertar_oficial(TablaHash *oficiales, char *nombre, char RUT[10],
                      char clave[5]) {
  int indice = funcion_hash(RUT);
  Oficial *nuevoOficial = malloc(sizeof(Oficial));
  strncpy(nuevoOficial->nombre, nombre, sizeof(nuevoOficial->nombre) - 1);
  nuevoOficial->nombre[sizeof(nuevoOficial->nombre) - 1] = '\0';
  strncpy(nuevoOficial->RUT, RUT, sizeof(nuevoOficial->RUT) - 1);
  nuevoOficial->RUT[sizeof(nuevoOficial->RUT) - 1] = '\0';
  strncpy(nuevoOficial->clave, clave, sizeof(nuevoOficial->clave) - 1);
  nuevoOficial->clave[sizeof(nuevoOficial->clave) - 1] = '\0';
  nuevoOficial->siguiente = oficiales->tabla[indice];
  oficiales->tabla[indice] = nuevoOficial;
}

void crear_oficiales(TablaHash *oficiales) {
  insertar_oficial(oficiales, "Ignacio Araya", "154891382", "1382");
  insertar_oficial(oficiales, "Javier Retamal", "216104625", "0462");
  insertar_oficial(oficiales, "Ignacia Brahim", "212751863", "1863");
  insertar_oficial(oficiales, "Eva Ponce", "216434889", "4889");
  insertar_oficial(oficiales, "Vicente Palma", "217521041", "1041");
}

int es_rut_valido(const char *rut) {
  if (strlen(rut) != 9) {
    return 0; // no era valida la longitud
  }

  for (int i = 0; i < 9; i++) {
    if (!isdigit(rut[i])) {
      return 0; // no era solo numerico
    }
  }

  return 1; // RUT válido
}

void anadir_oficial(TablaHash *oficiales) {
  int error = 1;
  while (1) {
    if (error == 0) {
      break;
    }
    char nombre_oficial[100];
    char RUT[10];
    char clave[5];
    printf("---------------------------------------\n");
    printf("|          AÑADIR NUEVO OFICIAL        |\n");
    printf("---------------------------------------\n\n");
    printf("Ingrese nombre del oficial: (ej: Ignacio Araya): ");
    scanf(" %[^\n]", nombre_oficial);
    getchar();
    printf("Bienvenido, oficial %s\n", nombre_oficial);
    printf("Por favor, ingrese su RUT como USUARIO (formato 082858717): ");
    scanf("%9s", RUT);
    if (es_rut_valido(RUT)) {
      error = 0;
      strncpy(clave, &RUT[5], 4);
      clave[4] = '\0'; // Null-terminate the string
      printf(
          "Perfecto, su contraseña serán los últimos 4 dígitos de su RUT: %s\n",
          clave);
      insertar_oficial(oficiales, nombre_oficial, RUT, clave);
    } else {
      int opcion;
      printf("RUT no válido, por favor ingrese una opción.\n");
      printf("1) Volver a intentar.\n");
      printf("2) Menú Principal.\n");
      scanf("%d", &opcion);
      if (opcion != 1) {
        error = 1;
        printf("Volverás al Menú Principal\n\n");
      }
    }
  }
  presioneTeclaParaContinuar();
}

Oficial *buscar_oficial(TablaHash *oficiales, char RUT[10], char clave[5]) {
  int indice = funcion_hash(RUT);
  Oficial *actual = oficiales->tabla[indice];
  while (actual != NULL) {
    if (strcmp(actual->RUT, RUT) == 0 && strcmp(actual->clave, clave) == 0) {
      return actual;
    }
    actual = actual->siguiente;
  }
  return NULL;
}

void validacion(TablaHash *oficiales, Map *mapaEmergencias,
                Map *mapaCompanias) {
  char RUT[10];
  char clave[5];
  bool valido = false;
  int opcionError;

  printf("Por favor, ingrese su usuario y contraseña.\n");
  printf("Usuario: ");
  scanf("%9s", RUT);
  printf("Contraseña: ");
  scanf("%4s", clave);

  Oficial *of = buscar_oficial(oficiales, RUT, clave);
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
      validacion(oficiales, mapaCompanias, mapaEmergencias);
    else
      return;
  } else {
    submenu2(oficiales, mapaCompanias, mapaEmergencias);
  }
  presioneTeclaParaContinuar();
}
