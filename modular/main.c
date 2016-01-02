#include "fdtd.h"

int main(){
	Grid *g;

	printf("This FDTD module can be used to simulate the propagation \n"); 
	printf("of a gaussian EM-wave of the form \n\n");
	printf("exp[-{(time-delay-location/cdtds)/width}^2] \n\n");

	//printf("[Init]: Allocation. \n");

	ALLOC_1D(g, 1, Grid);		// allocate memory for grid

	//printf("[Init]: Grid. \n");
	gridInit(g);
	//printf("[Init]: ABC. \n");
	abcInit(g);
	//printf("[Init]: TFSF. \n");
	tfsfInit(g);
	//printf("[Init]: Snapshot. \n");
	snapshotInit(g);

	//printf("Initialization complete. \n \n");

	/* do time stepping */
	//printf("Starting time step. \n \n");

	for (Time = 0; Time < MaxTime; Time++){
		//printf("%d. ", Time);
		//printf("Update H \t");
		updateH(g);
		
		//printf("Update tfsf \t");
		tfsfUpdate(g);
		
		//printf("ABC \t");
		abc(g);
		
		//printf("Update E \t");
		updateE(g);
		
		//printf("Snapshot \n");
		//printf("\ntime %d: Ez(0) = %g, Ez(1) = %g", Time, Ez(0), Ez(1));
		snapshot(g);
	}	// end of time stepping

	return 0;
}
