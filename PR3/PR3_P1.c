/*
==============================================================================
PRÁCTICA: 3
EJERCICIO: 1
ALUMNOS: Carmen Gallardo,Pablo Mendieta y Miguel Ángel Rojo.
ÚLTIMA REVISIÓN: 06/12/2022 - 00:52
RESUMEN/ENUNCIADO: Desarrollar un programa que lea un fichero que contiene
datos de usuarios (nombre, apellido, código postal, código de línea)
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NOMFICHERO "fich04.csv"
#define LONGITUDMAX 50
#define DELIMITADOR ";"

//Estructura tipo dato.
typedef struct tipo_usuario {
    char nombre[LONGITUDMAX];
    char apellido[LONGITUDMAX];
    char cp [5];
    int cl; //codificacion linea
} tPersona;

//Tipo boolean
typedef enum boolean {FALSE, TRUE} tBool;

/*--- Declaraciones de las funciones ---*/
tBool leer_fichero (char NomFichero[], tPersona **lista,int *n);
void mostrar_datos (tPersona **lista, int n);
void ordenacion_quickSort(tPersona **lista, int pequeno, int tamano);
void ordenacion_seleccionDirecta(tPersona **lista,int tamano);
void ordenacion_burbuja_(tPersona **lista,int tamano);

/*--- Implementación de las funciones ---*/
void intercambiar(tPersona ** lista, int i, int j) {
  tPersona temporal;
  temporal = *(*lista + i);
  *(*lista + i) = *(*lista + j);
  *(*lista + j) = temporal;
}
int particion(tPersona **lista, int low, int high) {
    int pivote = (*lista + high)->cl; // El pivote es el elemento que vamos a colocar en su posición correcta.
    int i = (low - 1);
    int j;
    for (j = low; j <= high- 1; j++){
         // Si el elemento es más pequeño que el pivote, se intercambia la posición con este.
        if ((*lista + j)->cl < pivote){
            i++;
            intercambiar(lista, i, j);
        }
    }
    intercambiar(lista, i + 1, high);
    return (i + 1);
}
void ordenacion_quickSort(tPersona **lista, int pequeno, int tamano) {
    if (pequeno < tamano) {
        int pi = particion(lista, pequeno, tamano);
        ordenacion_quickSort(lista, pequeno, pi - 1);  // Ordenar los valores que están antes del pivote.
        ordenacion_quickSort(lista, pi + 1, tamano); // Ordenar los valores que están después del pivote.
    }
}
void ordenacion_seleccion_directa(tPersona **lista,int tamano) {
    int comparaciones = 0; // cuenta el número de veces que se realiza una comparacion
	int i,j,min;
	tPersona aux;
	for (i=0;i<tamano-1;i++) {
		min=i;
		for (j=i+1;j<=tamano-1;j++) {
		  if ((*lista + j)->cl < (*lista + min)->cl)
            min=j;
			comparaciones++;
        }
        intercambiar(lista,i,min);
        // aux = *(*lista + i);
        // *(*lista + i) = *(*lista + min);
        // *(*lista + min) = aux;
	}
	//printf("\n\nN COMPARACIONES: %d \n\n", comparaciones);
}
void ordenacion_burbuja_interruptor(tPersona **lista,int tamano) {
    int comparaciones = 0; // cuenta el número de veces que se realiza una comparacion
    int i,j;
    int interruptor = 1;    // Se va a usar para ahorrar pasadas en caso de tener ya ordenado el array
	tPersona aux;
    i = 0;
    while ( (i < tamano) & interruptor){ // Uso de while en lugar de for. Si está ordenado nos ahorramos pasadas...
        interruptor = 0; // Se inicializa en cada pasada...
        for(j=0; j < tamano-i-1; j++){
            if((*lista + j)->cl > (*lista + j + 1)->cl){
                intercambiar(lista,j, j +1);
               // aux = *(*lista + j);
               // *(*lista + j) = *(*lista + j + 1);
               // *(*lista + j + 1) = aux;
                interruptor = 1; // Se ha realizado intercambio
            }
            comparaciones++;
        }
        i++; // Se incrementa el indice del while
	}
	//printf("\n\nN COMPARACIONES: %d \n\n", comparaciones);
}
tBool leer_fichero (char NomFichero[], tPersona **lista,int *n){
	//Declaramos las variables necesarias
	FILE *pfich;
	*n = 0;
	int ctrl = 0;
	tBool ficheroLeido = FALSE;
	int i = 0;
	int j= 0;
    tPersona buffer;
    char fila[LONGITUDMAX+LONGITUDMAX+5];
    char *ptrtoken;
    int suma1 = 0;
	int suma2 = 0;
    int aleatorio = time(NULL);

	pfich = fopen(NomFichero, "r+");
	if (pfich == NULL) {
		// No se ha podido abrir.
		printf("Error: No se puede abrir el fichero \%f\\n",NomFichero);
	}
	else{
		ficheroLeido = TRUE;
		/* Contamos el numero de personas */
		while((ctrl = fgetc(pfich)) != EOF){
        	if( ctrl == '\n'){
        		*n += 1;
			}
		}
		*n += 1; //Como la última línea no termina en '\n', no cuenta la última linea, por eso le sumamos uno más.
		//Volvemos al principio del fichero
		rewind(pfich);

		//Guardamos en nuestro struct los datos del fichero en memoria dinámica:
		(*lista) = (tPersona *) calloc(*n, sizeof(tPersona)); //Creamos un vector de tamaño n
		//Alamcenamos los datos
		while(fgets(fila, LONGITUDMAX, pfich) != NULL) {
			//Primera llamada del token (nombre)
			ptrtoken = strtok (fila, DELIMITADOR);
			if(ptrtoken != NULL){
				strcpy(buffer.nombre,ptrtoken);
			}
			//Apellido
			ptrtoken = strtok (NULL, DELIMITADOR);
			if(ptrtoken != NULL){
				strcpy(buffer.apellido,ptrtoken);
			}
			//Codigo Postal
			ptrtoken = strtok (NULL, "\n");
			if(ptrtoken != NULL){
				strcpy(buffer.cp,ptrtoken);
			}
			//Codigo de linea
			for (j = 0; j<strlen(buffer.nombre);j++){
				suma1 = suma1 + buffer.nombre[j];
			}
			for (j = 0; j<strlen(buffer.apellido);j++){
				suma1 = suma1 + buffer.apellido[j];
			}
			for (j = 0; j<strlen(buffer.cp);j++){
				suma2 = suma2 + buffer.cp[j];
			}
			srand(aleatorio);
			aleatorio = rand()%100;
			buffer.cl = suma1 - suma2 + aleatorio;
			suma1 = 0;
			suma2 = 0;
			//Lo guardamos:
			*(*lista+i) = buffer;
			i++;
		}
	}
	mostrar_datos (lista, *n);
	//Cerramos el archivo:
	if( fclose(pfich) != 0) {
        printf("Error al cerrar el fichero - 'LeerFichero'.\n");
    }
	return ficheroLeido;
}
void mostrar_datos (tPersona **lista, int n){
	int i;
	for (i = 1; i<=n;i++){
		printf("\nUsuario: %d\n", i);
		printf("\t- Nombre: %s\n",((*lista + i - 1)->nombre));
		printf("\t- Apellido: %s\n",((*lista + i - 1)->apellido));
		printf("\t- Codigo Postal: %s\n",((*lista + i - 1)->cp));
		printf("\t- Codigo de linea: %d\n",((*lista + i - 1)->cl));
	}
}

