#include "ezinc.h"

/* global variables */
static double delay = 30, width = 10, cdtds;

/* promt user for source-function width and delay */
void ezIncInit(Grid *g){
	cdtds = Cdtds;
	printf("Enter delay: ");
	scanf("%lf", &delay);
	printf("Enter width: ");
	scanf("%lf", &width);

	return;
}

/* calculate source function at given time and location */
double ezInc(double time, double location){
	if (width <= 0){
		fprintf(stderr, "ezInc: must call ezIncInit before ezInc. \n"
			"	Width must be positive. \n");
		exit(-1);
	}

	return exp(-pow((time - delay - location / cdtds) / width, 2));
}
