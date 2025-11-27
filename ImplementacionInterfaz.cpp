#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include "interfaz.h"
#include "lista.h"
#include "audio.h"
#include <stdlib.h> // Para rand(), srand() 
#include <time.h>   // Para time()
#include "arbolavl.h"
#include "interfaz.h"

//Menu para pageRank que contiene las interaciones desde 1000 al 10000
void menuRecomendaciones() {
    Recomendador rec;
    int opcion = 0;
    int interacciones = 1000;
    rec.cargarCancionesDesdeLista(); 

    do {
        system("cls");
        printf("   SISTEMA DE RECOMENDACION (PageRank)\n");
        printf("========================================\n");
        printf("1. Simular 1,000 interacciones\n");
        printf("2. Simular 2,000 interacciones\n");
        printf("3. Simular 5,000 interacciones\n");
        printf("4. Simular 10,000 interacciones\n");
        printf("0. Volver al menu principal\n");
        printf("========================================\n");
        printf("> Seleccione cantidad de interacciones: ");
        if (scanf("%d", &opcion) != 1) { 
             while(getchar() != '\n');
             continue; 
        }
        switch(opcion) {
            case 1: interacciones = 1000; break;
            case 2: interacciones = 2000; break;
            case 3: interacciones = 5000; break;
            case 4: interacciones = 10000; break;
            case 0: return;
            default: printf("Opcion no valida.\n"); continue;
        }
        if (opcion != 0) {
            printf("\nGenerando grafo y calculando...\n");          
            // Generar nuevas interacciones
            rec.generarGrafoInteracciones(interacciones);
            // Ejecutar algoritmo (damping 0.85 es estándar)
            std::vector<double> scores = rec.ejecutarPageRank(0.85, 100); // 100 iteraciones es suficiente
            // Mostrar Top 10
            rec.mostrarTop(10, scores);
            printf("\nPresione cualquier tecla para continuar...");
            _getch();
        }

    } while (opcion != 0);
}

//La funcion que llamaremos en el caso 2 Switch: reproducir musica
void menuReproduccion() {
    if (head == NULL) {
        printf("La lista de reproduccion esta vacia.\n");
        return;
    }

    NodoCancion* actual = head;
    int tecla = 0;
    int seguir = 1;

    printf("Iniciando reproduccion...\n");
    reproducirMusica(actual->ruta);
	
	
    do {
        system("cls");
        printf("\n========================================\n");
        printf("        REPRODUCTOR DE MUSICA         \n");
        printf("========================================\n");
        printf("REPRODUCIENDO AHORA:\n");
        if(actual) {
            printf(">> ID:     %s\n", actual->id);
            printf(">> TITULO: %s\n", actual->titulo);
            printf(">> GENERO: %s\n", actual->genero);
        }
        printf("----------------------------------------\n");
        printf("[ -> ] Siguiente Cancion\n");
        printf("[ <- ] Cancion Anterior\n");
        printf("[  0 ] Salir al Menu Principal\n");
        printf("========================================\n");
        tecla = _getch();
        if (tecla == 224) {
            tecla = _getch(); 

            switch (tecla) {
                case 77: // Derecha
                    if (actual && actual->next != NULL) {
                        actual = actual->next;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Fin de la lista!\n");
                        SDL_Delay(1000); // Usamos SDL_Delay en lugar de _sleep para portabilidad
                    }
                    break;

                case 75: // Izquierda
                    if (actual && actual->prev != NULL) {
                        actual = actual->prev;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Inicio de la lista!\n");
                        SDL_Delay(1000);
                    }
                    break;
            }
        } 
        else if (tecla == 48) { // ESC
            Mix_HaltMusic();
			seguir = 0;
            
        }
    }while (seguir!=0);
}
// Inicializa el generador de numeros aleatorios una vez
void inicializar_aleatorio() {
    srand(time(NULL));
}

//Funcion auxiliar
NodoCancion* obtenerCancionAleatoria(NodoCancion* head) {
    if (head == NULL) {
        return NULL; // La lista esta vacía
    }
    // Contar el numero total de nodos (canciones)
    // Contador es igual a 1 para evitar divicoin por 0 en caso de tener un solo nodo 
    //y si hay mas de un nodo el while tiene en cuenta solo n-1 conteos asi que por eso iniciamos en 0
    int count = 1; 
    NodoCancion* temp = head;
    NodoCancion* temp2 = tail;
    //Cerramos nuestro bucle cuando nuestro nodo sea diferente a la cola ya que es una lista circular doble mente enlazada
    while (temp != temp2) {
        count++;
        temp = temp->next;
    }

    if (count == 0) {
        return NULL;
    }

    // Generar un indice aleatorio entre 0 y count
    int randomIndex = rand() % count;

    // Recorrer la lista hasta el indice aleatorio
    NodoCancion* randomNode = head;
    for (int i = 0; i < randomIndex; i++) {
        randomNode = randomNode->next;
    }

    return randomNode;
}

