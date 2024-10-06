/*
==============================================================================
PRÁCTICA: 2
EJERCICIO: 3
ALUMNOS: Carmen Gallardo,Pablo Mendieta y Miguel Ángel Rojo.
ÚLTIMA REVISIÓN: 30/11/2022 - 17:19
RESUMEN/ENUNCIADO: Desarrollar un programa que lea un fichero que contiene
datos de longitud y latitud
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NOMFICHERO "fich02.csv"

//Tipos struct:
typedef struct tipo_coordenada{
	float latitud;
	float longitud;
}tCoordenada;

//Tipo Nodo:
typedef struct nodo {
    tCoordenada valor;
    struct nodo *sig;
}tNodo;

//Tipo Lista:
typedef struct lista {
    tNodo * primero;
    tNodo * ultimo;
    //tNodo * posicion;
    int N_elementos;
}tLista;

//Tipo boolean
typedef enum boolean {FALSE, TRUE} tBool;

/*--- Declaraciones de las funciones ---*/
tLista lista_vacia();
tBool es_lista_vacia(tLista lista);
tLista unit(tCoordenada elemento);
tLista insertar_al_principio(tLista lista, tCoordenada elemento);
tLista insertar_al_final(tLista lista, tCoordenada elemento);
tLista eliminar_al_principio(tLista lista);
tLista eliminar_al_final(tLista lista);
tCoordenada primero(tLista lista);
tCoordenada ultimo(tLista lista);
void mostrar_lista(tLista lista);
tLista limpiar_lista(tLista lista);
tLista insertar(tLista lista, tCoordenada elemento, int posicion);

tLista introducir_geolocalizacion(tLista lista);
tLista eliminar_geolocalizacion(tLista lista);

//Funcion leer fichero:
tBool leer_fichero(char NomFichero[], tLista * lista);

