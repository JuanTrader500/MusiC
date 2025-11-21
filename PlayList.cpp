#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necesario para strncpy
#include <SDL2/SDL.h>// libreria para musica
#include <SDL2/SDL_mixer.h>//libreria para musica
#include <conio.h> // Necesario para _getch() (detectar teclas)
// Lista doble mente enlazada para reproducir las canciones de 1 a 100 y de 100 a 1

// Estructura del Nodo 
typedef struct NodoCancion {
    // Datos de la Cancion (tomados del CSV)
    char id[16];                
    char titulo[128];
    char ruta[512];  
	char genero[50];           
    int calificacion;
    
    //Punteros para hacer la linked list
    struct NodoCancion* prev;
    struct NodoCancion* next;
} NodoCancion;//Nombre de nuestra estructura

// Punteros Globales
NodoCancion* head = NULL;  // Inicio de la lista
NodoCancion* tail = NULL;  // Final de la lista 

// ---CORRECCION DEL NODO ---
NodoCancion* crearNodo(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion) {
    NodoCancion* newNode = (NodoCancion*)malloc(sizeof(NodoCancion));
    if (newNode == NULL) { 
        fprintf(stderr, "Memory allocation failed!\n"); 
        return NULL; 
    }
    
    strncpy(newNode->id, id, sizeof(newNode->id) - 1);
    strncpy(newNode->titulo, titulo, sizeof(newNode->titulo) - 1);
    strncpy(newNode->ruta, ruta, sizeof(newNode->ruta) - 1);
    strncpy(newNode->genero, genero, sizeof(newNode->genero) - 1); // Copiamos el género
    newNode->calificacion = calificacion;
    
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


// ---INSERTAR AL FINAL ---
void insertEnd(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion) {
    // AQUI FALTABA PASAR 'genero'
    NodoCancion* newNode = crearNodo(id, titulo, ruta, genero, calificacion);
    
    if (newNode == NULL) return; 

    if (head == NULL) { 
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail; 
        tail = newNode;       
    }
}

void displayForward() {
    NodoCancion* curr = head;
    printf("\n--- Lista de Reproduccion (Ascendente) ---\n");
    while (curr != NULL) {
        // Agregue que muestre el genero tambien
        printf("ID: %s | Titulo: %s | Genero: %s\n", curr->id, curr->titulo, curr->genero);
        curr = curr->next;
    }
    printf("--- Fin de la Lista ---\n");
}

//--------------- TOMAR LOS DATOS DEL ARCHIVO CSV ----------------------

// Definicion del delimitador CSV (Mi archivo CSV lo separe con ";" porque hay nombres de canciones con "," asi evitamos errores
#define DELIMITADOR ";"

void freeList() {
    NodoCancion* current = head;
    NodoCancion* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current); 
        current = next_node;
    }
    head = tail = NULL; 
}

// --- 3. CORRECCION EN EL PARSING ---
// Agregamos el argumento 'genero' y el paso de strtok extra
int parse_csv_line(char *line, char *id, char *titulo, char *ruta, char *genero) {
    char *token;
    int calificacion = -1;
    
    // 1. ID
    token = strtok(line, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(id, token, 15); id[15] = '\0'; 

    // 2. TITULO
    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(titulo, token, 127); titulo[127] = '\0';
    
    // 3. RUTA
    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(ruta, token, 511); ruta[511] = '\0';

    // 4. GENERO (ESTO FALTABA)
    // Leemos el token siguiente que corresponde al género
    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(genero, token, 49); genero[49] = '\0';

    // 5. CALIFICACION
    token = strtok(NULL, DELIMITADOR); 
    if (token != NULL) {
        calificacion = atoi(token); 
    }
    
    return calificacion;
}

// --- 4. CORRECCION EN LA CARGA ---
// Agregamos la variable temporal y actualizamos las llamadas
void load_data_from_csv(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo CSV");
        return;
    }

    char line[1024]; 
    int line_count = 0;
    
    // 1. Descartar encabezado
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("Omitiendo encabezado: %s", line);
    } else {
        fclose(file);
        printf("Archivo CSV vacío.\n");
        return; 
    }

    // 2. Leer datos
    while (fgets(line, sizeof(line), file)) {
        line_count++;
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char id_str[16];
        char titulo_str[128];
        char ruta_str[512];
        char genero_str[50]; // <--- VARIABLE NUEVA
        int calificacion_val;

        // Pasamos genero_str a la funcion de parsing
        calificacion_val = parse_csv_line(line, id_str, titulo_str, ruta_str, genero_str);

        if (calificacion_val != -1) {
            // Pasamos genero_str a la funcion de insertar
            insertEnd(id_str, titulo_str, ruta_str, genero_str, calificacion_val);
        } else {
            fprintf(stderr, "Error al procesar la línea %d: %s\n", line_count, line);
        }
    }

    fclose(file);
    printf("\nDatos cargados exitosamente. Total de nodos creados: %d\n", line_count);
}

// --- GESTIÓN DE AUDIO (SDL2) ---

// Puntero global para la música actual
Mix_Music *musicaActual = NULL;

