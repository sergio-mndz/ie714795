/*
 ============================================================================
 Name        : Tarea1.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void imprimeAlReves (char arr[], int n){
	printf("%c", arr[n - 1]);
	if(n > 1){
		imprimeAlReves(arr, n - 1);
	}
}

int main(void) {
	char array[100];
	gets(array);
	int n = 0;

	while(array[n]!=0){
		n++;
	}

	imprimeAlReves(array, n);
	return EXIT_SUCCESS;
}
