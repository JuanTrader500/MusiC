#include <stdio.h>
#include "lista.h"
#include "audio.h"
#include "archivo.h"
#include "interfaz.h"
#include "arbolAVL.h"
#include "recomendador.h"

//La clase prinsipal de nuestro proyecto donde esta nuestro menu principal
int main(int argc, char *argv[]) {
    
    //Primero iniciamos el Audio llamando a la funcion
    initAudio();
    
    // Ahora debemos de cargar los datos por medio de nuestro archivo txt en formato csv separado por ";"
    const char* csv_filename = "C:/Users/juana/OneDrive/Escritorio/FinalProyectDataEstructure/playlist.txt";
    printf("Cargando canciones...\n");
    
    //llamamos a la funcion de cargar los datos para que se puedan generar nuestro nodos 
    load_data_from_csv(csv_filename);

    // Verificamos que se cargaron correctamente nuestras canciones.
    if (head == NULL) {
        printf("Error: No se cargaron canciones. Revisa el archivo CSV.\n");
        // Esperar tecla antes de salir
        getchar(); 
        cerrarAudio();
        return 1;
    }
    
    
    int opcion = -1;// opcion del menu
    do{
    	
    	
    	printf("Bienvenido a MusiC++! ingrese una opcion del menu\n");
    	printf("1.Imprimir lista de canciones\n2.Reproducir musica\n3.Reproducir Cancion aleatoria ->?\n");
    	printf("4.Buscar cancion por su nombre usando AVL \n5.Recomendar canciones (PageRank)\n0. Salir\nOpcion->");
    	scanf("%d",&opcion);// Se optiene y se guarda en memoria la opcion del usuario.
    	
    	
    	switch (opcion){
    		
    		case 1 : displayForward(); break; // Funcion para cagar lista de canciones (Recorre la lista circular)
    		
    		case 2: menuReproduccion(); break; //Funcion para reproducir musica eh iteraciones con botones
    		
    		case 3: menuReproduccionAleatoria(); break;// Funcion para buscar un nodo aleatorio de nuestra lista y reproducir la cancion.
    		
    		case 4: buscarYReproducirPorTitulo();
                	printf("\nPresione cualquier tecla para continuar...");
                	break;
            case 5: {
					menuRecomendaciones();
                 	break;}
            
    		
    		case 0: break; // Cerrar el programa.
    		
    		default: printf("ERROR! Ingrese una opcion del menu..."); break;
		}
    	
	}while (opcion != 0);
    
    // Liverar memoria para que nuestro PC no explote :V
    cerrarAudio();
    freeList();
    
    printf("\n5.0 Para Todo el grupo.\n");
    return 0;
}