/*--- Implementación de las funciones ---*/
tLista lista_vacia(){
	//Crea una lista vacia
    tLista lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    //lista.posicion = NULL;
    lista.N_elementos = 0;
    return lista;
}
tLista unit(tCoordenada elemento){
	tLista lista;
	//Crea un nodo
	tNodo * aux = (tNodo*) malloc(sizeof(tNodo));
    aux->valor = elemento;
    aux->sig = NULL;
	lista.primero = aux;
	lista.ultimo = aux;
	lista.N_elementos = 1;
	return lista;
}
tBool es_lista_vacia(tLista lista) {
    return lista.primero == NULL;
}
tLista insertar_al_principio(tLista lista, tCoordenada elemento) {
	tNodo * aux = (tNodo*) malloc(sizeof(tNodo));
    aux->valor = elemento;
    aux->sig = NULL;

    if (lista.primero == NULL) {
        lista.primero = aux;
    }
    else {
    	aux->sig = lista.primero;
    	lista.primero = aux;
    }
    lista.N_elementos += 1;
    return lista;
}
tLista insertar_al_final(tLista lista, tCoordenada elemento) { // Insertar un valor al final de la lista
	tNodo * aux = (tNodo*) malloc(sizeof(tNodo));
    aux->valor = elemento;
    aux->sig = NULL;

    //Si la lista está vacía insertamos el valor dado en la primera posición
    if (lista.primero == NULL) {
    	lista.primero = aux;
    }
    // Guardamos el valor después del último elemento de la lista.
    else {
        lista.ultimo->sig = aux;
    }
    lista.ultimo = aux;
    lista.N_elementos += 1;
    return lista;
}
tLista insertar(tLista lista, tCoordenada elemento, int n) {
	tNodo * posicion = (tNodo*) malloc(sizeof(tNodo));
	posicion = lista.primero;

	tNodo * aux = (tNodo*) malloc(sizeof(tNodo));
    aux->valor = elemento;
    int i = 1;
    tBool ctrl = FALSE;
    if (lista.primero == NULL) {
        lista.primero = aux;
    }
	else {
    	while (posicion!=NULL) {
    	    // comprobamos que el la localización insertada por el usuario no esté en la lista.
    		if (posicion->valor.latitud == elemento.latitud && posicion->valor.longitud == elemento.longitud) {
    			ctrl = TRUE;
        	}
        	posicion = posicion->sig;
		}
		posicion = lista.primero;
        // si la localización no está en la lista recorremos la lista hasta la posición dada y la guarda
		if (!ctrl) {
			while (i < n) {
				if (i == n - 1) {
    				aux->sig = posicion->sig;
    				posicion->sig = aux;
    				lista.N_elementos += 1;
        		}
        		posicion = posicion->sig;
        		i++;
			}
		}
		else {
			printf("\nERROR - 'insertar': El elemento ya se encuentra en la lista.");
		}
	}
	return lista;
}
tLista eliminar_al_principio(tLista lista) {
    tNodo * aux;
    if (!es_lista_vacia(lista)) {
        // guardamos el primer elemento en un auxiliar
    	aux = lista.primero;
        lista.primero = lista.primero->sig;
        if (lista.primero == NULL) { // La lista queda vacia
            lista.ultimo = NULL;
        }
        // liberamos el auxiliar (con el primer elemento).
        free(aux);
        lista.N_elementos = lista.N_elementos - 1;
    }
    else {
        printf("ERROR - eliminar_al_principio: La lista es vacia.\n");
    }
    return lista;
}
tLista eliminar_al_final(tLista lista) {
	tNodo * posicion = (tNodo*) malloc(sizeof(tNodo));
	posicion = lista.primero;
    tNodo * aux = (tNodo*) malloc(sizeof(tNodo));
    if (!es_lista_vacia(lista)) {
        // recorremos la lista hasta llegar que llegar al último elemento
    	while (posicion!=NULL) {
    		if (posicion->sig == lista.ultimo) {
    			aux = lista.ultimo;
    			posicion->sig = NULL;
            	lista.ultimo = posicion;
        	}
        	posicion = posicion->sig;
		}
		lista.N_elementos = lista.N_elementos - 1;
    }
    else {
        printf("ERROR - eliminar_al_final: La lista es vacia.\n");
    }
    free(aux);
    return lista;
}
tLista limpiar_lista(tLista lista) {
	while (!es_lista_vacia(lista)) {
        lista = eliminar_al_principio(lista);
    }
    return lista;
}
tCoordenada primero(tLista lista) {
    tCoordenada resultado;
    resultado.latitud = 0;
    resultado.longitud = 0;
    if (!es_lista_vacia(lista)) {
        resultado = lista.primero->valor;
    }
    else {
        printf("ERROR - primero: La lista es vacia.\n");
    }
    return resultado;
}
tCoordenada ultimo(tLista lista) {
    tCoordenada resultado;
    resultado.latitud = 0;
    resultado.longitud = 0;
    if (!es_lista_vacia(lista)) {
        resultado = lista.ultimo->valor;
    }
    else {
        printf("ERROR - ultimo: La lista es vacia.\n");
    }
    return resultado;
}
void mostrar_lista(tLista lista) {
	int i = 0;
	if (!es_lista_vacia(lista)){
		tLista temporal = lista;
		printf("\nCOORDENADA      Longitud        Latitud\n");
		printf("----------      ----------      ----------\n");
		while (!es_lista_vacia(temporal)) {
			printf("\n%.3d\t\t%f\t%f", i+1, temporal.primero->valor.latitud,temporal.primero->valor.longitud);
			i++;
			temporal.primero = temporal.primero->sig;
		}
	}
	else{
		printf("\nERROR - lista vacia\n");
	}
}
//Funcion leer_fichero:
tBool leer_fichero(char NomFichero[], tLista * lista) {
	//Declaramos las variables necesarias
	FILE *pfich;
	int ctrl = 0;
	float dato1 = 0;
	float dato2 = 0;
	int contador = 0;
	tBool ficheroLeido = FALSE;

	pfich = fopen(NomFichero, "r+");
	if (pfich == NULL) {
		// No se ha podido abrir.
		printf("Error: No se puede abrir el fichero \fich02.csv\\n");
	}
	else {
		ficheroLeido = TRUE;
		//Guardamos en memoria dinámica:
		tCoordenada cordAux;
		tLista aux;
		while((ctrl = fscanf(pfich, "%f; %f", &dato1, &dato2)) != EOF) {
			contador += 1;
			cordAux.latitud= dato1;
			cordAux.longitud= dato2;
			*lista = insertar_al_final(*lista, cordAux);
		}
		lista->N_elementos = contador;
	}

	//Cerramos el archivo:
	if( fclose(pfich) != 0) {
        printf("Error al cerrar el fichero - 'LeerFichero'.\n");
    }

    return ficheroLeido;
}

