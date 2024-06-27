#include "mapasEmergenciasYCompanias.h"
#include "prints.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14
#endif

#define NUM_COMPANIAS 4

typedef struct Nodo {
  char nombre[100];
  int x, y;
  struct Nodo *siguiente;
  struct Arista *adyacentes;
} Nodo;

typedef struct Arista {
  Nodo *destino;
  struct Arista *siguiente;
} Arista;

typedef struct Grafo {
  Nodo *nodos;
} Grafo;

Grafo grafo;

typedef struct {
  Grafo *grafo;
  Map *mapaEmergencias;
  Map *mapaCompanias;
  Emergencia *emergencia;
} AppData;

Nodo *crearNodo(const char *nombre, int x, int y) {
  Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
  strcpy(nuevoNodo->nombre, nombre);
  nuevoNodo->x = x;
  nuevoNodo->y = y;
  nuevoNodo->siguiente = NULL;
  nuevoNodo->adyacentes = NULL;
  return nuevoNodo;
}

void agregarNodo(Grafo *grafo, const char *nombre, int x, int y) {
  Nodo *nuevoNodo = crearNodo(nombre, x, y);
  nuevoNodo->siguiente = grafo->nodos;
  grafo->nodos = nuevoNodo;
}

Arista *crearArista(Nodo *destino) {
  Arista *nuevaArista = (Arista *)malloc(sizeof(Arista));
  nuevaArista->destino = destino;
  nuevaArista->siguiente = NULL;
  return nuevaArista;
}

void agregarArista(Nodo *origen, Nodo *destino) {
  Arista *nuevaArista = crearArista(destino);
  nuevaArista->siguiente = origen->adyacentes;
  origen->adyacentes = nuevaArista;
}

Nodo *encontrarNodo(Grafo *grafo, const char *nombre) {
  Nodo *actual = grafo->nodos;
  while (actual != NULL) {
    if (strcmp(actual->nombre, nombre) == 0) {
      return actual;
    }
    actual = actual->siguiente;
  }
  return NULL;
}

void dibujarGrafo(cairo_t *cr, Grafo *grafo) {
  Nodo *nodo = grafo->nodos;
  while (nodo != NULL) {
    if (strcmp(nodo->nombre, "PRIMERA COMPAÑIA") == 0 ||
        strcmp(nodo->nombre, "SEGUNDA COMPAÑIA") == 0 ||
        strcmp(nodo->nombre, "TERCERA COMPAÑIA") == 0 ||
        strcmp(nodo->nombre, "CUARTA COMPAÑIA") == 0) {
      cairo_set_source_rgb(cr, 1, 0, 0);
      cairo_arc(cr, nodo->x, nodo->y, 10, 0, 2 * M_PI);
    } else {
      cairo_set_source_rgb(cr, 0, 0, 0);
      cairo_arc(cr, nodo->x, nodo->y, 5, 0, 2 * M_PI);
    }
    cairo_fill(cr);
    nodo = nodo->siguiente;
  }
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  cairo_surface_t *image = cairo_image_surface_create_from_png("imagen.png");
  if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS) {
    g_print("Error al cargar la imagen: %s\n",
            cairo_status_to_string(cairo_surface_status(image)));
    return FALSE;
  }

  int img_width = cairo_image_surface_get_width(image);
  int img_height = cairo_image_surface_get_height(image);

  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  double scale_x = (double)allocation.width / img_width;
  double scale_y = (double)allocation.height / img_height;

  cairo_save(cr);
  cairo_scale(cr, scale_x, scale_y);
  cairo_set_source_surface(cr, image, 0, 0);
  cairo_paint(cr);
  cairo_restore(cr);
  cairo_surface_destroy(image);

  dibujarGrafo(cr, &grafo);

  return FALSE;
}

