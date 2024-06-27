#include "prints.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM_TABLA 50

typedef struct Oficial {
  char nombre[100];
  char RUT[10];
  char clave[5];
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

int rut_a_ascii(char RUT[10]) 
{
    int val[10];
    int suma = 0;
    for (int i = 0; i < 10; i++) {
        val[i] = (int)RUT[i]; 
        suma += val[i];
    }
  return suma;
}

int funcion_hash(char RUT[10]) { return rut_a_ascii(RUT) % TAM_TABLA; }

void insertar_oficial(TablaHash *tabla, char *nombre, char RUT[10], char clave[5]) 
{
  int indice = funcion_hash(RUT);
  Oficial *nuevoOficial = malloc(sizeof(Oficial));
  strcpy(nuevoOficial->nombre, nombre);
  strcpy(nuevoOficial->RUT, RUT);
  strcpy(nuevoOficial->clave, clave);
  nuevoOficial->siguiente = tabla->tabla[indice];
  tabla->tabla[indice] = nuevoOficial;
}

int es_rut_valido(const char *rut) 
{
    if (strlen(rut) != 9) 
    {
        return 0; //no era valida la longitud
    }

    for (int i = 0; i < 9; i++) {
        if (!isdigit(rut[i])) 
        {
            return 0; //no era solo numerico
        }
    }

    return 1; // RUT válido
}

void anadir_oficial(TablaHash *oficiales)
{
    int error = 1;
    while (1)
    {
        if (error == 0)
        {
            break;
        }
        char nombre_oficial[100];
        char RUT[10];
        char clave[5];
        printf("---------------------------------------\n");
        printf("|          AÑADIR NUEVO OFICIAL        |\n");
        printf("---------------------------------------\n\n");
        printf("Ingrese nombre del oficial: (ej: Ignacio Araya)");
        scanf(" %[101^\n]", nombre_oficial);
        printf("Bienvenido, oficial %s\n", nombre_oficial);
        printf("Por favor, ingrese su RUT como USUARIO (formato 082858717): ");
        scanf("%s", RUT);
        if (es_rut_valido(RUT))
        {
            error = 0;
            strncpy(clave, &RUT[5], 4);
            printf("Perfecto, su contrasena seran los ultimos 4 digitos de su RUT: %s\n", clave);
            insertar_oficial(oficiales, nombre_oficial, RUT, clave);
        }
        else
        {
            int opcion;
            printf("RUT no valido, por favor ingrese una opción.\n");
            printf("1) Volver a intentar.\n");
            printf("2) Menú Principal.\n");
            scanf("%d", &opcion);
            if (opcion != 1)
            {
                error = 1;
                printf("Volverás al Menú Principal\n\n");
            }
        }
    }
    presioneTeclaParaContinuar();  
}

Oficial *buscar_oficial(TablaHash *tabla, char RUT[10], char clave[5]) {
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
  insertar_oficial(tabla, "Ignacio Araya", "154891382", "1382");
  insertar_oficial(tabla, "Javier Retamal", "216104625", "4625");
  insertar_oficial(tabla, "Ignacia Brahim", "212751863", "1863");
  insertar_oficial(tabla, "Eva Ponce", "216434889", "4889");
  insertar_oficial(tabla, "Vicente Palma", "217521041", "1041");
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

  Oficial *of = buscar_oficial(tabla, RUT, clave);
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
