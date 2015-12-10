#include "fdtd.h"

static int temporalStride = 2, spatialStride = 1, startTime = 0, startNode = 1, endNode = 198, frame = 0;
//static char basename[80] = "frame.log";
//static char filename[80] = "frame.log";

void snapshotInit(Grid *g){
	printf("for the snapshots: \n");
	printf(" Duration of simulation is %d steps. \n", MaxTime);
	//printf(" Enter start time and temporal stride: ");
	//scanf(" %d %d", &startTime, &temporalStride);
	printf(" Grid has %d total nodes (ranging from 0 to %d). \n", SizeX, SizeX-1);
	//printf(" Enter the base name: ");
	//scanf(" %s", basename);

	return;
}

void snapshot(Grid *g){
	int mm;
	char filename[100];
	FILE *snapshot;

	/* ensure temporal stride set to a reasonable value */
	if (temporalStride <= 0){
		fprintf(stderr,
			"snapshot: snapshotInit must be called before snapshot. \n"
			"	Temoral stride must be set to positive value. \n");
		exit(-1);
	}
	//printf("Hello snapshot! %d", Time);

	/* get snapshot if temporal conditions met */
	if(Time >= startTime && (Time - startTime) % temporalStride ==0){
		//sprintf(filename, "%s", basename);
		//snapshot = fopen(filename, "a+");
		snapshot = fopen("frame.log", "a+");

		//printf("%d", Time);

		for (mm = startNode; mm <= endNode; mm +=spatialStride)
			fprintf(snapshot, "%g\t", Ez(mm));
		fprintf(snapshot, "\n");

		fclose(snapshot);
	}

	return;
}
