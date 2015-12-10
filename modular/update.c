#include "fdtd.h"

/* update magnetic field */
void updateH(Grid *g){
	int mm;

	for (mm = 0; mm < SizeX - 1; mm++)
		Hy(mm) = Chyh(mm) * Hy(mm) + Chye(mm) * (Ez(mm + 1) - Ez(mm));

	//printf("Hy(0): %g, Hy(1): %g\t", Hy(0), Hy(1));
	
	return;
}

/* update electric field */
void updateE(Grid *g){
	int mm;

	for (mm = 1; mm < SizeX - 1; mm++)
		Ez(mm) = Ceze(mm) * Ez(mm) + Cezh(mm) * (Hy(mm) - Hy(mm - 1));
	
	//printf("Ez(0): %g, Ez(1): %g\n", Ez(0), Ez(1));
	return;
}