// 1. Inicializar SDL y Mixer
void initAudio() {
    // Iniciar subsistema de Audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // Iniciar Mixer (Frecuencia 44100Hz, Formato default, 2 canales, chunk 2048)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error Mixer: %s\n", Mix_GetError());
        exit(1);
    }
    printf("✅ Sistema de Audio Inicializado.\n");
}

// 2. Reproducir archivo MP3 desde la ruta
void reproducirMusica(const char *rutaArchivo) {
    // Si hay música sonando o cargada, la liberamos primero
    if (musicaActual != NULL) {
        Mix_HaltMusic();            // Detener
        Mix_FreeMusic(musicaActual); // Liberar memoria anterior
        musicaActual = NULL;
    }

    // Cargar el nuevo archivo
    musicaActual = Mix_LoadMUS(rutaArchivo);
    
    if (musicaActual == NULL) {
        printf("❌ Error cargando MP3 (%s): %s\n", rutaArchivo, Mix_GetError());
        return;
    }

    // Reproducir (el segundo parámetro es loop: 1 = una vez, -1 = infinito)
    Mix_PlayMusic(musicaActual, 1);
    printf("🎵 Reproduciendo: %s\n", rutaArchivo);
}

// 3. Cerrar sistema de audio (al salir del programa)
void cerrarAudio() {
    if (musicaActual != NULL) {
        Mix_FreeMusic(musicaActual);
    }
    Mix_CloseAudio();
    SDL_Quit();
    printf("Audio cerrado correctamente.\n");
}

// Función para buscar y reproducir por ID
void reproducirPorID(const char* idBusqueda) {
    NodoCancion* actual = head;
    int encontrado = 0; // Bandera para saber si lo encontramos

    printf("\n🔍 Buscando cancion con ID: '%s'...\n", idBusqueda);

    // Recorrer toda la lista
    while (actual != NULL) {
        // strcmp compara dos cadenas. Retorna 0 si son IGUALES.
        if (strcmp(actual->id, idBusqueda) == 0) {
            printf("✅ ¡Cancion encontrada!: %s\n", actual->titulo);
            
            // Llamamos a la función de audio que ya tienes
            reproducirMusica(actual->ruta);
            
            encontrado = 1;
            break; // Salimos del bucle porque ya la encontramos
        }
        actual = actual->next; // Pasar al siguiente nodo
    }

    if (encontrado == 0) {
        printf("❌ No se encontro ninguna cancion con el ID: %s\n", idBusqueda);
    }
}

// Función para navegar la lista con teclas
void menuReproduccion() {
    if (head == NULL) {
        printf("La lista de reproduccion esta vacia.\n");
        return;
    }

    NodoCancion* actual = head; // Empezamos por la primera canción
    int tecla = 0;
    int seguir = 1;

    // Reproducir la primera canción automáticamente
    printf("Iniciando reproduccion...\n");
    reproducirMusica(actual->ruta);

    while (seguir) {
        // Limpiar pantalla (Opcional, hace que se vea más limpio en Windows)
        system("cls"); 
        
        printf("\n========================================\n");
        printf("      🎵  REPRODUCTOR DE MUSICA  🎵      \n");
        printf("========================================\n");
        printf("REPRODUCIENDO AHORA:\n");
        printf(">> ID:     %s\n", actual->id);
        printf(">> TITULO: %s\n", actual->titulo);
        printf("----------------------------------------\n");
        printf("[ -> ] Siguiente Cancion\n");
        printf("[ <- ] Cancion Anterior\n");
        printf("[ ESC] Salir al Menu Principal\n");
        printf("========================================\n");

        // Capturar la tecla presionada
        tecla = _getch();

        // Las flechas en Windows envían dos códigos: primero 224, luego el código de la flecha
        if (tecla == 224) {
            tecla = _getch(); // Capturamos el segundo código

            switch (tecla) {
                case 77: // Flecha DERECHA (-->) = Siguiente
                    if (actual->next != NULL) {
                        actual = actual->next;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Has llegado al final de la lista!\n");
                        // Pequeña pausa para que el usuario lea el mensaje
                        _sleep(1000); 
                    }
                    break;

                case 75: // Flecha IZQUIERDA (<--) = Anterior
                    if (actual->prev != NULL) {
                        actual = actual->prev;
                        reproducirMusica(actual->ruta);
                    } else {
                        printf("\n¡Estas al inicio de la lista!\n");
                        _sleep(1000);
                    }
                    break;
            }
        } 
        else if (tecla == 27) { // Tecla ESC (Código ASCII 27)
            seguir = 0; // Romper el bucle
        }
    }
}

int main(int argc, char *argv[]) {
    
    // 1. Iniciar Audio
    initAudio();
    
    // 2. Cargar Datos
    const char* csv_filename = "C:/Users/juana/OneDrive/Escritorio/FinalProyectDataEstructure/playlist.txt";
    printf("Cargando canciones...\n");
    load_data_from_csv(csv_filename);

    // 3. Verificar carga
    if (head == NULL) {
        printf("Error: No se cargaron canciones. Revisa el archivo CSV.\n");
        getchar();
        return 1;
    }

    // 4. Entrar al modo Reproductor (Control por teclas)
    menuReproduccion();

    // 5. Limpieza final
    cerrarAudio();
    freeList();
    
    printf("\nGracias por usar el reproductor.\n");
    return 0;
}

