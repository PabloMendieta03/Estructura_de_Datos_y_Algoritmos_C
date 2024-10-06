/*
==============================================================================
PRÁCTICA: 1
EJERCICIO: 1
ALUMNOS: Carmen Gallardo,Pablo Mendieta y Miguel Ángel Rojo.
ÚLTIMA REVISIÓN: 14/10/2022 - 12:31:28
RESUMEN/ENUNCIADO: Menú con diversas opciones para leer y editar un fichero
=============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGITUDMAX 50
#define DELIMITADOR ";"
#define NOMFICHERO "fich01.csv"

//Estructura tipo usuario.
typedef struct tipo_usuario {
    char nombre[LONGITUDMAX];
    char apellidos[LONGITUDMAX];
    char pais[LONGITUDMAX];
    char ciudad[LONGITUDMAX];
} tUsuario;

//Tipo boolean
typedef enum boolean {FALSE, TRUE} tBool;

/*--- Declaraciones de las funciones ---*/
void MuestraFichero(tUsuario *e, int *Usuarios);
int LeerFicheroE (char NomFichero[], tUsuario **e, int *Usuarios);
void MostrarLinea(tUsuario **e, int NumLinea);
int EscribirFichero(char NomFichero[], tUsuario *e, int *Usuarios);
int EliminarLinea(tUsuario **e, int NumLinea, int *Usuarios);
int MostrarDatosDeUsuario(tUsuario **e, int *Usuarios);

/*--- Implementación de las funciones ---*/
void MostrarFichero(tUsuario *e, int *Usuarios, int *MayorLen) {
	int i, j, k, huecos;
	//Creamos una tabla para mostrar los datos del fichero:
	printf("\nUSUARIO     NOMBRE");
	for (k = 0; k < *(MayorLen) - 6; k++) {printf(" ");} printf("     ");
	printf("APELLIDOS");
	for (k = 0; k < *(MayorLen + 1) - 9; k++) {printf(" ");} printf("     ");
	printf("PAIS");
	for (k = 0; k < *(MayorLen + 2) - 4; k++) {printf(" ");} printf("     ");
	printf("CIUDAD");
	for (k = 0; k < *(MayorLen + 3) - 6; k++) {printf(" ");} printf("     \n");
	printf("-------     ");
	for (k = 0; k < *(MayorLen); k++) {printf("-");} printf("     ");
	for (k = 0; k < *(MayorLen + 1); k++) {printf("-");} printf("     ");
	for (k = 0; k < *(MayorLen + 1); k++) {printf("-");} printf("     ");
	for (k = 0; k < *(MayorLen + 1); k++) {printf("-");} printf("     \n");

	for (i = 0; i < *Usuarios; i++) {
		printf("%.3d         ", i+1);
		printf("%s", (e + i)->nombre);
		huecos = *(MayorLen) - strlen((e + i)->nombre);
		for (j = 0; j < huecos; j++) {printf(" ");} printf("     ");
		printf("%s", (e + i)->apellidos);
		huecos = *(MayorLen + 1) - strlen((e + i)->apellidos);
		for (j = 0; j < huecos; j++) {printf(" ");} printf("     ");
		printf("%s", (e + i)->pais);
		huecos = *(MayorLen + 2) - strlen((e + i)->pais);
		for (j = 0; j < huecos; j++) {printf(" ");} printf("     ");
		printf("%s\n", (e + i)->ciudad);
	}
}

