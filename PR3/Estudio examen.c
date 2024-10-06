/********************************************************
*               TAD Conjunto Naturales
* Implementación de conjuntos finitos mediante vectores
*             EDA IM | Curso 2022 - 2023
*
*           Autor: Javier Sánchez Soriano
********************************************************/

#include <stdio.h>
#include <stdlib.h>

#define N 5 // Valor bajo para pruebas (llenar el conjunto)

//----- Declaraciones de tipos -----//
// Tad Conjunto naturales
typedef struct conjunto {
    int contenido[N];   // Array donde se guardan los numeros
    int ultimo;         // Indice del ultimo elemento
} tConjunto;            // Tipo conjunto basado en vector

typedef enum boolean {FALSE, TRUE} tBool;   // Enumerado que "simula" los booleanos

//----- Declaraciones de funciones del TAD -----//
tConjunto cjtoVacio();
tConjunto unit(int elemento);
tBool esConjuntoVacio(tConjunto conjunto);
tBool esta(int elemento, tConjunto conjunto);
void aniadir(int elemento, tConjunto *conjunto);
void quitar(int elemento, tConjunto *conjunto);
void mostrarConjunto(tConjunto *conjunto);
// faltan union, interseccion y diferencia
int cardinal (tConjunto conjunto);

//----- Implementaciones de las funciones del TAD -----//
tConjunto cjtoVacio() {
    tConjunto conjunto;
    conjunto.ultimo = -1;   // Conjunto vacio si ultimo elemento esta en posicion -1.
    return conjunto;
}

tConjunto unit(int elemento) {
    tConjunto conjunto;
    conjunto.ultimo = 0;    // El primer elemento del array en posicion 0. En diapositivas array con indices 1 a N
    conjunto.contenido[conjunto.ultimo] = elemento; // Se pone el elemento en la primera posicion del array
    return conjunto;
}

tBool esConjuntoVacio(tConjunto conjunto) {
    return conjunto.ultimo==-1;     // Si el ultimo elemento esta en posicion -1 es que el conjunto esta vacio. Ver cjtoVacio()

    /*
    // Alternativa que hace lo mismo
    tBool vacio = FALSE;
    if (conjunto.ultimo == -1) {
        vacio = TRUE;
    }
    return vacio; */
}

tBool esta(int elemento, tConjunto conjunto){
    tBool encontrado = FALSE;
    int i = 0;
    while(!encontrado && i<=conjunto.ultimo) {
        encontrado = (conjunto.contenido[i]==elemento);

        /*
        // Alternativa que hace lo mismo
        if (conjunto.contenido[i]==elemento) {
            encontrado = TRUE;
        }
        */

        i++;    // Se incrementa indice para seguir iterando...
    }
    return encontrado;
}

void aniadir(int elemento, tConjunto *conjunto){
    if (!esta(elemento, *conjunto)) {
        // Elemento no esta dentro
        if (conjunto->ultimo< (N-1) )  { // Con 'conjunto->ultimo<N' desbordabamos la capacidad
            // Cabe en el conjunto
            conjunto->ultimo++;
            conjunto->contenido[conjunto->ultimo] = elemento;
        }
        else { // No cabe en el conjunto
            printf("ERROR - aniadir: No cabe el elemento %d.\n", elemento);
        }
    }
    else { // elemento ya estaba dentro
        printf("ERROR - aniadir: No se puede aniadir el valor %d, ya estaba dentro.\n", elemento);
    }
}

void quitar(int elemento, tConjunto *conjunto){
    int i = 0;

    // Bucle que simplemente itera hasta encontar elemento en conjunto.
    //   Si lo encuentra, i almacenara su posicion.
    //   Si no lo encuentra, i será mayor que ultimo por la ultima iteracion.
    while(i<=conjunto->ultimo && conjunto->contenido[i]!=elemento) {
        i++;    // Se incrementa indice para seguir iterando...
    }

    if (i<= conjunto->ultimo) {
        conjunto->contenido[i] = conjunto->contenido[conjunto->ultimo];
        conjunto->ultimo--;
    }
    else { // elemento no estaba dentro del conjunto
        printf("INFO - quitar: No se puede quitar, NO estaba dentro.\n");
    }
}
void mostrarConjunto(tConjunto *conjunto){
    printf("El contenido del conjunto: \n");
    if (!esConjuntoVacio(*conjunto)){

        printf("%d \n",conjunto->contenido);
    }

   /* if (p!= NULL) {
        tNodo *aux = p->Cima;
        while(aux != NULL) {
            printf("%d \n", aux->elemento); // Muestro el valor
            aux = aux->sig; // paso al siguiente valor
        }
    }
    else {
        printf("Nada que mostrar. Pila vacia.\n");
    }*/
}

int cardinal (tConjunto conjunto){
    return conjunto.ultimo+1;
}

// PROGRAMA PRINCIPAL
int main() {
    // Las pruebas de las operaciones

    // mis conjuntos para pruebas
    tConjunto c1 = cjtoVacio(); // inicializo vacio
    tConjunto c2 = unit(4);     // Inicializo con un valor

    if (esConjuntoVacio(c1)) { printf("C1 vacio! \n"); }
    if (esConjuntoVacio(c2)) { printf("C2 vacio! \n"); }

    aniadir(33, &c2); // segundo valor
    aniadir(16, &c2); // tercero
    aniadir(4, &c2);  // valor que ya estaba
    aniadir(5, &c2);  // cuarto...
    aniadir(6, &c2);  // quinto, con esto llenamos (Si N=5)
    aniadir(7, &c2);  // Con N 5 este ya no debería caber...

    printf("Cardinal C2: %d \n", cardinal(c2));

    if (esta(33, c2))   { printf("Esta el 33 en C2. \n"); }
    if (esta(10,c2))    { printf("Esta el 10 en C2. \n"); }
    if (esta(4,c2))     { printf("Esta el 4 en C2. \n"); }

    quitar(33, &c2);
    quitar(1, &c2);

    if (esta(33, c2))   { printf("Esta el 33 en C2. \n"); }

    printf("Cardinal C2: %d \n", cardinal(c2));

    mostrarConjunto(&c2);

	// Probar operaciones que faltan por implementar... ver diapositivas del tema
}
