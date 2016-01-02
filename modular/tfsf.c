#include <math.h>
#include "fdtd.h"
#include "ezinc.h"

static int tfsfBoundary = 49;

void tfsfInit(Grid *g){
	printf("Entr location of TFSF boundary: ");
	scanf("%d", &tfsfBoundary);

	ezIncInit(g);

	return;
}

void tfsfUpdate(Grid *g){
	/* check if ifsfInit() has been called */
	if (tfsfBoundary <= 0){
		fprintf(stderr,
			"tfsfUpdate: tfsfInit must be called before tfsfUpdate. \n"
			" Boundary location must be set to positive value. \n");
		exit(-1);
	}

	/* correct Hy adjacent to TFSF boundary */
	Hy(tfsfBoundary) -= ezInc(Time, 0.0) * Chye(tfsfBoundary);

	/* correct Ez adjacent to TFST boundary */
	Ez(tfsfBoundary + 1) += ezInc(Time + 0.5, -0.5);

	return;
}
/*
void tfsfhard(Grid *g){
	// check if ifsfInit() has been called 
	if (tfsfBoundary <= 0){
		fprintf(stderr,
			"tfsfUpdate: tfsfInit must be called before tfsfUpdate. \n"
			" Boundary location must be set to positive value. \n");
		exit(-1);
	}

	// correct Hy adjacent to TFSF boundary 
	//Hy(tfsfBoundary) -= ezInc(Time, 0.0) + Chye(tfsfBoundary);

	// correct Ez adjacent to TFST boundary 
	Ez(tfsfBoundary + 1) += ezInc(Time + 0.5, -0.5);

	return;
}
*/