int LeerFicheroE (char NomFichero[], tUsuario **e, int *Usuarios) {
	//Declaramos las variables necesarias
	FILE *pfich;
	int ctrl = 0;
	int i;
	char fila[LONGITUDMAX];
	char *ptrtoken;
	tUsuario buffer;
	tBool ficheroleido = FALSE;
	int mayorlen[4] = {0, 0, 0, 0};

	*Usuarios = 0;

	pfich = fopen(NomFichero, "r+");
	if (pfich == NULL) {
		// No se ha podido abrir.
		printf("Error: No se puede abrir el fichero \"fich01.csv\\n");
	}
	else {
		ficheroleido = TRUE;
		/* *Usuarios es el total de usuarios */
		while((ctrl = fgetc(pfich)) != EOF){
        	if( ctrl == '\n'){
        		*Usuarios += 1;
			}
		}
		//printf ("\nNumero de datos del archivo: %d\n", *Usuarios);

    	//Volvemos al principio del fichero
		rewind(pfich);

		//Guardamos en nuestro struct los datos del fichero en memoria dinámica:
		(*e) = (tUsuario *) calloc(*Usuarios, sizeof(tUsuario)); //Creamos un vector de tamaño Usuarios

	    i = 0;
		printf("\n'LeerFicheroE' - Estos son los usuarios del fichero leido:\n");

		while(fgets(fila, LONGITUDMAX, pfich) != NULL) {
			//Primera llamada del token (nombre)
			ptrtoken = strtok (fila, DELIMITADOR);
			if (strlen(ptrtoken) > mayorlen[0]) {
				mayorlen[0] = strlen(ptrtoken);
			}
			if(ptrtoken != NULL){
				strcpy(buffer.nombre,ptrtoken);
			}
			//Apellidos
			ptrtoken = strtok (NULL, DELIMITADOR);
			if (strlen(ptrtoken) > mayorlen[1]) {
				mayorlen[1] = strlen(ptrtoken);
			}
			if(ptrtoken != NULL){
				strcpy(buffer.apellidos,ptrtoken);
			}
			//Pais
			ptrtoken = strtok (NULL, DELIMITADOR);
			if (strlen(ptrtoken) > mayorlen[2]) {
				mayorlen[2] = strlen(ptrtoken);
			}
			if(ptrtoken != NULL){
				strcpy(buffer.pais,ptrtoken);
			}
			//Ciudad
			ptrtoken = strtok (NULL, DELIMITADOR);
			if (strlen(ptrtoken) > mayorlen[3]) {
				mayorlen[3] = strlen(ptrtoken);
			}
			if(ptrtoken != NULL){
				strcpy(buffer.ciudad,ptrtoken);
			}
//			printf("\nUsuario %d:", (i + 1));
//			printf("%s,",(buffer.nombre));
//			printf("%s,",(buffer.apellidos));
//			printf("%s,",(buffer.pais));
//			printf("%s",(buffer.ciudad));

			//Almaceno los datos leidos en mi varible global
			*(*e+i) = buffer;
			i++;
		}
		MostrarFichero(*e, Usuarios, mayorlen);
	}

	//Cerramos el archivo:
	if( fclose(pfich) != 0) {
        printf("Error al cerrar el fichero - 'LeerFicheroE'.\n");
    }
	return ficheroleido;
}

void MostrarLinea(tUsuario **e, int NumLinea) {
	printf("\nMostrando linea %d:\n", NumLinea);
	printf("\n\tUsuario: %d\n", NumLinea);
	printf("\t- Nombre: %s\n",((*e + NumLinea - 1)->nombre));
	printf("\t- Apellido: %s\n",((*e + NumLinea - 1)->apellidos));
	printf("\t- Pais: %s\n",((*e + NumLinea - 1)->pais));
	printf("\t- Ciudad: %s\n",((*e + NumLinea - 1)->ciudad));
}

int EscribirFichero(char NomFichero[], tUsuario *e, int *Usuarios){
	//Declaramos las variables necesarias
	FILE *pfich;
	int ctrl = 0;
	int i = 0;
	tBool ficheroescrito = FALSE;

	pfich = fopen(NomFichero, "w+");
	if (pfich == NULL) {
		// No se ha podido abrir.
		printf("Error: No se puede abrir el fichero \"fich01.csv\\n");
	}
	else {
		while(i < *Usuarios) {
			fputs(((e+i)->nombre), pfich);
			fputc(';', pfich);
			fputs((e+i)->apellidos, pfich);
			fputc(';', pfich);
			fputs((e+i)->pais, pfich);
			fputc(';', pfich);
			fputs((e+i)->ciudad, pfich);
			i++;
		}
		ficheroescrito = TRUE;
	}
	//Cerramos el archivo:
	if( fclose(pfich) != 0) {
        printf("Error al cerrar el fichero - 'EscibirFichero'.\n");
    }
	return ficheroescrito;
}

int EliminarLinea(tUsuario **e, int NumLinea, int *Usuarios){
	int i = NumLinea;
	tBool lineaeliminada = TRUE;
	while (i <= (*Usuarios)) {
		strcpy(((*e+i-1)->nombre),((*e+i)->nombre));
		strcpy(((*e+i-1)->apellidos),((*e+i)->apellidos));
		strcpy(((*e+i-1)->pais),((*e+i)->pais));
		strcpy(((*e+i-1)->ciudad),((*e+i)->ciudad));
		i++;
	}
	*Usuarios -= 1;
//	MostrarLinea(e, NumLinea);
	return lineaeliminada;
}

int MostrarDatosDeUsuario(tUsuario **e, int *Usuarios) {
	tBool usuariomostrado = FALSE;
	tUsuario aux;
	int i;
	printf("\nIntroduce el nombre del usuario que desee encontrar:");
	gets(aux.nombre);
	//puts(aux.nombre);
	printf("\nIntroduce los apellidos del usuario que desee encontrar:");
	gets(aux.apellidos);
	//puts(aux.apellidos);
	for (i = 0; i <= *Usuarios; i++) {
		if (!strcmp(aux.nombre, ((*e + i)->nombre))) {
			if (!strcmp(aux.apellidos, ((*e + i)->apellidos))) {
				printf("\nPais: %s\nCiudad: %s", ((*e + i)->pais), ((*e + i)->ciudad));
				usuariomostrado = TRUE;
			}
		}
	}
	return usuariomostrado;
}


