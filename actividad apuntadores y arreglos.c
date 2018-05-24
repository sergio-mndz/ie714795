/*
 ============================================================================
 Name        : actividad.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nombre[30];
	unsigned short expediente;
	unsigned short carrera;
	unsigned short edad;
} Alumno;

unsigned int contador = 0;
Alumno alumnos[20];

void registrar(contador){
	Alumno *pointer;
	pointer = &alumnos[contador];
	printf("Nombre del alumno: ");
	scanf("%s", pointer->nombre);
	printf("Expendiente del alumno: ");
	scanf("%d", &pointer->expediente);
	printf("Carrera del alumno: ");
	scanf("%d", &pointer->carrera);
	printf("Edad del alumno: ");
	scanf("%d", &pointer->edad);
	printf("\n");
}

void imprimir(int contador, Alumno alumnos[20]){
	Alumno *apuntador;
	apuntador = &alumnos[0];
	for (int i=0; i<contador; i++){
		printf("Registro %d\n", i+1);
		printf("Nombre: %s\n", (*apuntador).nombre);
		printf("Expediente: %d\n", (*apuntador).expediente);
		printf("Carrera: %d\n", (*apuntador).carrera);
		printf("Edad: %d\n\n", (*apuntador).edad);
		apuntador++;
	}
}

int buscarExp(int n, int cont, Alumno regis[20]){
	int posicion = -1;
	Alumno *pointer;
	pointer = &alumnos[0];
	for (int i=0; i<cont; i++){
		if (n == (*pointer).expediente) posicion = i;
		pointer++;
	}
	return posicion;
}

void eliminarRegistro(int contador, int posicion){
	for(int i = posicion; i<contador; i++){
		alumnos[i] = alumnos[i+1];
	}
}

void buscarRegistro(int contador, int opcion, int dato){
	Alumno *point;
	point = &alumnos[0];
	int bool = 0;
	if (opcion == 1){
		for(int i = 0; i<contador;i++){
			if((*point).expediente==dato){
				printf("Registro encontrado, los datos del registro son:\n");
				printf("Nombre: %s\n", (*point).nombre);
				printf("Expediente: %d\n", (*point).expediente);
				printf("Carrera: %d\n", (*point).carrera);
				printf("Edad: %d\n", (*point).edad);
				bool = 1;
			}
			point++;
		}
	} else {
		for(int i = 0; i<contador;i++){
			if((*point).edad==dato){
				printf("Registro encontrado, los datos del registro son:\n");
				printf("Nombre: %s\n", (*point).nombre);
				printf("Expediente: %d\n", (*point).expediente);
				printf("Carrera: %d\n", (*point).carrera);
				printf("Edad: %d\n", (*point).edad);
				bool = 1;
			}
			point++;
		}
	}
	if (bool == 0) printf("Registro no encontrado\n");
}

int main(void) {
	unsigned int opcion, exp, opBusqueda;
	do{
		printf("     ***MENU***\n\n");
		printf("1) Registrar nuevo alumno\n");
		printf("2) Imprimir datos\n");
		printf("3) Eliminar alumno\n");
		printf("4) Buscar alumno\n");
		printf("0) Salir\n");
		scanf("%d", &opcion);
		printf("\n");
		switch(opcion){
		case 1: //registrar
			if (contador>=20) printf("No hay mas espacio de registro\n");
			else registrar(contador);
			contador++;
			break;
		case 2: //imprimir
			imprimir(contador, alumnos);
			break;
		case 3: //eliminar
			printf("De el expediente del alumno a eliminar: ");
			scanf("%d", &exp);
			if (buscarExp(exp, contador, alumnos) != -1){
				int posi = buscarExp(exp, contador, alumnos);
				eliminarRegistro(contador, posi);
				contador--;
			} else {
				printf("Registro no encontrado\n");
			}
			break;
		case 4: //Buscar
			printf("Introduce la forma de busqueda (1.- por expediente, 2.- por edad): ");
			scanf("%d", &opBusqueda);
			if(opBusqueda == 1){
				int expBusqueda;
				printf("Introduce el expediente a buscar: ");
				scanf("%d", &expBusqueda);
				buscarRegistro(contador, opBusqueda, expBusqueda);
			} else if (opBusqueda == 2){
				int edadBusqueda;
				printf("Introduce la edad a buscar: ");
				scanf("%d", &edadBusqueda);
				buscarRegistro(contador, opBusqueda, edadBusqueda);
			}
			break;
		default:
			opcion = 0;
		}
	}while (opcion != 0);
}