int main (){
	//Cambiamos el color de la consola
	system("color F0");

	//Declaración de variables
	char enter[2];
	int n = 0;
	int metodoOrd = 0;
	tBool ficheroLeido = FALSE;
	tPersona * persona = NULL;
	tPersona ** listaPersonas = &persona;
	int nPersonas = 0;

	//Creamos un menú con las diferentes opciones.
	do {
		printf("\n\n\tMENU DEL PROGRAMA: \n\t1.Leer fichero y codificar.\n\t2.Ordenar segun codificacion de linea.\n"
		"\t3.Salir del programa.");
		//Cambiamos el titulo de la consolo
		system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo.");
	    printf("\n\nElige la opcion que quiere ejecutar: ");
	    scanf("%d%c",&n, &enter);
	    if (n != 3) {
	    	printf("\n---------------------------------------------------------\n");
		}
	    switch(n){
		    case 1: //Leer fichero
				system("title PR1_P3: Lectura del fichero");
				printf("\nLeyendo la informacion del fichero...\n");
				ficheroLeido = leer_fichero(NOMFICHERO, listaPersonas, &nPersonas);
				if (ficheroLeido) {
					printf("\nFichero leido y guardado con exito.\n");
				}
				break;
			case 2: //Ordenar.
				system("title PR1_P2: Selección de metodo de ordenacion");
				if(ficheroLeido){
					printf("\n\n\tMETODOS DE ORDENACION: \n\t0.QuickSort.\n\t1.Seleccion Directa.\n\t2.Burbuja.");
	    			printf("\n\nElige la opcion que quiere ejecutar: ");
	    			scanf("%d%c",&metodoOrd, &enter);
	    			switch (metodoOrd) {
	    				case 0://QUICK-SORT
	    					ordenacion_quickSort(listaPersonas, 0, nPersonas - 1);
	    					mostrar_datos(listaPersonas, nPersonas);
	    					break;
	    				case 1://SELECCION DIRECTA
	    					ordenacion_seleccion_directa(listaPersonas, nPersonas);
	    					mostrar_datos (listaPersonas, nPersonas);
							break;
	    				case 2://BURBUJA
	    					ordenacion_burbuja_interruptor(listaPersonas, nPersonas);
	    					mostrar_datos(listaPersonas, nPersonas);
							break;
                        default:
                            printf("\nError - opcion no valida.\n");
                            break;
					}
	        	}
	        	else{
					printf("\nError - no se ha leido aun el fichero.\nLealo antes de mostrar una linea.\n");
				}
				break;
		    case 3: //Salir del programa.
	        	system("title PR1_P2: Fin del programa");
				printf("\nSaliendo del programa ...\n");
				free(persona);
				break;
		    default:
		        printf("\nError - opcion no valida.\n");
		        break;
	    }
	    if (n != 3) {
	    	printf("\n---------------------------------------------------------");
		}
	} while (n!=3);
	return 0;
}
