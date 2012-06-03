#include <stdio.h>
#include <stdlib.h>
#include "targeting.h"
#include "Matrix.h"

int main(int argc, char* argv[]){


	//Debug place holder for input data creating  
	CreateMatrix(50, 10, "v.data");	
	
	
	//debug add input data form here
	CreateMatrix(50, 10, "x.data");
	CreateMatrix(50, 10, "y.data");	
	CreateMatrix(50, 10, "h.data");
	



	myArray MatX;
	MatX.name = "Matrix X coordinate of target";
	MatX.ar = readFile("x.data", &(MatX.row), &(MatX.col));

	myArray MatY;
	MatY.name = "Matrix Y coordinate of target";
	MatY.ar = readFile("y.data", &(MatY.row), &(MatY.col));
	
	myArray MatH;
	MatH.name = "Matrix with relative height coordinate of target";
	MatH.ar = readFile("h.data", &(MatH.row), &(MatH.col));
	
	myArray MatV;
	MatV.name = "Matrix with relative height coordinate of target";
	MatV.ar = readFile("v.data", &(MatV.row), &(MatV.col));

	myArray MatDefec;
	MatDefec.name = "defection to target";
	MatDefec.row = MatY.row;
	MatDefec.col = MatY.col;
	MatDefec.ar = malloc(sizeof(double)*(MatY.row * MatY.col));
	
	myArray MatElev;
	MatElev.name = "Elevation to target";
	MatElev.row = MatY.row;
	MatElev.col = MatY.col;
	MatElev.ar = malloc(sizeof(double)*(MatY.row * MatY.col));

	
	printf("-----------------------------------------------\n");
	
	printf("Oringinal X and Y\n-----------------------------------------------\n");
	printf("XXXX printing original matrixX ");
	printArray(MatX.row, MatX.col, MatX.ar);
	
	printf("YYYYYprinting original matrixY ");
	printArray(MatY.row, MatY.col, MatY.ar);
	
	printf("\n-----------------------------------------------\n");
	printf("-----------------------------------------------\n");
	

	printf("printing original matrix Defelction to target\n");	
	printArray(MatDefec.row, MatDefec.col, MatDefec.ar);
	
	printf("performing the operation\n");
	Defection(&MatX, &MatY, &MatDefec);
 	// Defection2(MatX.ar, MatY.ar, MatDefec.ar, MatX.row * MatY.col);
	
	printf("-----------------------------------------------\n");
	
	printf("printing original matrix Defelction to target\n");	
	printArray(MatDefec.row, MatDefec.col, MatDefec.ar);
	
	printf("-----------------------------------------------\n");
	printf("-----------------------------------------------\n");
	printf("printing elevation to target\n");	
	
	elevation(&MatX, &MatY, &MatH,  &MatV, &MatElev);

	printArray(MatElev.row, MatElev.col, MatElev.ar);
	
	



	//Thou shalt free all that thy malloc
	free(MatDefec.ar);
	free(MatY.ar);
	free(MatX.ar);
	free(MatH.ar);
	free(MatElev.ar);
	free(MatV.ar);
	return 0;
}