int main(){
	//Definicion de variables
	tUsuario * usuario = NULL;
	tUsuario ** listaUsuarios = &usuario;
	char enter[2];
	int nUsuarios = 0;
	int n = 0, linea = 0;
	tBool FicheroLeido = FALSE, LineaEliminada = FALSE, FicheroEscrito = FALSE, UsuarioMostrado = FALSE;

	//Cambiamos el color de la consola
	system("color F0");

	//Creamos un menú con las diferentes opciones.
    do {
		printf("\n\n\tMENU DEL PROGRAMA: \n\t1.Leer informacion de entrada\n\t2.Eliminar linea\n\t3.Mostrar linea\n"
		"\t4.Mostrar datos de usuario\n\t5.Salir del programa");
      //Cambiamos el titulo de la consolo
  		system("title PR1_P2: Carmen Gallardo, Pablo Mendieta, Miguel Angel Rojo.");
    	printf("\n\nElige la opcion que quiere ejecutar: ");
    	scanf("%d%c",&n, &enter);
    	switch(n){
	        case 1:
				//Leer información de entrada.
        		system("title PR1_P2: Lectura del fichero");
				printf("\nLeyendo la informacion del fichero...\n");
				FicheroLeido = LeerFicheroE(NOMFICHERO, listaUsuarios, &nUsuarios);
				break;
	        case 2://Eliminar línea.
        		system("title PR1_P2: Eliminar linea");
				if(FicheroLeido){
					printf("\nIntroduzca el numero de linea que desea eliminar: ");
					do{
						scanf ("%d",&linea);
						if ((linea <= 0) || (linea > nUsuarios)) {
							printf("ERROR - La linea no puede ser menor que 0 ni mayor que el numero total de usuarios.\n"
							"Introduce una linea dentro de los limites: ");
						}
					} while (((linea <= 0) || (linea > nUsuarios)));
					LineaEliminada = EliminarLinea(listaUsuarios, linea, &nUsuarios);
					if (LineaEliminada) {
						printf("\n'EliminarLinea' - Linea %d eliminada con exito.\n", linea);
						FicheroEscrito = EscribirFichero(NOMFICHERO, usuario, &nUsuarios);
						if (FicheroEscrito) {
							printf("\n'EscribirFichero' - El fichero con la linea eliminada se ha reescrito con exito.\n");
						}
						else {
							printf("\nERROR: El fichero con la linea eliminada no se ha reescrito con exito - 'EscribirFichero'.\n");
						}
					}
				}
          		else {
            		printf("\nError - no se ha leido aun el fichero.\nLealo antes de eliminar una linea.\n");
				}
				break;
	        case 3: //Mostrar línea.
				system("title PR1_P2: Mostrar linea");
	        	if(FicheroLeido){
					printf("\nIntroduzca el numero de linea que desea leer: ");
					do{
						scanf ("%d",&linea);
						if ((linea <= 0) || (linea > nUsuarios)) {
							printf("\nERROR - La linea no puede ser menor que 0 ni mayor que el numero total de usuarios.\n"
							"Introduce una linea dentro de los limites: ");
						}
					} while (((linea <= 0) || (linea > nUsuarios)));
					MostrarLinea(listaUsuarios, linea);
	        	}
	        	else{
					printf("\nError - no se ha leido aun el fichero.\nLealo antes de mostrar una linea.\n");
				}
				break;
	        case 4://Mostrar datos de usuario
				system("title PR1_P2: Mostrar datos de usuario");
	        	if(FicheroLeido){
	        		UsuarioMostrado = MostrarDatosDeUsuario(listaUsuarios, &nUsuarios);
	        		if (UsuarioMostrado) {
	        			printf("\n'MostrarDatosDeUsuario' - Datos de usuario mostrados con exito.\n");
					}
					else {
						printf("\n'MostrarDatosDeUsuario' - Usuario no encontrado.\n");
					}
				}
				else{
					printf("\nError - no se ha leido aun el fichero.\nLealo antes de mostrar datos de un usuario.\n");
				}
	        	break;
	        case 5:
				system("title PR1_P2: Fin del programa");
				printf("\nSaliendo del programa ...\n");
				printf("\nAdios!");
	        	break;
	        default:
	        	printf("\nError - opcion no valida.\n");
	        	break;
    	}
    	if (n != 5) {
    		printf("\n---------------------------------------------------------");
		}
	}while (n!=5);
	free(*listaUsuarios);
	return 0;
}