void crearMallaConNombres(int filas, int columnas, int separacion,
                          char *nombres[]) {
  int nombreIndex = 0;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (nombreIndex < filas * columnas) {
        agregarNodo(&grafo, nombres[nombreIndex], j * separacion + 50,
                    i * separacion + 50);
        nombreIndex++;
      }
    }
  }

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      char nombreCalle1[100], nombreCalle2[100];

      if (j < columnas - 1) {
        snprintf(nombreCalle1, sizeof(nombreCalle1), "%s",
                 nombres[i * columnas + j]);
        snprintf(nombreCalle2, sizeof(nombreCalle2), "%s",
                 nombres[i * columnas + j + 1]);
        agregarArista(encontrarNodo(&grafo, nombreCalle1),
                      encontrarNodo(&grafo, nombreCalle2));
        agregarArista(encontrarNodo(&grafo, nombreCalle2),
                      encontrarNodo(&grafo, nombreCalle1));
      }

      if (i < filas - 1) {
        snprintf(nombreCalle1, sizeof(nombreCalle1), "%s",
                 nombres[i * columnas + j]);
        snprintf(nombreCalle2, sizeof(nombreCalle2), "%s",
                 nombres[(i + 1) * columnas + j]);
        agregarArista(encontrarNodo(&grafo, nombreCalle1),
                      encontrarNodo(&grafo, nombreCalle2));
        agregarArista(encontrarNodo(&grafo, nombreCalle2),
                      encontrarNodo(&grafo, nombreCalle1));
      }
    }
  }
}

// Modificación en la función BFS para seleccionar la compañía más cercana con
// bomberos disponibles

void bfs(Grafo *grafo, Nodo *inicio, Nodo *companias[], int numCompanias,
         Map *mapaEmergencias, Map *mapaCompanias, Emergencia *emergencia) {
  int num = 1;
  if (inicio == NULL) {
    printf("Nodo inicial no encontrado.\n");
    return;
  }

  Nodo *cola[1000];
  int front = 0;
  int rear = 0;

  Nodo *predecesor[1000] = {NULL};
  bool visitado[1000] = {false};

  Nodo *indice_nodos[1000];
  int indice = 0;
  Nodo *actual = grafo->nodos;
  while (actual != NULL) {
    indice_nodos[indice++] = actual;
    actual = actual->siguiente;
  }

  int obtenerIndice(Nodo * nodo) {
    for (int i = 0; i < indice; i++) {
      if (indice_nodos[i] == nodo) {
        return i;
      }
    }
    return -1;
  }

  int inicioIndice = obtenerIndice(inicio);
  cola[rear++] = inicio;
  visitado[inicioIndice] = true;

  while (front < rear) {
    Nodo *nodoActual = cola[front++];
    int nodoActualIndice = obtenerIndice(nodoActual);

    for (int i = 0; i < numCompanias; i++) {
      if (nodoActual == companias[i]) {

        MapPair *pairCompania = map_search(mapaCompanias, &i);
        if (pairCompania) {
          Compania *compania = pairCompania->value;
          if (compania->bomberosDisponibles != 0) {
            Nodo *nodo = nodoActual;
            num = 0;
            printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
            while (nodo != NULL) {
              if (num == 0) {
                printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
                printf("|           COMPAÑIA DESPACHADA           |\n");
                printf("|             %s            |\n", nodo->nombre);
                if (strcmp(nodo->nombre, "PRIMERA COMPAÑIA") == 0)
                  emergencia->numeroCompania = 1;
                else if (strcmp(nodo->nombre, "SEGUNDA COMPAÑIA") == 0)
                  emergencia->numeroCompania = 2;
                else if (strcmp(nodo->nombre, "TERCERA COMPAÑIA") == 0)
                  emergencia->numeroCompania = 3;
                else
                  emergencia->numeroCompania = 4;
                agregarEmergencia(mapaEmergencias, mapaCompanias, emergencia);
                printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
                printf("|          CAMINO MAS EFICIENTE           |\n");
                printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
                nodo = predecesor[obtenerIndice(nodo)];
                num = 1;
              }
              printf("| %s\n", nodo->nombre);
              nodo = predecesor[obtenerIndice(nodo)];
            }
            return;
          }
        }
      }
    }

    Arista *arista = nodoActual->adyacentes;
    while (arista != NULL) {
      Nodo *nodoAdyacente = arista->destino;
      int nodoAdyacenteIndice = obtenerIndice(nodoAdyacente);
      if (!visitado[nodoAdyacenteIndice]) {
        cola[rear++] = nodoAdyacente;
        visitado[nodoAdyacenteIndice] = true;
        predecesor[nodoAdyacenteIndice] = nodoActual;
      }
      arista = arista->siguiente;
    }
  }

  // En caso de que no se haya encontrado ninguna compañía con bomberos
  // disponibles
  printf("No se encontró una compañía con suficientes bomberos disponibles.\n");
  printf("Se hará llamado a otras ciudades para despacho de bomberos.\n");
}

gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event,
                               gpointer user_data) {
  AppData *appData = (AppData *)user_data;
  Nodo *nodoSeleccionado = NULL;
  Nodo *nodo = appData->grafo->nodos;

  while (nodo != NULL) {
    if ((event->x - nodo->x) * (event->x - nodo->x) +
            (event->y - nodo->y) * (event->y - nodo->y) <=
        100) {
      nodoSeleccionado = nodo;
      break;
    }
    nodo = nodo->siguiente;
  }

  if (nodoSeleccionado != NULL) {
    g_print("Ha seleccionado la calle: %s\n", nodoSeleccionado->nombre);
    strcpy(appData->emergencia->direccion, nodoSeleccionado->nombre);
    appData->emergencia->estadoEmergencia = 1;
    Nodo *companias[NUM_COMPANIAS];
    companias[0] = encontrarNodo(appData->grafo, "PRIMERA COMPAÑIA");
    companias[1] = encontrarNodo(appData->grafo, "SEGUNDA COMPAÑIA");
    companias[2] = encontrarNodo(appData->grafo, "TERCERA COMPAÑIA");
    companias[3] = encontrarNodo(appData->grafo, "CUARTA COMPAÑIA");

    bfs(appData->grafo, nodoSeleccionado, companias, NUM_COMPANIAS,
        appData->mapaEmergencias, appData->mapaCompanias, appData->emergencia);

    gtk_main_quit();
  } else {
    g_print("No se ha seleccionado ninguna calle válida.\n");
  }

  return TRUE;
}

