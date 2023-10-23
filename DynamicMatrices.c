//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//-----------------------------------------------------------------------------
double* input_matrix(int*, int*, char[]);
bool matrix_multiply(double*, int, int, double*, int, int, double*);
void output_matrix(double*, int, int);
//-----------------------------------------------------------------------------
int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
    
}
//-----------------------------------------------------------------------------
double* input_matrix(int* rows, int* columns, char name[]){

    double* m;
    int i, j, index;
    index = 0;
  
    // Prompt user for dimensions
    printf("Enter the number of rows for %s:    ", name);
    scanf("%d", rows);
    printf("Enter the number of columns for %s: ", name);
    scanf("%d", columns);
  
    // Dynamically allocate memory from the heap
    m = (double*)malloc(*rows * *columns * sizeof(double));
    
    // Read the values into the memory using row major ordering
    for (i = 1; i < *rows + 1; i++){
        for (j  = 1; j < *columns + 1; j++){
	    printf("Enter the value for [%d, %d]: ", i, j);
	    scanf("%lf", &m[index]);
	    index++;
        }
    }
    
    return m;
}
//-----------------------------------------------------------------------------
bool matrix_multiply(double* m1, int m1_rows, int m1_columns, double* m2,
		     int m2_rows, int m2_columns, double* m3){

    // Check if dimensions are appropriate
    if (m1_columns != m2_rows)
        return false;

    // Define variables
    int i, j, k, index;
    index = 0;
    
    // Multiply the two matrices together
    for (i = 0; i < m1_rows; i++){
        for (j = 0; j < m2_columns; j++) {
	    m3[index] = 0;
	    for (k = 0; k < m1_columns; k++){
	        m3[index] += m1[i * m1_columns + k] * m2[k * m2_columns + j];
	    }
	    index++;
	}
    }

    return true;
}
//-----------------------------------------------------------------------------
void output_matrix(double* m, int rows, int columns){

    int i, j, index;
    index = 0;

    // Print matrix 
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++) {
	    printf("%f ", m[index]);
	    index++;
	}
	printf("\n");
    }
  
}
//-----------------------------------------------------------------------------
