#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h> 
#include "Matrix.h"





double* readFile(char* file, int * row, int * col) {

	FILE * fileptr = fopen(file, "r");
	if (fileptr == NULL) {
		fprintf(stderr, "invalid file: %s\n", file);
	}

	int columns = 0;
	int rows = 0;
	
	char * buff = NULL;
	size_t size;
	while (0 <= getline(&buff, &size, fileptr)) {
		if (rows == 0) {
			int i;
			for (i = 0; buff[i] != '\n'; ++i) {
				if (buff[i] == ' ')
					++columns;
			}
			++columns;
		}
		++rows;
	}
	if (buff) {
		free(buff);
	}

	if (0 != fseek(fileptr, 0, SEEK_SET)) {
		perror("fseek:\n");
		exit(errno);
	}

	//printf("allocating buf with size: %d (%d * %d * %d)\n", rows * columns * sizeof(double), rows, columns, sizeof(double)); 
	double * buf = (double * ) malloc(rows * columns * sizeof(double));
	if (buf == NULL) 
		fprintf(stderr, "Error allocating space\n");

	int i, j;
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < columns; ++j) {
			fscanf(fileptr, "%lf ", &buf[i * columns  + j]);
		}
	}

	//printf("reading input file completed\n");
	if (0 != fclose(fileptr)) {
		perror("Error closing\n");
		exit(-1);
	}

	*row = rows;
	*col = columns;
	return buf;
}


void writeFile(char * filename, myArray * result) {
	FILE * file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error creating result file: %s\n", filename);
	}

	int i, j;
	int rows = result->row;
	int cols = result->col;
  	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			fprintf(file, "%.f ", result->ar[i * cols + j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

//
void printArray(int rows, int cols, double* array) {
	int i; //row index, ros is total number of rows
	int j; //col idex, cols is the total number of cols
	

	// for (col = 0; col < cols; ++col) {
	// 	for (row = 0; row < rows; ++row) {
	// 		printf("%.02f ", array[col * cols + row]);
	// 	}
	// 	printf("\n");
	// }
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			printf("%.02f ", array[i * cols + j]);
		}
		printf("\n");
	}
	
}


//adds matrix m1 to m2 and places the retult in m3
//m3 must have space already malloced in m3
//returns 0 on success -1 for failed
//m3 must be malloced from outside the function
int addMatrix(myArray *m1, myArray *m2, myArray *m3){
	
	int row = m1->row;
	int col = m1->col;
	
	//checks dirmentions of original matrix
	if((m1->row != m2->row)||(m1->col != m2->col)){
		return ERROR;
	}
	
	m3->row = row;
	m3->col = col;
	
	int i;
	for(i=0; i<(row*col);i++ ){
		m3->ar[i] = m1->ar[i]+m2->ar[i];
	}
	
	return 0;
}


int checkCompatability(myArray* m1, myArray* m2){
	if((m1->row != m2->row) || (m1->col != m2->col)){ 
		printf("matrix not compatable\n");
		return ERROR;
	}
	return ITS_FINE;
}



