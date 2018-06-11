/*
 ============================================================================
 Name        : Hilos.c
 Author      : Sergio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{
	unsigned long long inicio;
	unsigned long long final;
	long double sumaParcial;
}Rango;

void * suma(void *parametro);


int main(void) {
	clock_t tiempo1, tiempo2;
	long tfinal;
	int num, i;
	long double sumaPi = 0;
	printf("Numero de hilos: ");
	scanf("%d", &num);

	Rango rango[num];
	rango[0].inicio = 1;
	rango[0].final = 50000000000/num;
	rango[0].sumaParcial = 0;
	for(i=1; i<num; i++){
		rango[i].sumaParcial = 0;
		rango[i].inicio = rango[i-1].final + 1;
		rango[i].final = rango[i].inicio + 50000000000/num;
	}
	rango[num-1].final = 50000000000;

	tiempo1=clock();

	pthread_t thread[num];
	for(i=0; i<num; i++){
		pthread_create(&thread[i], NULL, suma, (void *) &rango[i]);
	}

	for(i=0; i<num; i++){
		pthread_join(thread[i], NULL);
	}

	tiempo2=clock();
	tfinal = (tiempo2-tiempo1)/1000;

	for(i=0; i<num; i++){
		sumaPi += rango[i].sumaParcial;
	}
	printf("%.10LF\n", sumaPi);
	printf("Tiempo:\t%lu ms", tfinal);

	return EXIT_SUCCESS;
}

void * suma(void *param){
	Rango *r = (Rango*)param;
	int signo;
	long long i;
	long double suma = 0;
	long long denom;

	if (r->inicio%2 == 0){
		signo = -1;
	} else {
		signo = 1;
	}

	denom = 2*r->inicio - 1;
	for(i=r->inicio; i<=r->final;i++){
		suma += signo*4.0/(denom);
		signo *= -1;
		denom += 2;
	}
	r->sumaParcial = suma;
	return NULL;
}
