#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define dprintf(expr) printf(#expr " = %f, ", expr)
#define dprints(expr) printf(#expr " = %s\n", expr)
#define PI 3.14159 
#define NSUM 25




// This gaussian exploit the Central Limit Theorem (``law of large numbers'') 
// and add up several uniformly-distributed random numbers:
// modified from http://c-faq.com/lib/gaussian.html
double gaussian(double mean, double stddev)	{
		sranddev();
	
		double x = 0;
		int i;
		for(i = 0; i < NSUM; i++)
			x += (double)rand() / RAND_MAX;

		x -= NSUM / 2.0;
		x /= sqrt(NSUM / 12.0);
		x *= stddev;
		x += mean;
		return x;
	}


void fillMatRandom(float ** mat, int rows, int cols, float range, double mean, double stdv){
	srandom(time(NULL));
	int i, j;
	float debugrand, debuggaus;
	for(i = 0; i < rows; ++i){
		for(j = 0;j < cols; ++j){
			(*mat)[i * cols + j] = gaussian(mean,stdv);//gaussian(200,10, (((float)random()/RAND_MAX) * range));
		}
	}
}



void writeFile(char * filename, float * result, int rows, int cols) {
	FILE * file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error creating result file: %s\n", filename);
	}

	int i, j;
  	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			// for use when generating input files
			fprintf(file, "%.2f", result[i * cols + j]);
			if (j != cols - 1) 
			   fprintf(file, " ");
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

int main(int argc, char ** argv) {

	if (argc != 7) {
		fprintf(stderr, "Usage error: <exec> rows columns range filename mean <standard deviation>\n");
		exit(-1);
	}
	
	//debug statment
	// int i;
	// for(i=0;i<7;i++)
	// 	dprints(argv[i]);
	
	
	double mean = atoi(argv[5]);
	double stdv = atoi(argv[6]);
	
	dprintf(mean);
	dprintf(stdv);
	

	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);
	int range = atoi(argv[3]);

	float * mat = malloc(rows * cols * sizeof(float));
	fillMatRandom(&mat, rows, cols, range, mean, stdv);
	writeFile(argv[4], mat, rows, cols);
	free(mat);
	return 0;
}