// Nueva funcion para iniciar la reproduccion aleatoria que usaremos en el switch opcion 3
void menuReproduccionAleatoria() {
    if (head == NULL) {
        printf("La lista de reproduccion esta vacia.\n");
        return;
    }

    // Obtener una cancion aleatoria
    inicializar_aleatorio(); // Asegurar que el generador este inicializado
    NodoCancion* actual = obtenerCancionAleatoria(head); 

    if (actual == NULL) {
        printf("Error: No se pudo obtener la cancion aleatoria.\n");
        return;
    }
    
    int tecla = 0;
    int seguir = 1;

    printf("Iniciando reproduccion aleatoria...\n");
    reproducirMusica(actual->ruta);
	
    // Bucle de interaccion (El mismo de arriba)
    do {
        system("cls");  
        
        printf("\n========================================\n");
        printf("        REPRODUCTOR DE MUSICA         \n");
        printf("========================================\n");
        printf("REPRODUCIENDO AHORA:\n");
        if(actual) {
            printf(">> ID:     %s\n", actual->id);
            printf(">> TITULO: %s\n", actual->titulo);
            printf(">> GENERO: %s\n", actual->genero);
        }
        printf("----------------------------------------\n");
        printf("[ -> ] Siguiente Cancion\n");
        printf("[ <- ] Cancion Anterior\n");
        printf("[  0 ] Salir al Menu Principal\n");
        printf("========================================\n");


        tecla = _getch();

        if (tecla == 224) {
            tecla = _getch(); 
            // Logica para ir a la siguiente/anterior cancion en la lista
            switch (tecla) {
                case 77: // Derecha (Siguiente en la lista)
                    if (actual && actual->next != NULL) {
                        actual = actual->next;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Fin de la lista!\n");
                        SDL_Delay(1000); 
                    }
                    break;
                case 75: // Izquierda (Anterior en la lista)
                    if (actual && actual->prev != NULL) {
                        actual = actual->prev;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Inicio de la lista!\n");
                        SDL_Delay(1000);
                    }
                    break;
            }
        }
        else if (tecla == 48) { //salimos con el 0 
            Mix_HaltMusic(); //Detiene la reproduccion
            seguir = 0;
        }
    } while (seguir != 0);
}


// Implementacion de reproduccion por busqueda de nombre usando AVL

// --- FUNCION DE BUSQUEDA POR TITULO Y REPRODUCCION ---
// Esta funcion se usara en el switch en el caso 4 (Punto 2 del proyecto)
void buscarYReproducirPorTitulo() {
    char tituloBusqueda[128];
    NodoCancion* cancionEncontrada = NULL;
    int seguir = 1;
    int tecla = 0;
    
    system("cls"); // Limpiar pantalla
    printf("\n========================================\n");
    printf("   BUSQUEDA RAPIDA POR TITULO (AVL)\n");
    printf("========================================\n");
    printf("Ingrese el titulo exacto de la cancion:\n> ");
    printf("[  0 ] Salir al Menu Principal\n");
    
    // Limpiamos el buffer de entrada por seguridad
    fflush(stdin); 

    // Usamos fgets para leer titulos que contengan espacios
    if (fgets(tituloBusqueda, sizeof(tituloBusqueda), stdin) != NULL) {
        
        // fgets incluye el salto de linea al final, debemos eliminarlo
        size_t len = strlen(tituloBusqueda);
        if (len > 0 && tituloBusqueda[len - 1] == '\n') {
            tituloBusqueda[len - 1] = '\0';
        }

        printf("\nBuscando en el Arbol AVL: '%s'...\n", tituloBusqueda);
        
        //LLAMADA AL ARBOL AVL
        cancionEncontrada = buscarPorTituloAVL(raizAVL, tituloBusqueda); //Usamos la funcion que esta en ImplementacionAVL.cpp
        
        //VERIFICACIÓN Y REPRODUCCIÓN
        if (cancionEncontrada != NULL) {
        	// Bucle de interaccion (El mismo de arriba)
		    do {
		        system("cls");  
		        
		        printf("\nCANCION ENCONTRADA!\n");
		            printf("--------------------------------\n");
		            printf("ID:     %s\n", cancionEncontrada->id);
		            printf("Titulo: %s\n", cancionEncontrada->titulo);
		            printf("Genero: %s\n", cancionEncontrada->genero);
		            printf("--------------------------------\n");
		            
		            printf(" Reproduciendo ahora...\n");
		            reproducirMusica(cancionEncontrada->ruta); // Llamamos a la funcion de reproducirMusica
		
		        	tecla = _getch();

        			if (tecla == 48) { // salimos con el 0 
            			Mix_HaltMusic(); // Detiene la reproducción
            			seguir = 0;}  
						
			    }while (seguir != 0);   							
    
           }
		else {
            printf("\nNo se encontro ninguna cancion con el titulo: '%s'\n", tituloBusqueda);
            printf("Asegurate de escribirlo exactamente igual (Mayusculas/Minusculas).\n");
        } 
	}
}