int grafo_main(int argc, char *argv[], Map *mapaEmergencias, Map *mapaCompanias,
               Emergencia *emergencia) {
  gtk_init(&argc, &argv);
  char respuesta;
  printf("| Para indicar la zona de emergencia, hay |\n");
  printf("| que expandir la ventana 'OUTPUT', donde |'\n");
  printf("| se activará el mapa de la ciudad. Para  |\n");
  printf("| seleccionar su ubicación, haga clic en  |\n");
  printf("| la zona en la que se encuentra.         |\n");
  printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
  printf("| Para indicar la ubicación, escriba 'S'  |\n");
  printf("+ - - - - - - - - - - - - - - - - - - - - +\n");

  if (scanf(" %c", &respuesta) != 1) {
    fprintf(stderr, "Error al leer la entrada\n");
    return 1;
  }
  if (respuesta != 'S' && respuesta != 's') {
    printf("Respuesta aceptada. Volviendo al menú...\n");
    presioneTeclaParaContinuar();
    limpiarPantalla();
    return;
  }
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 1000, 800);

  gtk_container_add(GTK_CONTAINER(window), drawing_area);

  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event),
                   NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  AppData appData = {&grafo, mapaEmergencias, mapaCompanias, emergencia};

  g_signal_connect(G_OBJECT(drawing_area), "button-press-event",
                   G_CALLBACK(on_button_press_event), &appData);

  gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK);

  char *nombres[] = {"Alto el Rocío",
                     "El Sol",
                     "Sirimiri",
                     "Beethoven",
                     "El Río",
                     "PRIMERA COMPAÑIA",
                     "El Bosque",
                     "El Mar",
                     "Los Aromos",
                     "El Valle",
                     "Avenida Valparaíso",
                     "El Jardín",
                     "Ramayana",
                     "El Campo",
                     "Pasaje 1",
                     "Pasaje 2",
                     "La Colina",
                     "Huanhuali",
                     "Maqui",
                     "Dinamarca",
                     "Araya",
                     "Los Carrera",
                     "San Enrique",
                     "San Lorenzo",
                     "Santa Rita",
                     "Victoria",
                     "La Barranca",
                     "Camanchaca",
                     "Pasaje  Patricio Lynch",
                     "Av Díaz",
                     "La Nube",
                     "Yungay",
                     "Pasaje Lastra",
                     "Las Brisas",
                     "Pasaje Serena",
                     "Pasaje Villar",
                     "Pasaje Marconi",
                     "Pasaje Balmaceda",
                     "Aerosoles",
                     "Jose Bohr",
                     "Jazmin Del Cabo",
                     "Asturias",
                     "Pasaje Baker",
                     "Los Maitenes",
                     "Barros Arana",
                     "Freire",
                     "Sargento Aldea",
                     "Concepción",
                     "El Amanecer",
                     "Londres",
                     "Paris",
                     "La Estación",
                     "El Sendero",
                     "Carlos Condell",
                     "Buenos Aires",
                     "Santa Ema",
                     "Las Vegas",
                     "Carlos Ibañez Del Campo",
                     "Los Molinos",
                     "Las Palmas",
                     "Las Acacias",
                     "Bernardo Leigthon",
                     "El Castillo",
                     "Colón",
                     "La Torre",
                     "Av. Nueva Hipodromo",
                     "La Pista",
                     "El Puerto",
                     "Barcelona",
                     "Los Danieles",
                     "Troncos Viejos",
                     "Rio Valdivia",
                     "San Jorge",
                     "Guacolda",
                     "Fresia",
                     "La Paz",
                     "Laguna Azul",
                     "Remanso",
                     "Catarata",
                     "Caupolican",
                     "El Bosque",
                     "Roma",
                     "Lima",
                     "Ines de Suarez",
                     "El Olivar",
                     "Las Heras",
                     "Valentin Letelier",
                     "La Sierra",
                     "El Llano",
                     "Isabel Riquelme",
                     "Abtao",
                     "Pdte. Montt",
                     "El Escondite",
                     "Juan José Latorre",
                     "America",
                     "Freigburg",
                     "Los Fresnos",
                     "Boulevard",
                     "Yacolen",
                     "Almirante Wilson",
                     "Cumming",
                     "SEGUNDA COMPAÑIA",
                     "Gran Baquedano",
                     "La Camanchaca",
                     "Los Delirios",
                     "Gran Avenida Villa Alemana",
                     "Flora Silvestre",
                     "Troncos Nuevos",
                     "Covadonga",
                     "Medallas de Honor",
                     "Presidentes de Chile",
                     "Rusia",
                     "El Castaño",
                     "Pasaje Los Ríos",
                     "Años 2000",
                     "Venida de Dios",
                     "Avenida Iglesias",
                     "Ramos de Flores",
                     "Calle Sin Salida",
                     "Centro de Chile",
                     "Divina Comedia",
                     "Años Eternos",
                     "Vida Lejana",
                     "Dolores",
                     "Gran Calle",
                     "Inundación",
                     "Matapulgas",
                     "Los Dragones",
                     "Las Sombras",
                     "Brujos",
                     "Fenix Dorado",
                     "Estrellas Fugaces",
                     "Pasaje Girasoles",
                     "La Dormida",
                     "El Pastel",
                     "Calle Abada",
                     "TERCERA COMPAÑIA",
                     "El Olvido",
                     "La Reforma",
                     "Gold Hill",
                     "Bulevar",
                     "La Perla",
                     "Calle Del Mercado",
                     "Infanteria",
                     "Grandes Poderes",
                     "Pasaje Primera",
                     "Pasaje Segunda",
                     "Pasaje Tercera",
                     "Pasaje Cuarta",
                     "Pasaje Quinta",
                     "Pasaje Roquerio",
                     "Elite",
                     "Avenida Errazuriz",
                     "Avenida Las Estaciones",
                     "Calle Principal",
                     "Calle Secundaria",
                     "Liceo Profesional",
                     "Los deseos",
                     "El Esplendor",
                     "Mar Muerto",
                     "Hertz",
                     "Republica Dominicana",
                     "Colon 271",
                     "Calle Condominio con Acacias",
                     "Los Laureles",
                     "Rosas Rojas",
                     "Amapolas",
                     "Azulejos",
                     "Av. Presidentes",
                     "CUARTA COMPAÑIA",
                     "Luis Cruz Martinez",
                     "1 Norte",
                     "2 Norte",
                     "3 Norte",
                     "Gabriela Mistral",
                     "Galerna",
                     "Lautaro",
                     "Los Venedictinos",
                     "Pasaje Oropesa",
                     "Tarragona",
                     "Broadway",
                     "Fifth Avenue",
                     "Champs-Élysées",
                     "Lombard Street",
                     "Abbey Road",
                     "Sunset Boulevard",
                     "Via Veneto",
                     "La Rambla",
                     "Rodeo Drive",
                     "Bourbon Street",
                     "Wall Street",
                     "Michigan Avenue",
                     "Melrose Avenue",
                     "Orchard Road",
                     "Nevsky Prospect",
                     "Ocean Drive",
                     "Nathan Road",
                     "Hollywood Boulevard",
                     "Avenida Paulista",
                     "Portobello Road",
                     "The Strip",
                     "Via della Conciliazione",
                     "Königsallee",
                     "Passeig de Gràcia",
                     "Princes Street",
                     "Amores Eternos",
                     "Ginza",
                     "Unter den Linden",
                     "Linden 777",
                     "Auxiliares",
                     "La Gran Baquedano",
                     "Miniaturas del Sol",
                     "Belleza Diurna",
                     "Calle Cerrada ! !",
                     "Mientos",
                     "Cimientos Negros",
                     "Frieditchz",
                     "Andres de Fuenzalida",
                     "Angamos",
                     "Antofagasta",
                     "Secchi",
                     "Aravena",
                     "Gran Arauco",
                     "Juana De Arco",
                     "Pasaje Pichilemu 135",
                     "Arriero Stay",
                     "Aurora de Chile",
                     "Pensamientos",
                     "Ayuntamiento",
                     "Aviador Fuentes",
                     "Barnechea",
                     "La Dignidad",
                     "Barros Luco",
                     "Belgica",
                     "Av Beaucheff",
                     "Benedicto XV",
                     "Elena Blanco",
                     "Blas Cañas",
                     "Borgoño",
                     "Bombero Adolfo Ossa",
                     "Bretaña",
                     "Cadiz",
                     "Compoamor",
                     "Capitan Wood",
                     "Canelo",
                     "Carlos Clark",
                     "Ramon Silva",
                     "Carnott",
                     "Avenida Centenario",
                     "Club de la Union",
                     "Comandante Canales",
                     "Concha y Toro",
                     "Cordoba con Yungay",
                     "Cornejo Tristan",
                     "Ricardo Marchant",
                     "Churruca",
                     "Dardignac",
                     "Davila Larrain",
                     "Avenida de la Paz!",
                     "Calle Polideportiva",
                     "Diaz Velasco",
                     "Doctor Moore",
                     "Domingo Fautino Sarmiento",
                     "Antonio Ebner",
                     "Hyatt",
                     "Matte",
                     "El Golf",
                     "Embajador Quintana",
                     "Mariño de Lobera",
                     "Ercilla",
                     "Esmeralda",
                     "Estrella Polar",
                     "Eudosia Vicuña",
                     "Eyzaguirre",
                     "Lazcano Manterola",
                     "Lobos Noguera",
                     "PEORESNADA",
                     "Calle Eater Egg",
                     "Fucsias",
                     "1990",
                     "1980",
                     "1970",
                     "1960",
                     "1950",
                     "1940",
                     "1930",
                     "1920",
                     "1910",
                     "Gay",
                     "Gavilan",
                     "Salvo Urriola",
                     "German del Sol",
                     "La Buena Gumercindo",
                     "Feliz",
                     "Infeliz",
                     "Señor Hipolito",
                     "Ibañez Ib.",
                     "Ingeniero Obrecht",
                     "Ingeniero Perez",
                     "Ingeniero Perez",
                     "Profe Araya",
                     "Av Italia 2",
                     "Pasaje Jofre",
                     "Jofre Canning",
                     "Perez Copapopo",
                     "Tenochtitlan",
                     "Lamon Lafer Teh",
                     "Keller",
                     "Los Simpson",
                     "La Bolsa",
                     "Ex Concepcion",
                     "La Virgen",
                     "Latorre Almirante",
                     "Leon Gallo",
                     "Anibal Letelier",
                     "Pollos Feos",
                     "Tokio Rev",
                     "Un Piñon",
                     "Luz Lunar",
                     "Mac-Clure",
                     "Marpa Quilp Ue",
                     "Zañartu",
                     "Mapocho",
                     "Auxiliadora",
                     "Maria Graham",
                     "Marne",
                     "Maxwell",
                     "Michael Jackson",
                     "Mira, Ana",
                     "Quejueh Oyzo Will Yrex",
                     "Moises Flores"
                     "Molina Hermosa",
                     "Montevideo",
                     "Mujika",
                     "Noyel Luckas",
                     "Espartanos Gay",
                     "NoRay Leyespera Tea",
                     "Nuremberg",
                     "Noyla Nacha",
                     "Noyel Vix O",
                     "Razas",
                     "Patronatos",
                     "Corazon",
                     "Uñas",
                     "CALLE NO RECONOCIDA",
                     "NO°0",
                     "Sin recargo",
                     "Congelar Carrera",
                     "Chile Campeon",
                     "Medicinas",
                     "Antropomorfico",
                     "Estado 119",
                     "Estado 120",
                     "Estado 121",
                     "Estado 122",
                     "Estado 123",
                     "Estado 124",
                     "Estado 125",
                     "Shibuya Crossing"};

  crearMallaConNombres(17, 20, 49, nombres);

  gtk_widget_show_all(window);
  gtk_main();

  printf("\n+ - - - - - - - - - - - - - - - - - - - - +\n");
  printf("|          INFORMACION ALMACENADA         |\n");
  printf("+ - - - - - - - - - - - - - - - - - - - - +\n");
  presioneTeclaParaContinuar();

  return 1;
}