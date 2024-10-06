/*
============================================================================
Práctica: 1
Ejercicio: 2
Carmen Gallardo Martín, Pablo Mendieta Ruiz, Miguel Ángel Rojo Gala
Última revisión: 14/10/2022
Resumen/Enunciado: Calcular producto escalar de dos vectores
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>

void LeerVector (float *vector, int n){ //Función que lee los datos introducidos por el usuario.
	int i;
	for(i = 0; i < n; i++){
		printf("\nIntroduzca el elemento %d: ", i + 1);
		scanf("%f", vector + i);
	}
}

void ImprimirVector (float *v, int n){ //Función que muestra por pantalla los datos de un vector.
	int i;
	printf("[");
	for(i = 0; i < n; i++){
		//printf("\nCoordenada %d: %5.2f", i + 1, *(v + i));
		printf("%5.2f",v[i]);
        if(i!= n-1){
           printf(",");
        }

	}
	printf(" ]\n");
}

void ProductoEscalar (float *v1, float *v2, int n, float *ppe) {//Función que calcula el producto escalar.
	int i;
	for(i = 0; i < n; i++) {
		*ppe = *ppe + (*(v1 + i))*(*(v2 + i));
	}
}

int main(){

	int n;
	int x;
	float * ptrvector1;
	float * ptrvector2;
	float pe;
	float * ppe = &pe;

	system("color 02"); //Cambio color fondo y texto
    system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo."); //Cambiamos el titulo
	printf("Este programa calcula el producto escalar dados dos vectores introducidos por teclado.\n");


	do {
		//Pedimos la longitud de los vectores:
		printf("\nIntroduzca la longitud de los vectores: ");
		scanf("%d", &n);
        while(n <= 0){
            printf("Valor invalido, introduzca valor positivo:\n");
            scanf("%d", &n);
		}


		//Asignamos memoria de manera dinámica a los dos vectores con dos punteros:
		ptrvector1 = (float *) calloc(n, sizeof(float));
		ptrvector2 = (float *) calloc(n, sizeof(float));

		//Leemos el primer vector:
		system("title PR1_P2: Lectura de vectores");
		printf("\nAhora introduzca las coordenadas del primer vector");
		LeerVector(ptrvector1, n);
		//printf("\n\nVector 1: "); ImprimirVector(ptrvector1, n); //Para comprobar.

		//Leemos el segundo vector:
		printf("\n\nAhora introduzca las coordenadas del segundo vector");
		LeerVector(ptrvector2, n);
		//printf("\n\nVector 2: "); ImprimirVector(ptrvector2, n); //Para comprobar.

		//Llamamos a la función para calcular el producto escalar:
		pe = 0;
		ProductoEscalar(ptrvector1, ptrvector2, n, ppe);

		//Mostramos los resultados por pantalla:
		system("title PR1_P2: JAVIER TE FOLLO");
		printf("\n======= RESULTADO =======\n");
		printf("Vector 1:");
		ImprimirVector(ptrvector1, n);
		printf("\nVector 2:");
		ImprimirVector(ptrvector2, n);
		printf("\nEl producto escalar de los dos vectores es: %.2f.", pe);
		//Liberamos la memoria que habíamos ocupado:
		free(ptrvector1);
		free(ptrvector2);

		printf("\n\nSi quiere hacer mas calculos introduzca un 1, si desea acabar introduzca un 0\n");
		scanf("%d", &x);
		while(x!=1 && x!=0){
            printf("Valor invalido, introduzca un 0 o un 1\n");
            scanf("%d", &x);
		}
	} while (x == 1);
	printf("\nSe cierra el programa.");
	return  0;
}
