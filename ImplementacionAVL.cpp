#include "arbolavl.h"

// Definición de la Raíz global
NodoAVL* raizAVL = NULL;

void inicializarAVL() {
    raizAVL = NULL;
}

// --- Funciones Auxiliares AVL ---

// Retorna la altura de un nodo (0 si es NULL)
static int altura(NodoAVL* n) {
    return n ? n->altura : 0;
}

// Retorna el máximo de dos enteros
static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Crea un nuevo nodo AVL, enlazándolo a un NodoCancion existente
static NodoAVL* crearNodoAVL(NodoCancion* cancion) {
    NodoAVL* nuevo = (NodoAVL*)malloc(sizeof(NodoAVL));
    if (nuevo == NULL) {
        fprintf(stderr, "Error: Falla en la asignacion de memoria para NodoAVL.\n");
        return NULL;
    }
    nuevo->datosCancion = cancion; // Almacenamos el puntero a la canción
    nuevo->izq = nuevo->der = NULL;
    nuevo->altura = 1;
    return nuevo;
}

// Obtiene el factor de balance de un nodo
static int getBalance(NodoAVL* n) {
    return n ? altura(n->izq) - altura(n->der) : 0;
}

// --- Rotaciones ---

// Rotación simple a la derecha [Image of AVL tree Right Rotation]
static NodoAVL* rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;

    // Realizar rotación
    x->der = y;
    y->izq = T2;

    // Actualizar alturas
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

// Rotación simple a la izquierda 
static NodoAVL* rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;

    // Realizar rotación
    y->izq = x;
    x->der = T2;

    // Actualizar alturas
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

// --- Insercion AVL ---

// Inserta recursivamente un NodoCancion en el AVL y mantiene el balance
NodoAVL* insertarAVL(NodoAVL* raiz, NodoCancion* nuevaCancion) {
    // Inserción normal de BST (alcanzar una hoja)
    if (!raiz) return crearNodoAVL(nuevaCancion);

    // Usamos el título para la comparacion
    int cmp = strcmp(nuevaCancion->titulo, raiz->datosCancion->titulo);
    
    if (cmp < 0) {
        raiz->izq = insertarAVL(raiz->izq, nuevaCancion);
    }
    else if (cmp > 0) {
        raiz->der = insertarAVL(raiz->der, nuevaCancion);
    }
    else {
        return raiz; // No insertar duplicados
    }

    //Actualizar altura del nodo actual
    raiz->altura = 1 + max(altura(raiz->izq), altura(raiz->der));

    //Obtener factor de balance
    int balance = getBalance(raiz);

    //Casos de Desbalance (Rotaciones)
    
    // Caso Izquierda-Izquierda (LL)
    if (balance > 1 && cmp < 0)
        return rotacionDerecha(raiz);

    // Caso Derecha-Derecha (RR)
    if (balance < -1 && cmp > 0)
        return rotacionIzquierda(raiz);

    // Caso Izquierda-Derecha (LR)
    if (balance > 1 && cmp > 0) {
        raiz->izq = rotacionIzquierda(raiz->izq);
        return rotacionDerecha(raiz);
    }

    // Caso Derecha-Izquierda (RL)
    if (balance < -1 && cmp < 0) {
        raiz->der = rotacionDerecha(raiz->der);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// --- Busqueda AVL ---

// Busca un nodo por el titulo de la canci0n. Retorna el puntero a NodoCancion o NULL.
NodoCancion* buscarPorTituloAVL(NodoAVL* raiz, const char* titulo) {
    if (!raiz) return NULL;
    
    int cmp = strcmp(titulo, raiz->datosCancion->titulo);
    
    if (cmp == 0) {
        return raiz->datosCancion; //SI se encuentra el titulo devuelve los datos de la cancion
    } else if (cmp < 0) {
        return buscarPorTituloAVL(raiz->izq, titulo);
    } else {
        return buscarPorTituloAVL(raiz->der, titulo);
    }
}

// --- Liberar Memoria ---
void liberarAVL(NodoAVL* raiz) {
    if (raiz) {
        // NOTA: Solo liberamos el nodo AVL, los datos de la cancion se liberan con la lista enlazada (freeList)
        liberarAVL(raiz->izq);
        liberarAVL(raiz->der);
        free(raiz);
    }
}