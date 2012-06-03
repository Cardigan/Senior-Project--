#include "Matrix.h"


#ifndef TARGETING_H
#define TARGETING_H

// ========================
// = debuging expressions =
// ========================
#define dprintd(expr) printf(#expr " = %d\n", expr)
#define dprintc(expr) printf(#expr " = %c\n", expr)
#define dprints(expr) printf(#expr " = %s\n", expr)
#define dprintx(expr) printf(#expr " = %x\n", expr)
#define dprintf(expr) printf(#expr " = %f\n", expr)
#define dprintld(expr) printf(#expr " = %ld\n", expr)

#define paste(front, back) front ## back
#define max(A,B) ((A)>(B)? (A) : (B))

#define debugbar printf("# \n");
#define debugbar1 printf("$ \n");
#define debugbar2 printf("* \n");

#define INTROW "1"
#define INTCOL "5" //debug extend this to a real number when ready
#define INTRANGE "10"


int CreateMatrix(double mean, double std, char* filename);
char* itoa(int val, int base);


//Fills matrix z with arctan of x/y
void Defection(myArray *x, myArray *y, myArray *z);


void elevation(myArray* matX, myArray* matY, myArray* matH,  myArray* matV, myArray* matE);


#endif /*TARGETING_H*/
