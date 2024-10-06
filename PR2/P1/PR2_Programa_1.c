/*
==============================================================================
PRÁCTICA: 2
EJERCICIO: 2
ALUMNOS: Carmen Gallardo,Pablo Mendieta y Miguel Ángel Rojo.
ÚLTIMA REVISIÓN: 23/11/2022 - 13:30
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
} tCoordenada;

//Pilas:
typedef struct nodo {
    tCoordenada valor;
    struct nodo *sig;
} tNodo;

typedef tNodo * tPila;

//Colas:
typedef struct cola {
    tNodo * primero;
    tNodo * ultimo;
} tCola;

//Tipo boolean
typedef enum boolean {FALSE, TRUE} tBool;

/*--- Declaraciones de las funciones ---*/
//Pilas:
tPila pila_vacia();
tBool es_pila_vacia(tPila pila);
tPila apilar(tCoordenada elemento, tPila pila);
tPila desapilar(tPila pila);
tCoordenada cima(tPila pila);
void mostrar_pila(tPila *pila);
tPila limpiar_pila(tPila pila);
tPila eliminar_pares_pila(tPila pila);
tPila intercambiar_posiciones_pila(tPila pila);
//Colas:
tCola cola_vacia();
tBool es_cola_vacia(tCola cola);
tCola encolar(tCola cola, tCoordenada elemento);
tCola desencolar(tCola cola);
tCoordenada primero (tCola cola);
void mostrar_cola(tCola cola);
tCola limpiar_cola(tCola cola);
tCola eliminar_pares_cola(tCola cola);
tCola intercambiar_posiciones_cola(tCola cola);

//Funcion leer fichero:
tBool leer_fichero(char NomFichero[], tPila *p1, tPila *p2, tCola *c1, tCola *c2);

/*--- Implementación de las funciones ---*/

//Pilas:
tPila pila_vacia() {
    /*tPila pila = NULL;
    return pila;*/
    return NULL;
}
tBool es_pila_vacia(tPila pila){
    return pila==NULL;
}
tPila apilar(tCoordenada elemento, tPila pila){
    // Nuevo nodo
    tNodo *nuevo;
    nuevo = (tNodo*) malloc(sizeof(tNodo));
    nuevo->valor = elemento;
    nuevo->sig = pila;
    pila = nuevo;
    return pila;
}
tPila desapilar(tPila pila) {
   tNodo *aux = pila;
   if(es_pila_vacia(pila)) {
    printf("ERROR - desapilar: La pila esta vacia.\n");
    }
    else {
        aux = pila;
        pila = pila->sig;
        free(aux);
    }
   return pila;
}
tCoordenada cima(tPila pila) {
    tCoordenada resultado; // En caso de error devuelve 0
    resultado.latitud = 0;
    resultado.longitud = 0;
    if(es_pila_vacia(pila)) {
        printf("ERROR - cima: La pila esta vacia.\n");
    }
    else {
        resultado.latitud = pila->valor.latitud;
        resultado.longitud = pila->valor.longitud;
    }
    return resultado;
}
void mostrar_pila(tPila *pila) {
	int i = 0, k = 0, huecos = 0;
	div_t tabulacion;
	if (!es_pila_vacia(*pila)){
		tPila temporal = *pila;
		printf("\nCOORDENADA      Longitud        Latitud\n");
		for (k = 0; k < 10; k++) {printf("-");} printf("      ");
		for (k = 0; k < 10; k++) {printf("-");} printf("      ");
		for (k = 0; k < 10; k++) {printf("-");}
		while (!es_pila_vacia(temporal)) {
			tabulacion = div(temporal->valor.latitud, 10);
			printf("\n%.3d             %f", i+1, temporal->valor.latitud);
			if (temporal->valor.latitud < 0 && (fabs(tabulacion.quot) >= 1 && fabs(tabulacion.quot < 10))) {printf("      %f", temporal->valor.longitud);}
			if (temporal->valor.latitud > 0 && (fabs(tabulacion.quot) >= 1 && fabs(tabulacion.quot < 10))) {printf("       %f", temporal->valor.longitud);}
			if (temporal->valor.latitud > 0 && fabs(tabulacion.quot) < 1) {printf("        %f", temporal->valor.longitud);}
			if (temporal->valor.latitud < 0 && fabs(tabulacion.quot) < 1) {printf("       %f", temporal->valor.longitud);}
			if (temporal->valor.latitud < 0 && fabs(tabulacion.quot) > 10){printf("     %f", temporal->valor.longitud);}
			if (temporal->valor.latitud > 0 && fabs(tabulacion.quot) > 10){printf("      %f", temporal->valor.longitud);}
			i++;
			temporal = temporal->sig;
		}
	}
	else{
		printf("\nERROR - pila vacia\n");
	}
}
tPila limpiar_pila(tPila pila){
	while (!es_pila_vacia(pila)) {
        pila = desapilar(pila);
    }
	return pila;
}
tPila eliminar_pares_pila(tPila pila){
	tPila resultado = pila_vacia();
	tPila aux = pila_vacia();
    //Eliminamos los valores pares
	while (!es_pila_vacia(pila)) {
		aux = apilar(cima(pila),aux);
		pila = desapilar(pila);
		if (!es_pila_vacia(pila)){
       		pila = desapilar(pila);
		}
    }
    //Giramos la pila para que empiece por el 1
	while (!es_pila_vacia(aux)) {
		resultado = apilar(cima(aux),resultado);
		aux = desapilar(aux);
    }
	return resultado;
}
tPila intercambiar_posiciones_pila(tPila pila){
	tPila resultado = pila_vacia();
	tPila aux = pila_vacia();
	tCoordenada elemento;
	while (!es_pila_vacia(pila)) {
		elemento = cima (pila);
		if (!(pila->sig == NULL)){
			pila = desapilar(pila);
			aux = apilar(cima(pila),aux);
		}
		aux = apilar(elemento,aux);
		pila = desapilar(pila);
    }
    //Giramos la pila para que empiece por el 1
	while (!es_pila_vacia(aux)) {
		resultado = apilar(cima(aux),resultado);
		aux = desapilar(aux);
    }
    return resultado;
}

