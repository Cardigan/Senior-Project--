#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "Matrix.h"
#include "targeting.h"
#include <math.h>

void rtndeflection(double x, double y, double* deflection){
	*deflection = atan(x/y);
	return;
}


int CreateMatrix(double mean, double std, char* filename){
	pid_t pid;
	int status;
	char amean[30];
	char astd[30];
	
	strcpy(amean, itoa(mean, 10));
	strcpy(astd, itoa(std,10));
	
	/* Fork a child */
	if ((pid = fork()) < 0)
	{
		perror("Fork error!");
	}
	else if (pid == 0) /* In the child */
	{
		//useage <exec> rows columns range filename mean <standard deviation>
		// example ./genMat.out 32 1 10 test.data 50 10
		if (execlp("./genMat.out", "./genMat.out", INTROW, INTCOL, INTRANGE, filename, amean, astd, (char *)0) < 0){
			perror("Exec error!");
			exit(-1);
		}
	}
	waitpid(pid, &status, 0);
	return 0;
}

//simple itoa function borrowed from the web
//Below is an early version described by Robert Jan Schaper on Google groups:
char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}


//Fills matrix z with arctan of x/y
void Defection(myArray *x, myArray *y, myArray * z)						{

	int limit = x->row * x->col;
	int i;


	for(i=0; i<limit; i++){
		z->ar[i]= atan(x->ar[i] / y->ar[i]);

		//debug prints
		if(i<10){
			printf("i=%d, x=%.4f, y=%.4f, ratio=%.4f, atan=%.4f\n", 
				i, x->ar[i],
				y->ar[i],
				(x->ar[i] / y->ar[i]),
				atan(x->ar[i] / y->ar[i]));
		}
		//end debug

	}	
}


void elevation(myArray* matX, myArray* matY, myArray* matH,  myArray* matV, myArray* matE){
	double d, h, v, e;
	int i;
	int limit = matX->row * matX->col;
	
	for(i=0;i<limit;i++){
		d = sqrt(( (matX->ar[i]) * matX->ar[i]) + (matY->ar[i] * matY->ar[i]));
		h = matH->ar[i];
		v = matV->ar[i];
		
		//debug this is a placeholder equation until the actual physics is done
		e = d+h+v;
		
		if(i<5){
			printf("i= %d, d=%.4f, h= %.4f, v= %.4f,e= %.4f\n", i, d ,h ,v, e);
		}
		
		matE->ar[i] = e;
	}
	
}


