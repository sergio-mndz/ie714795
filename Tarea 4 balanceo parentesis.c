/*
 * tarea4parte2.c
 *
 *  Created on: 2 jul. 2018
 *      Author: sergio_mndz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueStackTarea4.h"

bool balancedBrackets(char *exp);

int main(void) {
	bool verificar;
	char c=1;
	int i=0, j=1;
	char* expresion = (char*)malloc(sizeof(char));
	while (c != '\n') {
		c = getc(stdin);
		expresion[i] = c;
	    i++;
	    j++;
	    expresion = (char*)realloc(expresion, j * sizeof(char));
	}
	expresion[i] = '\0';
	verificar = balancedBrackets(expresion);
	if(verificar == true) printf("Esta balanceado\n");
	else printf("No esta balanceado\n");
	free(expresion);
	return 0;
}

bool balancedBrackets(char *exp){
	Stack pila = createStack();
	bool entrada;
	char* dato;
	int contador = 0;
	// (==40, )==41, [==91, ]==93
	while(*(exp+contador)!='\n'){
		if (exp[contador]==40 || exp[contador]==91){
			entrada = push(pila, (exp+contador));
			if(entrada==false){
				return false;
			}
		}
		if(exp[contador]==41){
			if(pila->size==0) return false;
			dato = (char*)pop(pila);
			if(dato[0]!=40){
				return false;
			}
		}
		if(exp[contador]==93){
			if(pila->size==0) return false;
			dato = (char*)pop(pila);
			if(dato[0]!=91){
				return false;
			}
		}
		contador++;
	}
	if(pila->size!=0) return false;
	else return true;
}