//Colas:


}

tCola desencolar(tCola cola) {
    tNodo * aux;
    if (!es_cola_vacia(cola)) {
        aux = cola.primero;
        cola.primero = cola.primero->sig;
        if (cola.primero == NULL) { // La cola queda vacia
            cola.ultimo = NULL;
        }
        free(aux);
    }
    else {
        printf("ERROR - desencolar: La cola es vacia.\n");
    }
    return cola;
}
tCoordenada primero (tCola cola) {
    tCoordenada resultado; // Un valor por defecto (error)
    if (!es_cola_vacia(cola)) {
        resultado = cola.primero->valor;
    }
    else {
        printf("ERROR - primero: La cola es vacia.\n");
    }
    return resultado;
}
void mostrar_cola(tCola cola) {
	int i = 0, k = 0, huecos = 0;
	div_t tabulacion;
	if (!es_cola_vacia(cola)){
		tCola temporal = cola;
		printf("\nCOORDENADA      Longitud        Latitud\n");
		for (k = 0; k < 10; k++) {printf("-");} printf("      ");
		for (k = 0; k < 10; k++) {printf("-");} printf("      ");
		for (k = 0; k < 10; k++) {printf("-");}
		while (!es_cola_vacia(temporal)) {
			tabulacion = div(temporal.primero->valor.latitud, 10);
			printf("\n%.3d             %f", i+1, temporal.primero->valor.latitud);
			if (temporal.primero->valor.latitud < 0 && (fabs(tabulacion.quot) >= 1 && fabs(tabulacion.quot < 10))) {printf("      %f", temporal.primero->valor.longitud);}
			if (temporal.primero->valor.latitud > 0 && (fabs(tabulacion.quot) >= 1 && fabs(tabulacion.quot < 10))) {printf("       %f", temporal.primero->valor.longitud);}
			if (temporal.primero->valor.latitud > 0 && fabs(tabulacion.quot) < 1) {printf("        %f", temporal.primero->valor.longitud);}
			if (temporal.primero->valor.latitud < 0 && fabs(tabulacion.quot) < 1) {printf("       %f", temporal.primero->valor.longitud);}
			if (temporal.primero->valor.latitud < 0 && fabs(tabulacion.quot) > 10){printf("     %f", temporal.primero->valor.longitud);}
			if (temporal.primero->valor.latitud > 0 && fabs(tabulacion.quot) > 10){printf("      %f", temporal.primero->valor.longitud);}
			i++;
			temporal.primero = temporal.primero->sig;
		}
	}
	else{
		printf("\nERROR - cola vacia\n");
	}
}
tCola limpiar_cola(tCola cola){
	while (!es_cola_vacia(cola)) {
        cola = desencolar(cola);
    }
    return cola;
}
tCola eliminar_pares_cola(tCola cola){
	tCola aux = cola_vacia();
	 //Eliminamos los valores pares
	while (!es_cola_vacia(cola)) {
        aux = encolar(aux,primero(cola));
        cola = desencolar(cola);
        if(!es_cola_vacia(cola)){
            cola = desencolar(cola);
        }

	}
    return aux;
}
tCola intercambiar_posiciones_cola(tCola cola){
	tCola resultado = cola_vacia();
	tCola aux = cola_vacia();
	tCoordenada elemento;
	while (!es_cola_vacia(cola)) {
		elemento = primero(cola);
		if (!(cola.primero->sig == NULL)){
			cola = desencolar(cola);
			aux = encolar(aux,primero(cola));
		}
		aux = encolar(aux,elemento);
		cola = desencolar(cola);
    }
    return aux;
}

