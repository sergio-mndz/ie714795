/*
 ============================================================================
 Name        : serie.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calcularPi(){
	double sum = 0;
	unsigned long denom = 1;
	int signo = 1;
	for (long i=1; i<=3125000000; i++){
		sum += signo*4.0/denom;
		denom += 2;
		signo *= -1;
	}
	return sum;
}

int main(void) {
	clock_t tiempo1, tiempo2, tfinal;
	int num;
	printf("Numero de hilos: ");
	scanf("%d", &num);
	tiempo1=clock();
	printf("Pi:\t%.10lf\n", calcularPi());
	tiempo2=clock();
	tfinal = (double)(tiempo2-tiempo1)/1000;
	printf("Tiempo:\t%lu ms", tfinal);
}