tLista introducir_geolocalizacion(tLista lista) {
	tCoordenada geolocalizacion;
	int posicion = 0;
	printf("\nIntroduce la geolocalizacion que desea insertar de la siguiente manera: '-12.45;34.21'.");
	printf("\nIntroduzca la geolocalizacion que desea introducir: ");
	scanf("%f;%f", &geolocalizacion.latitud, &geolocalizacion.longitud);
	printf("\nIntroduzca la posicion en la que desea introducir esta geolocalizacion: ");
	scanf("%d", &posicion);
	while (posicion < 1 || posicion > lista.N_elementos+1){ //POR SI QUIERES METERLO AL FINAL UN +1
		printf("\nIntroduzca una posicion valida (ni menor que uno ni mayor que el total): ");
		scanf("%d", &posicion);
	}
	lista = insertar(lista, geolocalizacion, posicion);
	return lista;
}
tLista eliminar_geolocalizacion(tLista lista) {
	tNodo * posicion = (tNodo*) malloc(sizeof(tNodo));
	posicion = lista.primero;

	tCoordenada geolocalizacion;
	tBool ctrl = FALSE;
	tLista laux = lista_vacia();

	printf("\nIntroduce la geolocalizacion que desea eliminar de la siguiente manera: '-12.45;34.21'.");
	printf("\nIntroduzca la geolocalizacion que desea eliminar: ");
	scanf("%f;%f", &geolocalizacion.latitud, &geolocalizacion.longitud);

	while (posicion != NULL) {
		if(posicion->valor.latitud != geolocalizacion.latitud && posicion->valor.longitud != geolocalizacion.longitud){
			laux = insertar_al_final(laux, posicion->valor );
		}else{
			printf("Valor eliminado con exito.");
			ctrl = TRUE;
		}
        posicion = posicion->sig;
	}
	if(ctrl != TRUE){
		printf("No se ha encontrado el valor solicitado.\n");
	}

	return laux;
}

int main(){
	//Cambiamos el color de la consola
	system("color F0");

	//Declaración de variables
	char enter[2];
	int n = 0;
	tBool ficheroLeido = FALSE;
	tLista lista = lista_vacia();
	tLista * ptr_lista = &lista;

	//Lee información de entrada.
    system("title PR1_P3: Lectura del fichero");
	printf("\nLeyendo la informacion del fichero...\n");
	ficheroLeido = leer_fichero(NOMFICHERO, ptr_lista);
	if (ficheroLeido) {
		printf("\nFichero leido y guardado con exito.\n");
	}
	if(ficheroLeido){
		//Creamos un menú con las diferentes opciones.
	    do {
			printf("\n\n\tMENU DEL PROGRAMA: \n\t1.Introducir geolocalizacion.\n\t2.Eliminar geolocalizacion.\n"
			"\t3.Mostrar lista.\n\t4.Salir del programa.");
			//Cambiamos el titulo de la consolo
			system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo.");
	    	printf("\n\nElige la opcion que quiere ejecutar: ");
	    	scanf("%d%c",&n, &enter);
	    	if (n != 5) {
	    		printf("\n---------------------------------------------------------\n");
			}
	    	switch(n){
		        case 1: //Introducir geolocalización
					system("title PR1_P3: Introducir geolocalizacion");
					*ptr_lista = introducir_geolocalizacion(*ptr_lista);
					break;
				case 2: //Eliminar geolocalización
					system("title PR1_P2: Eliminar geolocalizacion");
					*ptr_lista = eliminar_geolocalizacion(*ptr_lista);
					break;
		        case 3: //Mostrar lista.
	        		system("title PR1_P2: Mostrar lista");
					printf("\nImprimiendo...\n");
					mostrar_lista(*ptr_lista);
					break;
		        case 4: //Salir.
	        		*ptr_lista = limpiar_lista(*ptr_lista);
					system("title PR1_P2: Fin del programa");
					printf("\nSaliendo del programa ...\n");
					printf("\nAdios!");
					break;
		        default:
		        	printf("\nError - opcion no valida.\n");
		        	break;
	    	}
	    	if (n != 4) {
	    		printf("\n---------------------------------------------------------");
			}
		} while (n!=4);
	}else{
		printf("\nError - no se ha leido aun el fichero.\n");
	}
	return 0;
}
