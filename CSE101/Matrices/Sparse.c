#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Matrix.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA4
* Sparse.c
* Sparse Main Method File
*********************************************************************************/

FILE* infile;
FILE* outfile;
int line[255];

int main(int argc, char* argv[]){
    if(argc == 3){
        infile = fopen(argv[1],"r");
        outfile = fopen(argv[2],"w+");
        if(infile == NULL){
             fprintf(stderr,"Error: failed to open infile.\n");
             return -1;
        }
        if(outfile == NULL){
             fprintf(stderr,"Error opening file to write\n");
             return -1;
        }
    }
    else{
         fprintf(stderr,"Error: enter correct number of arguments.\n");
         return -1;
    } 
    int n,nnza,nnzb;
    int x,y;
    double enter;
    fscanf(infile,"%d %d %d",&n,&nnza,&nnzb);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    for(int i = 0;i<nnza;i++){
        fscanf(infile,"%d %d %lf\n",&x,&y,&enter);
        changeEntry(A,x,y,enter);
    }
    for(int j = 0; j<nnzb;j++){
        fscanf(infile,"%d %d %lf\n",&x,&y,&enter);
        changeEntry(B,x,y,enter);
    }
    fprintf(outfile, "A has %d non-zero entries: \n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");
    fprintf(outfile, "B has %d non zero-entries: \n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");
    Matrix scalar = scalarMult(1.5, A);
    fprintf(outfile, "(1.5)*A = \n");
    printMatrix(outfile, scalar);
    fprintf(outfile, "\n");
    Matrix sum1 = sum(A, B);
    fprintf(outfile, "A+B = \n");
    printMatrix(outfile, sum1);
    fprintf(outfile, "\n");
    Matrix sum2 = sum(A, A);
    fprintf(outfile, "A+A = \n");
    printMatrix(outfile, sum2);
    fprintf(outfile, "\n");
    Matrix difference = diff(B, A);
    fprintf(outfile, "B-A =\n");
    printMatrix(outfile, difference);
    fprintf(outfile, "\n");
    Matrix difference2 = diff(A, A);
    fprintf(outfile, "A-A =\n");
    printMatrix(outfile, difference2);
    fprintf(outfile, "\n");
    Matrix trans = transpose(A);
    fprintf(outfile, "Transpose(A) =\n");
    printMatrix(outfile, trans);
    fprintf(outfile, "\n");
    Matrix prod = product(A, B);
    fprintf(outfile, "A*B =\n");
    printMatrix(outfile, prod);
    fprintf(outfile, "\n");
    Matrix prod2 = product(B, B);
    fprintf(outfile, "B*B =\n");
    printMatrix(outfile, prod2);
    fprintf(outfile, "\n");
    freeMatrix(&scalar);
    freeMatrix(&sum1);
    freeMatrix(&sum2);
    freeMatrix(&difference);
    freeMatrix(&difference2);
    freeMatrix(&trans);
    freeMatrix(&prod);
    freeMatrix(&prod2);
    fclose(infile);
    fclose(outfile);
    return 0;
}
