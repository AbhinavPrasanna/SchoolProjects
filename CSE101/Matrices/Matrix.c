#include"List.h"
#include "Matrix.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA4
* Matrix.c
* Matrix ADT File
*********************************************************************************/

typedef struct MatrixObj{
    List* array;
    int size;
    int nnz;
}MatrixObj;
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    if(n<=0){
        printf("Matrix Error: not valid n value\n");
        exit(EXIT_FAILURE);
    }
    Matrix matrix = malloc(sizeof(MatrixObj));
    matrix->size = n;
    matrix->array = (List*)malloc((n+1) * sizeof(List));
    for(int i = 1; i<=n;i++){
        matrix->array[i] = newList();
    }
    matrix->nnz = 0;
    return matrix;
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    /*Matrix matrix = *pM;
    for (int i = 0; i < matrix->size; i++)
    {
        List list = matrix->array[i];
        if(get(list)!=NULL){
          clear(list);
          freeList(&list);
        }
    }
    free(*pM);
    matrix = NULL;
    pM = NULL;*/
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if(M==NULL){
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if(M==NULL){
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->nnz;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A==NULL||B==NULL){
        printf("Matrix Error: calling equals on one or multiple NULL matrix objects.\n");
        exit(EXIT_FAILURE);
    }
    if(size(A)!=size(B)){
        return 0;
    }
    for(int i = 1; i<=size(A); i++){
        if(length(A->array[i])!=length(B->array[i])){
            return 0;
        }
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        while(index(A->array[i])>=0 && index(B->array[i])>=0){
             if(column(get(A->array[i]))==column(get(A->array[i]))){
                 if(data(get(A->array[i]))!=data(get(B->array[i]))){
                     return 0;
                 }
             }
             else if(column(get(A->array[i]))<column(get(B->array[i]))){
                 return 0;
             }
             else if(column(get(A->array[i]))>column(get(B->array[i]))){
                 return 0;
             }
             moveNext(A->array[i]);
             moveNext(B->array[i]);
        }
    }
    return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
   if(M==NULL){
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i=2;i<size(M);i++){
        if(M->array[i-1]!=NULL){
            clear(M->array[i-1]);
            freeList(&(M->array[i-1]));
            M->array[i-1] = newList();
        }
    }
    M->nnz = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M==NULL){
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(i<1 && i>size(M)){
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(j<1 && j>size(M)){
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for(moveFront(M->array[i]);index(M->array[i])>=0;moveNext(M->array[i])){
        if(column(get(M->array[i]))==j){
            if(data(get(M->array[i]))!=x && x!=0){
                set(M->array[i],newEntry(j,x));
                return;
            }
            if(x==0){
                delete(M->array[i]);
                M->nnz--;
                return;
            }
            if(data(get(M->array[i]))==x){
                return;
            }
        }
        if(column(get(M->array[i]))>j && x!=0){
            insertBefore(M->array[i],newEntry(j,x));
            M->nnz++;
            return;
        }
    }
    if(x!=0){
        append(M->array[i],newEntry(j,x));
        M->nnz++;
    }
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A==NULL){
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix matrix = newMatrix(size(A));
    for(int i = 1; i<=size(A);i++){
        for(moveFront(A->array[i]);index(A->array[i])>=0;moveNext(A->array[i])){
            append(matrix->array[i],get(A->array[i])); 
            matrix->nnz++;       
        }
    }
    return matrix;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    Matrix matrix = newMatrix(size(A));
    if(A==NULL){
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i<=size(A);i++){
        for(moveFront(A->array[i]);index(A->array[i])>=0;moveNext(A->array[i])){
            append(matrix->array[(int)column(get(A->array[i]))],newEntry(i,data(get(A->array[i]))));
            matrix->nnz++;        
        }
    }
    return matrix;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    Matrix matrix = newMatrix(size(A));
    for(int i = 1; i<=size(A);i++){
        moveFront(A->array[i]);
               while(index(A->array[i])>=0){
                  append(matrix->array[i],newEntry(column(get(A->array[i])),x * data(get(A->array[i]))));
                  matrix->nnz++; 
                  moveNext(A->array[i]);
               }
        }
    return matrix;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)

void add(List A, List B, Matrix matrix,int i){
    if(A==NULL||B==NULL){
        printf("Matrix Error: calling add() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(A)==-1 && index(B)==-1){
        return;
    }
    if(index(A)==-1){
        changeEntry(matrix,i,column(get(B)),data(get(B)));
        moveNext(B);
    }
    else if(index(B)==-1){
        changeEntry(matrix,i,column(get(A)),data(get(A)));
        moveNext(A);
    }
    else if(column(get(A))>column(get(B))){
        changeEntry(matrix,i,column(get(B)),data(get(B)));
        moveNext(B);
    }
    else if(column(get(A))<column(get(B))){
        changeEntry(matrix,i,column(get(A)),data(get(A)));
        moveNext(A);
    }
    else{
        changeEntry(matrix,i,column(get(A)),data(get(A))+data(get(B)));
        moveNext(A);
        moveNext(B);
    }
    add(A,B,matrix,i);
}
Matrix sum(Matrix A, Matrix B){
    Matrix matrix = newMatrix(size(A));
    if(A==NULL||B==NULL){
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A)!=size(B)){
        printf("Matrix Error: calling sum() on nonequal sizes\n");
        exit(EXIT_FAILURE);
    }
    if(equals(A,B)){
        return scalarMult(2,A);
    }
    for(int i = 1; i<=size(A);i++){
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        add(A->array[i],B->array[i],matrix,i);
    }       
    return matrix;
}
void sub(List A, List B, Matrix matrix,int i){
    if(A==NULL||B==NULL){
        printf("Matrix Error: calling add() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(A)==-1 && index(B)==-1){
        return;
    }
    if(index(A)==-1){
        changeEntry(matrix,i,column(get(B)),data(get(B))*-1.0);
        moveNext(B);
    }
    else if(index(B)==-1){
        changeEntry(matrix,i,column(get(A)),data(get(A))*-1.0);
        moveNext(A);
    }
    else if(column(get(A))>column(get(B))){
        changeEntry(matrix,i,column(get(B)),data(get(B))*-1.0);
        moveNext(B);
    }
    else if(column(get(A))<column(get(B))){
        changeEntry(matrix,i,column(get(A)),data(get(A))*-1.0);
        moveNext(A);
    }
    else{
        changeEntry(matrix,i,column(get(A)),data(get(A))-data(get(B)));
        moveNext(A);
        moveNext(B);
    }
    sub(A,B,matrix,i);
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){ 
    Matrix matrix = newMatrix(size(A));
    if(A==NULL||B==NULL){
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A)!=size(B)){
        printf("SIZE!\n");
        printf("Matrix Error: calling sum() on nonequal sizes\n");
        exit(EXIT_FAILURE);
    }
    if(A==B){
        return newMatrix(size(A));
    }
    for(int j = 1; j<=size(A);j++){
        moveFront(A->array[j]);
        moveFront(B->array[j]);
        sub(A->array[j],B->array[j],matrix,j);
    }      
    return matrix;
}

double dotProduct(List A, List B){
    double total = 0.0;
     if(A==NULL||B==NULL){
         printf(" return 0.0\n");
         return 0.0;
     }
     moveFront(A);
     moveFront(B);
     while(index(A)>=0 && index(B)>=0){
         if(column(get(A))==column(get(B))){
             total += data(get(A)) * data(get(B));
             moveNext(B);
             moveNext(A);
         }
         else if(column(get(A))>column(get(B))){
             moveNext(B);
         }
         else{
             moveNext(A);
         }
     }
     return total;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
         printf("Error in product unction. A or B are NULL\n");
         exit(EXIT_FAILURE);
    }
    if(A==B){
        B = copy(A);
    }
    Matrix newB = transpose(B);
    Matrix matrix = newMatrix(size(A));
    for(int i = 1; i<=size(A);i++){
        if(length(A->array[i])!=0){
            for(int j=1; j<=size(newB);j++){
                if(length(newB->array[j])!=0){
                    double y = dotProduct(A->array[i],B->array[j]);
                    changeEntry(matrix,i,j,y);
                }
            }
        }
    }
    return matrix;
}

//Matrix dotProduct(List A, List B, List list,  )
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if(M==NULL){
        fprintf(out," ");
    }
    for(int i = 0; i<size(M);i++){
        if(M->array[i]!=NULL && length(M->array[i])>0){
           fprintf(out,"%d: ",i);
           printList(out,M->array[i]);
        }
    }
}
