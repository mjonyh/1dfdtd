/* Bare-Boones 1D FDTD simulation with a hard source. */

#include <stdio.h>
#include <math.h>

#define SIZE 200
#define LOSS 0.01
#define LOSS_LAYER 180

int main(){
  double ez[SIZE], hy[SIZE-1], ceze[SIZE], cezh[SIZE],
    chyh[SIZE-1], chye[SIZE-1], imp0 = 377.0;
  int qTime, maxTime = 450, mm;

  char basename[80] = "sim", filename[100];
  int frame = 0;
  FILE *snapshot, *freq;
  
  /*initialization of electric field */
  for (mm = 0; mm < SIZE; mm++)
    ez[mm] = 0.0;
    
  /*initialization of magnetic field */
  for (mm = 0; mm < SIZE; mm++)
    hy[mm] = 0.0;
    
  /* set electric field update coefficients */
  for (mm = 0; mm < SIZE; mm++)
    if (mm < 100){ /* free space */
      ceze[mm] = 1.0;
      cezh[mm] = imp0;
    } else if (mm < LOSS_LAYER) {
      ceze[mm] = 1.0;
      cezh[mm] = imp0/9.0;
    } else { /* lossy dielectric */
      ceze[mm] = (1.0 - LOSS) / (1.0 + LOSS);
      cezh[mm] = imp0/ 9.0/(1.0 + LOSS);
    }

  /* set magnetic field update coefficients */
  for(mm = 0; mm < SIZE - 1; mm++)
    if(mm < LOSS_LAYER){
      chyh[mm] = 1.0;
      chye[mm] = 1.0/imp0;
    } else {
      chyh[mm] = (1.0 - LOSS)/ (1.0 + LOSS);
      chye[mm] = 1.0 / imp0 / (1.0 + LOSS);
    }

  freq = fopen("freq.data", "w");

  /* do time stepping  */
  for (qTime = 0; qTime < maxTime; qTime++){

    /* update magnetic field  */
    for(mm = 0; mm < SIZE - 1; mm++)
      hy[mm] = chyh[mm] * hy[mm] + 
        chye[mm] * (ez[mm+1] - ez[mm]);
    
    /*correction for hy TFSF*/
    hy[49] -= exp(-(qTime - 30.)*(qTime - 30.)/100.)/imp0;
 
    /*simple ABC */
    ez[0] = ez[1];

    /*update electric field */
    for(mm = 1; mm <SIZE - 1; mm++)
      ez[mm] = ceze[mm] * ez[mm] + cezh[mm] * (hy[mm] - hy[mm - 1]);

    fprintf(freq, "%d\t%g\n", qTime, ez[30]);

    /*hardwire a source node*/
    ez[50] += exp(-(qTime + 0.5 -(-0.5) -30.)*
              (qTime + 0.5 - (-0.5) - 30.)/100.);

    /*write snapshot if time-step is a multiple of 10*/
    if(qTime % 10 == 0){
      sprintf(filename, "%d.%s", frame++, basename);
      snapshot = fopen(filename, "w");
      for(mm = 0; mm <SIZE; mm++)
        fprintf(snapshot, "%d\t%g\t%g\n", mm, ez[mm], hy[mm]);
      fclose(snapshot);
    }

//  fclose(freq);

//    printf("%d %g\n", qTime, ez[50]);
  }

  return 0;
}
