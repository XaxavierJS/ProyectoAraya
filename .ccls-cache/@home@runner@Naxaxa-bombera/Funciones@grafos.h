#ifndef GRAFO_H
#define GRAFO_H

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14
#endif

#define NUM_COMPAÑIAS 4

// Definición de la estructura de nodo
typedef struct Nodo {
    char nombre[100];          // Nombre del nodo
    int x, y;                  // Coordenadas para dibujar el nodo
    struct Nodo *siguiente;    // Puntero al siguiente nodo en la lista
    struct Arista *adyacentes; // Puntero a la lista de aristas adyacentes
} Nodo;

// Definición de la estructura de arista (adyacencias)
typedef struct Arista {
    Nodo *destino;            // Nodo de destino al que apunta la arista
    struct Arista *siguiente; // Puntero a la siguiente arista en la lista
} Arista;

// Lista de nodos
typedef struct Grafo {
    Nodo *nodos; // Puntero al primer nodo en el grafo
} Grafo;

extern Grafo grafo;

// Funciones para manejar nodos y aristas
Nodo *crearNodo(const char *nombre, int x, int y);
void agregarNodo(Grafo *grafo, const char *nombre, int x, int y);
Arista *crearArista(Nodo *destino);
void agregarArista(Nodo *origen, Nodo *destino);
Nodo *encontrarNodo(Grafo *grafo, const char *nombre);

// Funciones para dibujar el grafo
void dibujarGrafo(cairo_t *cr, Grafo *grafo);

// Eventos de GTK
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

// Función para crear una malla de nodos
void crearMallaConNombres(int filas, int columnas, int separacion, char *nombres[]);

// Función para realizar la búsqueda en anchura (BFS)
void bfs(Grafo *grafo, Nodo *inicio, Nodo *compañias[], int numCompañias);

// Función principal
int grafo_main(int argc, char *argv[]);

#endif // GRAFO_H
