#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prints.h"

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

void verEmergenciasProceso() {
    limpiarPantalla();
    printf("+--------------------------------------+\n");
    printf("|          EMERGENCIAS EN CURSO        |\n");
    printf("+--------------------------------------+\n");
    for (int i = 1; i < 5; i++) {
        printf("  %d. Emergencia - Forestal\n", i);
        printf("     Direccion - Valparaiso 850\n");
        printf("     Compania despachada - 4\n");
        printf("     Bomberos Presentes - 8\n");
        printf("     Estado actual - EN CURSO\n");
        printf("---------------------------------------\n");
    }
    presioneTeclaParaContinuar();
}

void verEmergenciasTerminadas() {
    limpiarPantalla();
    printf("---------------------------------------\n");
    printf("|        EMERGENCIAS FINALIZADAS       |\n");
    printf("---------------------------------------\n");
    for (int i = 1; i < 5; i++) {
        printf("  %d. Emergencia - Rescate\n", i);
        printf("     Direccion - Los Aromos 760\n");
        printf("     Compania despachada - 1\n");
        printf("     Bomberos Presentes - 5\n");
        printf("     Estado actual - FINALIZADO\n");
        printf("---------------------------------------\n");
    }
    presioneTeclaParaContinuar();
}

void actualizarEstadoEmergencia() {
    int opcion;
    int nuevoEstado;
    limpiarPantalla();
    printf("---------------------------------------\n");
    printf("|           EMERGENCIAS ACTUALES       |\n");
    printf("---------------------------------------\n");
    for (int i = 1; i < 5; i++) {
        printf("  %d. Emergencia - Estructural\n", i);
        printf("     Direccion - Los Robles 760\n");
        printf("     Compania despachada - 1\n");
        printf("     Bomberos Presentes - 5\n");
        printf("     Estado actual - FINALIZADO\n");
        printf("---------------------------------------\n");
    }
    printf("Ingrese el numero de la emergencia a actualizar: ");
    scanf("%d", &opcion);
    printf("Ingrese el nuevo estado de la emergencia:\n");
    printf("1) FINALIZADO\n");
    printf("2) EN CURSO\n");
    printf("3) VOLVER AL MENU\n");
    scanf("%d", &nuevoEstado);
    if (nuevoEstado == 1)
        printf("\n\n ( Aqui cambiamos el estado de la compania )\n");
    else if (nuevoEstado == 2)
        printf("\n\n ( Aqui tambien cambiamos el estado de la compania )\n");
    else if (nuevoEstado == 3)
        printf("\n\nRegresando al menu...\n");
    else {
        printf("Error en la seleccion del nuevo estado.\n");
        printf("Cancelando cambio... Intente nuevamente.\n");
    }
    presioneTeclaParaContinuar();
}

void anadirNuevoOficial() {
    char nombreOficial[100];
    char RUT[10];
    char clave[5];
    printf("---------------------------------------\n");
    printf("|          AÑADIR NUEVO OFICIAL        |\n");
    printf("---------------------------------------\n\n");
    printf("Ingrese nombre del oficial: ");
    scanf(" %[^\n]", nombreOficial);
    for (int i = 0; nombreOficial[i]; i++) {
        nombreOficial[i] = toupper(nombreOficial[i]);
    }
    printf("Ingrese su RUT como USUARIO (formato 123456789): ");
    scanf("%s", RUT);
    strncpy(clave, &RUT[5], 4);
    clave[4] = '\0';
    printf("Su contrasena seran los ultimos 4 digitos: %s\n", clave);
    printf("Se ha ingresado correctamente.\n");
    printf("Bienvenido/a, %s\n\n", nombreOficial);
    presioneTeclaParaContinuar();
}

void mostrarEstadocompanias(int cantidad) {
    limpiarPantalla();
    for (int i = 0; i < cantidad; i++) {
        printf("\n");
        printf("--------------------------------------------\n");
        printf("|       INFORMACION DE LA COMPANIA NO. %d    |\n", (i + 1));
        printf("--------------------------------------------\n");
        printf("Nombre de la compania y numero:    Resc Y Honor, No. %d\n", (i + 1));
        printf("Direccion de la compania:          Los Patroclos 770.\n");
        printf("Cantidad de bomberos disponibles:  1\n");
        printf("Cantidad de emergencias atendidas: 3\n");
        printf("--------------------------------------------\n");
    }
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

void submenu1() {
    char direccion[100];
    char tipoEmergencia;
    printf("\n");
    printf("--------------------------------------------\n");
    printf("|                NOTIFICAR                 |\n");
    printf("--------------------------------------------\n");
    printf("Ingrese la direccion de la emergencia: ");
    scanf(" %[^\n]", direccion);
    printf("\n\n");
    printf("--------------------------------------\n");
    printf("|     Que tipo de emergencia es ?       |\n");
    printf("--------------------------------------\n");
    printf("1) Incendio en zona vegetal.\n");
    printf("2) Incendio en estructura.\n");
    printf("3) Rescate.\n");
    printf("4) Material toxico/peligroso.\n");
    printf("--------------------------------------\n\n");
    printf("Seleccione el tipo de emergencia: ");
    scanf(" %c", &tipoEmergencia);
    if (tipoEmergencia != '1' && tipoEmergencia != '2' && tipoEmergencia != '3' && tipoEmergencia != '4') {
        printf("Error en la seleccion del tipo de emergencia.\n");
        printf("Cancelando aviso... Intente nuevamente.\n");
        presioneTeclaParaContinuar();
        return;
    }
    printf("\n");
    printf("--------------------------------------------\n");
    printf("| Muchas gracias por dar aviso. Se ha      |\n");
    printf("| registrado la emergencia y despachado    |\n");
    printf("| a la compania [X] a las [XX:XX] hrs.     |\n");
    printf("--------------------------------------------\n");
    printf("\n\n");
    presioneTeclaParaContinuar();
}

void submenu2() {
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
                verEmergenciasProceso();
                limpiarPantalla();
                break;
            case '2':
                verEmergenciasTerminadas();
                limpiarPantalla();
                break;
            case '3':
                actualizarEstadoEmergencia();
                limpiarPantalla();
                break;
            case '4':
                anadirNuevoOficial();
                limpiarPantalla();
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

void validacion() {
    char RUT[10];
    char password[5];
    bool test = true;
    int numErrorPass;
    printf("Por favor, ingrese su usuario y contrasena.\n");
    printf("Usuario: ");
    scanf("%s", RUT);
    printf("Contrasena: ");
    scanf(" %s", password);
    if (test != true) {
        printf("--------------------------------------\n");
        printf("Ha ocurrido un error.\n");
        printf("1) Volver a intentar.\n");
        printf("2) Volver al menu.\n");
        scanf(" %d", &numErrorPass);
        if (numErrorPass == 1)
            validacion();
        else
            return;
    } else {
        submenu2();
    }
    presioneTeclaParaContinuar();
}

void submenu3() {
    limpiarPantalla();
    mostrarEstadocompanias();
    presioneTeclaParaContinuar();
}
