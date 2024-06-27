#ifndef PRINTS_H
#define PRINTS_H

#include "tablaHashOficiales.h"
#include "tdas/map.h"

void limpiarPantalla();
void presioneTeclaParaContinuar();
void mostrarEstadocompanias(int cantidad);
void menuprincipal();
void submenu1();
void submenu2(TablaHash *oficiales, Map *mapaCompanias, Map *mapaEmergencias);
void submenu3(Map *mapaCompanias);

#endif // PRINTS_H
