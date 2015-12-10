/* terminate left side of the grid */

#include "fdtd.h"

// Initialize ABC
void abcInit(Grid *g){

	return;
}

// Apply the ABC -- only left side of the grid
void abc(Grid *g){
	
	/* simple ABC for the left side */
	Ez(0) = Ez(1);

	return;
}
