/*
 ============================================================================
 Name        : Tarea.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueStackSufijo.h"

char * InfixToPosfix(char *exp);
bool hasHigherPrecedence(char* top, char *operator);

int main(void) {

	char c=1;
	int i=0, j=1;
	char* expresion = (char*)malloc(sizeof(char));
	char* final = (char*)malloc(sizeof(char));
	while (c != '\n') {
		c = getc(stdin);
		expresion[i] = c;
	    i++;
	    j++;
	    expresion = (char*)realloc(expresion, j * sizeof(char));
	}
	expresion[i] = '\0';
	final = (char*)realloc(final, (j*2)*sizeof(char));
	final = InfixToPosfix(expresion);
	printf("%s", final);
	free(expresion);
	return 0;
}

bool hasHigherPrecedence(char* top, char *operator){
	if(operator[0]==42 || operator[0]==47)
		return false;
	else{
		if(top[0]==42 || top[0]==47)
			return true;
		else
			return false;
	}
}

char * InfixToPosfix(char *exp){
	Stack pila = createStack();
	Queue filaResultante = createQueue();
	Queue filaProceso = createQueue();
	int contador=0, i=0;
	char* dato, *datoTemp;
	bool verificador, precedencia;
	char* nuevaTemp = (char*)malloc(sizeof(char));

	while(*(exp+contador)!='\n'){
		offer(filaProceso, (exp+contador));
		contador++;
	}

	while(filaProceso->size>0){
		dato = (char*)poll(filaProceso);
		if(dato[0]>47&&dato[0]<58)
			offer(filaResultante, (Type)dato);
		if(dato[0]==40)
			verificador = push(pila, (Type)dato);
		if(dato[0]==42 || dato[0]==43 || dato[0]==45 || dato[0]==47){
			if (pila->size > 0)
				datoTemp=(char*)top(pila);
			while(pila->size>0 && datoTemp[0]!=40){
				precedencia=hasHigherPrecedence(datoTemp, dato);
				if(precedencia==true){
					datoTemp = (char*)pop(pila);
					offer(filaResultante, (Type)datoTemp);
				} else{
					break;
				}
			}
			verificador = push(pila, (Type)dato);
		}
		if(dato[0]==41){
			datoTemp=(char*)top(pila);
			while(pila->size>0 && datoTemp[0]!=40){
				datoTemp=(char*)pop(pila);
				offer(filaResultante, (Type)datoTemp);
				datoTemp=(char*)top(pila);
			}
			if(pila->size>0)
				datoTemp=(char*)pop(pila);
		}
	}
	while(pila->size>0){
		dato=(char*)pop(pila);
		offer(filaResultante, (Type)dato);
	}
	nuevaTemp = (char*)realloc(nuevaTemp, (filaResultante->size)*2*sizeof(char));
	while(filaResultante->size>0){
		datoTemp = (char*)poll(filaResultante);
		nuevaTemp[i] = *datoTemp;
		nuevaTemp[i+1] = ' ';
		i+=2;
	}
	return nuevaTemp;
}