//Funcion leer_fichero:
tBool leer_fichero(char NomFichero[], tPila *p1, tPila *p2, tCola *c1, tCola *c2){
	//Declaramos las variables necesarias
	FILE *pfich;
	int ctrl = 0;
	float dato1 = 0;
	float dato2 = 0;
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
		tPila aux;
		while((ctrl = fscanf(pfich, "%f; %f", &dato1, &dato2)) != EOF) {
			cordAux.latitud= dato1;
			cordAux.longitud= dato2;

			if(((int) dato2) % 2 == 0) {
        		*p1 = apilar(cordAux, *p1);
				*c1 = encolar(*c1, cordAux);
			}
			if (((int) dato2) % 2 != 0 || ((int) dato2) == 0){
        		*p2 = apilar(cordAux, *p2);
        		*c2 = encolar(*c2, cordAux);
			}
		}
	}
}

int main(){
	//Cambiamos el color de la consola
	system("color F0");

	//Declaración de variables
	char enter[2];
	int n = 0;
	int seleccion;
	tBool ficheroLeido = FALSE;
	tPila p1 = pila_vacia();
	tPila p2 = pila_vacia();
	tPila *pila1 = &p1;
	tPila *pila2 = &p2;
	tCola c1 = cola_vacia();
	tCola c2 = cola_vacia();
	tCola * cola1 = &c1;
	tCola * cola2 = &c2;


	//Creamos un menú con las diferentes opciones.
    do {
    	seleccion = 0;
		printf("\n\n\tMENU DEL PROGRAMA: \n\t1.Gestionar pilas y colas.\n\t2.Mostrar pilas.\n\t3.Intercambiar posiciones pares e impares en pila 1 y pila 2.\n"
		"\t4.Eliminar posiciones pares en pila.\n\t5.Limpiar pilas.\n\t6.Mostrar colas.\n\t7.Intercambiar posiciones pares e impares en cola 1 y cola2."
		"\n\t8.Eliminar posiciones pares en cola.\n\t9.Limpiar colas\n\t10.Salir del programa.");
		//Cambiamos el titulo de la consolo
		system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo.");
    	printf("\n\nElige la opcion que quiere ejecutar: ");
    	scanf("%d%c",&n, &enter);
    	if (n != 10) {
    		printf("\n---------------------------------------------------------\n");
		}
    	switch(n){
	        case 1:
				//Leer información de entrada (pilas y colas).
        		system("title PR1_P2: Lectura del fichero");
				printf("\nLeyendo la informacion del fichero...\n");
				ficheroLeido = leer_fichero(NOMFICHERO, pila1, pila2, cola1, cola2);
				if (ficheroLeido) {
					printf("\nFichero leido y guardado con exito.\n");
				}
				break;
	        case 2://Mostrar pilas 1 y 2.
        		system("title PR1_P2: Mostrar pilas 1 y 2");
				if(ficheroLeido){
					printf("Imprimiendo...\n");
					printf("\nPila 1:\n");
    				mostrar_pila(pila1);
    				printf("\nPila 2:\n");
    				mostrar_pila(pila2);
				}
          		else {
            		printf("\nError - no se ha leido aun el fichero.\n");
				}
				break;
	        case 3: //Intercambiar posiciones pares e impares pila 1 y 2.
				system("title PR1_P2: Intercambiar posiciones pares e impares pila 1 y 2");
	        	if(ficheroLeido){
	        		printf("\nIntercambiando posiciones pares e impares...");
	        		*pila1 = intercambiar_posiciones_pila(*pila1);
	        		*pila2 = intercambiar_posiciones_pila(*pila2);
	        		printf("\nPosiciones intercambiadas con exito.");
	        	}
	        	else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
				break;
	        case 4://Eliminar posicones pares en pila.
				system("title PR1_P2: Eliminar posicones pares en pila");
	        	if(ficheroLeido){
	        		//Pedimos que pila quiere cambiar
	        		printf("\nIndique en que pila (1 o 2) desea eliminar las posiciones pares: ");
	        		scanf("%d",&seleccion);
	        		while(seleccion!=1 && seleccion!=2){
	        			printf("\nValor invalido. Por favor introduzca un número del 1 al 2: ");
	        			scanf("%d",&seleccion);
					}
					printf("\nEliminando posiciones pares de la pila...\n");
	        		if(seleccion == 1){
	        			*pila1 = eliminar_pares_pila(*pila1);
					}
	        		else{
	        			*pila2 = eliminar_pares_pila(*pila2);
					}
    				printf("\nPila modificada con exito.\n");
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
	        case 5://Limpiar pilas.
				system("title PR1_P2: Limpiar pilas");
	        	if(ficheroLeido){
	        		printf("\nVaciando pilas...\n");
	        		*pila1 = limpiar_pila(*pila1);
	        		*pila2 = limpiar_pila(*pila2);
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
	        case 6://Mostrar colas.
				system("title PR1_P2: Mostrar colas");
	        	if(ficheroLeido){
					printf("Imprimiendo...\n");
					printf("\nCola 1:\n");
    				mostrar_cola(c1);
    				printf("\nCola2:\n");
    				mostrar_cola(c2);
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
	        case 7://Intercambiar posiciones pares en colas.
				system("title PR1_P2: Intercambiar posiciones pares en colas");
	        	if(ficheroLeido){
	        		printf("\nIntercambiando posiciones pares e impares...");
	        		*cola1 = intercambiar_posiciones_cola(*cola1);
	        		*cola2 = intercambiar_posiciones_cola(*cola2);
	        		printf("\nPosiciones intercambiadas con exito.");
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
	        case 8://Eliminar posiciones pares en cola.
				system("title PR1_P2: Eliminar posiciones pares en cola");
	        if(ficheroLeido){
	        		//Pedimos que pila quiere cambiar
	        		printf("\nIndique en que cola (1 o 2) desea eliminar las posiciones pares: ");
	        		scanf("%d",&seleccion);
	        		while(seleccion!=1 && seleccion!=2){
	        			printf("\nValor invalido. Por favor introduzca un número del 1 al 2: ");
	        			scanf("%d",&seleccion);
					}
					printf("\nEliminando posiciones pares de la cola...\n");
	        		if(seleccion == 1){
	        			c1 = eliminar_pares_cola(c1);
					}
	        		else{
	        			c2 = eliminar_pares_cola(c2);
					}
    				printf("\nPila modificada con exito.\n");
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
	        case 9://Limpiar colas.
				system("title PR1_P2: Limpiar colas");
	        	if(ficheroLeido){
	        		printf("\nVaciando colas...\n");
	        		c1 = limpiar_cola(c1);
	        		c2 = limpiar_cola(c1);
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\n");
				}
	        	break;
			case 10: //Salir.

				//Eliminamos las pilas para liberar la menmoria dinamica
				*pila1 = limpiar_pila(*pila1);
	        	*pila2 = limpiar_pila(*pila2);
	        	*cola1 = limpiar_cola(*cola1);
	        	*cola2 = limpiar_cola(*cola2);
				system("title PR1_P2: Fin del programa");
				printf("\nSaliendo del programa ...\n");
				printf("\nAdios!");
	        	break;
	        default:
	        	printf("\nError - opcion no valida.\n");
	        	break;
    	}
    	if (n != 10) {
    		printf("\n---------------------------------------------------------");
		}
	} while (n!=10);
	return 0;
}
