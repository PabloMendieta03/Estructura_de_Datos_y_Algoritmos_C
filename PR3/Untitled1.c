/*
==============================================================================
PRÁCTICA: 3
EJERCICIO: 2
ALUMNOS: Carmen Gallardo,Pablo Mendieta y Miguel Ángel Rojo.
ÚLTIMA REVISIÓN: 16/12/2022 - 13:44
RESUMEN/ENUNCIADO: Práctica de árboles binarios.
=============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definición de tipos:
typedef enum {FALSE, TRUE}
tBoolean;
struct NodoArbol {
	struct NodoArbol *pIzq;
	char Dato;
	struct NodoArbol *pDer;
};
typedef struct NodoArbol tNodoArbol; //Sinónimo estructura NodoArbol
typedef tNodoArbol *tpNodoArbol;

/*--- Declaraciones de las funciones ---*/
void InsertarNodo(tpNodoArbol *pArbol, int Valor);
int Menu (void);
tBoolean ComprobarSumaClavesDosNiveles ( tNodoArbol *Arbol, int n1, int n2);
int Sumar (tNodoArbol *Arbol, int Nivel);
void preOrden(tpNodoArbol pArbol);
int calcularAlturaArbol (tpNodoArbol pArbol);
int mayor (int n1, int n2);
void LimpiarArbol(tpNodoArbol * pArbol);
/*--- Implementación de las funciones ---*/
void InsertarNodo(tpNodoArbol *pArbol, int Valor){
	if (*pArbol == NULL) {
		*pArbol = (tpNodoArbol) malloc(sizeof(tpNodoArbol));
		if (*pArbol != NULL) {
			(*pArbol)->Dato = Valor;
			(*pArbol)->pIzq = NULL;
			(*pArbol)->pDer = NULL;
		}
		else {
			printf("No insertado %d. No hay memoria disponible.\n", Valor);
		}
	}
	/*Si ya hay elementos en el árbol*/
	else {
		/* el dato a insertar es menor que el dato en el nodo actual */
		if (Valor < (*pArbol)->Dato) {
			InsertarNodo(&((*pArbol)->pIzq), Valor);
		}
		else if (Valor > (*pArbol)->Dato) {
			InsertarNodo(&((*pArbol)->pDer), Valor);
		}
		else {
			printf(" No se puede insertar para respetar criterio. ");
		}
	}
}
int Menu (){
	int n;
	char enter[2];
	printf("\n\n\tMENU DEL PROGRAMA: \n\t1.Crear arbol binario de busqueda.\n\t2.Comprobar suma de claves.\n"
	"\t3.Salir del programa.");
	printf("\n\nElige la opcion que quiere ejecutar: ");
	scanf("%d%c",&n, &enter);
	return n;
}
tBoolean ComprobarSumaClavesDosNiveles ( tNodoArbol *Arbol, int n1, int n2){
	return Sumar(Arbol, n1) == Sumar (Arbol, n2);
}
int Sumar (tNodoArbol *Arbol, int Nivel){
	int suma = 0;
	//Recorremos el arbol entero y comprobamos cual esta en el nivel que nos interesa
	if (Nivel< 0){
    	printf("Error, nivel invalido \n");
	}
    else{
		if (Nivel==0){
          	if (Arbol!=NULL){
				suma = suma + Arbol->Dato;
		  	}
        }
		else{
           if (Arbol!=NULL)
           {
             suma = Sumar(Arbol->pIzq, Nivel-1) + suma;
             suma = Sumar(Arbol->pDer, Nivel-1) + suma;
           }
        }
	}

	return suma;
}

void preOrden(tpNodoArbol pArbol) {
	/* si el árbol no está vacío, entonces lo recorremos */
	if (pArbol != NULL) {
		printf("%c ", pArbol->Dato);
		preOrden(pArbol->pIzq);
		preOrden(pArbol->pDer);
	}
}

int calcularAlturaArbol (tpNodoArbol pArbol){
    if (pArbol != NULL){
        return 1 + mayor(calcularAlturaArbol(pArbol->pIzq), calcularAlturaArbol(pArbol->pDer));
    }
    else{
    	return 0;
	}
}

int mayor (int n1, int n2){
    if (n1 > n2){
    	return n1;
	}
    else{
    	return n2;
	}
}

void LimpiarArbol(tpNodoArbol * pArbol) {
	/* si el árbol está vacío, entonces no lo vacíamos */
	if (*pArbol != NULL) {
		if (((*pArbol)->pIzq == NULL) || ((*pArbol)->pDer == NULL)) {
			free(*pArbol);
			*pArbol = NULL;
		}
		else {
			LimpiarArbol(&((*pArbol)->pIzq));
			LimpiarArbol(&((*pArbol)->pDer));
			free(*pArbol);
			*pArbol = NULL;
		}
	}
}

int main (){
	//Cambiamos el color de la consola
	system("color F0");
	tpNodoArbol pRaiz = NULL;
	int n;
	char Elem;
	char enter[2];
	int i;
	int n1;
	int n2;
	int altura;
	tBoolean suma;
	do {
		//Cambiamos el titulo de la consolo
		system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo.");
		n = Menu();
	    if (n != 3) {
	    	printf("\n---------------------------------------------------------\n");
		}
	    switch(n){
		    case 1:
		    	system("title PR1_P3: Crear arbol binario de busqueda");
				LimpiarArbol(&pRaiz);
				//PRUEBA: No debería pintar nada.
				//preOrden(pRaiz);
				printf("\nIntroduzca los caracteres que desea introducir al arbol: \n");
				for (i= 0; i<20; i++){
					printf("\nInserte el caracter %d: ", i+1);
					scanf("%c%c", &Elem, &enter);
					InsertarNodo(&pRaiz, Elem);
				}
				printf("\nMostrando elementos en recorrido pre-orden (raiz, hijo izquierdo, hijo derecho): \n");
				preOrden(pRaiz);
				break;
			case 2:
			   	system("title PR1_P3: Comprobar suma de claves");
				if(pRaiz!=NULL){
					altura = calcularAlturaArbol (pRaiz);
					printf("La altura del arbol es: %d, introduzca los niveles que quiere comparar:\n",altura);
					printf("\nEliga el primer nivel: ");
					scanf("%d%c",&n1, &enter);
					while (n1>altura || n1<1){
						printf("\nValor invalido, introduzca un valor entre 1 y la altura del arbol: ");
						scanf("%d%c",&n1, &enter);
					}
					printf("\nEliga el segundo nivel: ");
					scanf("%d%c",&n2, &enter);
					while (n2>altura || n2<1){
						printf("\nValor invalido, introduzca un valor entre 1 y la altura del arbol: ");
						scanf("%d%c",&n2, &enter);
					}
					printf("\nLa suma del nivel %d es : %d\n", n1, Sumar(pRaiz, n1-1));
					printf("La suma del nivel %d es : %d\n", n2, Sumar(pRaiz, n2-1));
					suma = ComprobarSumaClavesDosNiveles(pRaiz,n1-1,n2-1);
					if(suma){
						printf("Las sumas son iguales");
					}else{
						printf("Las sumas no son iguales");
					}
				}
				else{
					printf("\nEl arbol esta vacio, no se puede comprobar la suma de claves.\n");
				}
				break;
		    case 3: //Saliendo del programa
	        	system("title PR1_P2: Fin del programa");
	        	LimpiarArbol(&pRaiz);
				printf("\nSaliendo del programa ...");
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
