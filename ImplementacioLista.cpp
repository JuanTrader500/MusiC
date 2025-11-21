#include "lista.h"

// En estas lineas de codigo declaramos la funcion para crear nuestro nodo. con la estrustura declarada en el archivo lusta.h
// Tambien se hace la creacion de la funcion donde se incertaran al final de nuetsra DLL(lista doble enlasada)
// La funcion que utilizamos para imprimir todas las canciones de nuestra PLay list en orden.
// yY muy importante la funcion para Limpiar la memoria 

// Definición real de las variables globales
NodoCancion* head = NULL;
NodoCancion* tail = NULL;


//Crear nodo
NodoCancion* crearNodo(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion) {
    NodoCancion* newNode = (NodoCancion*)malloc(sizeof(NodoCancion));
    if (newNode == NULL) { 
        fprintf(stderr, "Memory allocation failed!\n"); 
        return NULL; 
    }
    
    strncpy(newNode->id, id, sizeof(newNode->id) - 1);
    strncpy(newNode->titulo, titulo, sizeof(newNode->titulo) - 1);
    strncpy(newNode->ruta, ruta, sizeof(newNode->ruta) - 1);
    strncpy(newNode->genero, genero, sizeof(newNode->genero) - 1);
    newNode->calificacion = calificacion;
    
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// insertar al final (tail)
void insertEnd(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion) {
    NodoCancion* newNode = crearNodo(id, titulo, ruta, genero, calificacion);
    
    if (newNode == NULL) return; 

    if (head == NULL) { 
        head = tail = newNode;
        
        //Apuntar a si mismo para cerrar el círculo inicial
        head->next = head;
        head->prev = head;
    } else {
        // Enlace estandar doble
        tail->next = newNode;
        newNode->prev = tail;
        
        //Actualizamos la cola
        tail = newNode;        
        
        //Cerrar el círculo  de nuestra lista circular doble mente enlazada
        tail->next = head; // El siguiente del ultimo es el primero
        head->prev = tail; // El previo del primero es el ultimo
    }
}

void displayForward() {
    if (head == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    NodoCancion* curr = head;
    printf("\n--- Lista de Reproduccion (Circular) ---\n");
    
    // Usamos do-while para asegurar que entre al menos una vez
    do {
        printf("ID: %s | Titulo: %s | Genero: %s\n", curr->id, curr->titulo, curr->genero);
        curr = curr->next;
    } while (curr != head); // Se detiene cuando volvemos al inicio
    
    printf("--- Fin de la vuelta (regresando a Head) ---\n");
}

// Creamos la funcion para liberar memoria y que nuestro pc no explot :V
void freeList() {
    if (head == NULL) return;

    NodoCancion* curr = head;
    NodoCancion* next_node;

    // Recorremos hasta volver al inicio
    do {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    } while (curr != head);

    head = tail = NULL; 
    printf("Memoria liberada correctamente.\n");
}