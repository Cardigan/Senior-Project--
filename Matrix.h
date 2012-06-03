#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>


#define TRUE 1
#define FALSE 0
#define ERROR -1
#define ITS_FINE 0


typedef struct myArray {
	char* name;
	int row;
	int col;
	double * ar;
} myArray;




double* readFile(char* file, int * row, int * col); 


void writeFile(char * filename, myArray * result);


void printArray(int rows, int columns, double* array);

//adds matrix m1 to m2 and places the retult in m3
//m3 must have space already malloced in m3
//returns 0 on success -1 for failed
//m3 must be malloced from outside the function
int addMatrix(myArray *m1, myArray *m2, myArray *m3);

int checkCompatability(myArray* m1, myArray* m2);

#endif /*MATRIX_H*/