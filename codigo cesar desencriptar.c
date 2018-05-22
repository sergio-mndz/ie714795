/*
 ============================================================================
 Name        : codigo.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encriptar(char cadena[50], int desplazamiento){
	for(int i = 0; i<strlen(cadena);i++){
		if((cadena[i]>64 && cadena[i]<91)){
			if((cadena[i]-desplazamiento)<65){
				cadena[i] = cadena[i]+desplazamiento+26;
			} else {
				cadena[i] = cadena[i]-desplazamiento;
			}
		} else if (cadena[i]>96 && cadena[i]<123){
			if((cadena[i]-desplazamiento)<97){
				cadena[i] = cadena[i]-desplazamiento+26;
			} else {
				cadena[i] = cadena[i]-desplazamiento;
			}
		}
	}
	printf("%s", cadena);
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char texto[50];
	int des;

	printf("Introduce el texto ecriptado: ");
	fgets(texto, 50, stdin);
	printf("Introduce el desplazamiento: ");
	scanf("%d", &des);
	encriptar(texto, des);
}
