#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdbool.h>

/*!
 * Matrix c-structure
 */
typedef struct Matrix
{
    int row;
    int col;
    float** index;
}Matrix;

/*!
 * this function asks user for input and parse it into a float variable
 * @return A float variable parsed from the input
 */
float getfloat(void);

/*!
 * this function asks user for input and parse it into an int variable
 * @return An int variable parsed from the input
 */
int getint(void);

/*!
 * this function asks user for input and parse it into an int variable
 * @param string destination array to store the string
 * @param len maximum length EXCLUDING the '/0' character at the end.
 * @return A int variable parsed from the input
 */
void getstring(char* string, int len);

/*!
 * This function allocate appropriate memory to the matrix by using malloc()
 * @param matrix_ptr pointer to the matrix to allocate memory
 * @param row number of rows of the matrix to allocate memory
 * @param col number of columns of the matrix to allocate memory
 */
void iniMatrix(Matrix* matrix_ptr, int row, int col);

/*!
 * This function free the allocated memory by the function iniMatrix by using free()
 * @param matrix_ptr pointer to the matrix_ptr to free allocated memory
 * @param row number of rows
 * @param col number of columns
 */
void freeMatrix(Matrix* matrix_ptr);

/*!
 * This function is used in combination with iniMatrix to see if memory is allocated properly
 * This function is intended for internal uses only
 * @param matrix matrix to check
 * @return enum Bool True if matrix is initialised successfully
 * @return enum Bool False if matrix initialisation failed
 * @see iniMatrix()
 */
_Bool checkMatrix(Matrix matrix);

/*!
 * This function asks for input from user to create a Matrix struct
 * @param matrix_ptr pointer to the matrix variable which will be used to store the newly created matrix
 */
void getMatrix(Matrix* matrix_ptr);

/*!
 * This function print the matrix struct to the console in an easily readable fashion
 * @param matrix matrix to print out to the console
 */
void printMatrix(Matrix matrix);

/*!
 * A function to add two matrices together.
 * [base1 + base2 = results]
 *
 * @param base1 matrix to add to
 * @param base2 matrix to add
 * @param results_ptr pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * @return 0 if function operates normally
 * @return 1 if matrices are incompatible
 * @see iniMatrix()
 */
int addMatrix(Matrix base1, Matrix base2, Matrix* results_ptr);

/*!
 * A function to subtract matrices.
 * [base1 - base2 = results]
 *
 * @param base1 matrix to subtract from
 * @param base2 operand matrix
 * @param results_ptr pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * @return 0 if function operates normally
 * @return 1 if matrices are incompatible
 * @see iniMatrix()
 */
int subMatrix(Matrix base1, Matrix base2, Matrix* results_ptr);

/*!
 * A function to create a new identical matrix (on a new memory space)
 * @param from_matrix matrix to be copied
 * @param to_ptr pointer which will hold the copied matrix. iniMatrix() is used to allocate memory.
 * @see iniMatrix()
 */
void copyMatrix(Matrix from_matrix, Matrix* to_ptr);

/*!
 * A function to multiply a matrix by another matrix.
 * [base x multiply = results]
 * @param base a matrix to multiply
 * @param multiply operand matrix
 * @param results_ptr pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * if matrices are incompatible results_ptr will be set to NULL.
 * @see iniMatrix()
 * @return 0 if function operates normally
 * @return 1 if matrices are incompatible
 */
int multiplyMatrix(Matrix base, Matrix multiply, Matrix* results_ptr);

/*!
 * A function to multiply a matrix by a number(scalar)
 * [scalar * base = results]
 *
 * @param base matrix to be multiplied
 * @param scalar a real number by which the matrix will be multiplied
 * @param results_ptr pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * @see iniMatrix()
 */
void scalarMatrix(Matrix base, float scalar, Matrix* results_ptr);

/*!
 * A function to raise matrix to the n-th power.
 * @param base the base matrix
 * @param exponent power. Negative integers will be converted to a positive integer.
 * @param results_ptr pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * @return 0 if function operates normally
 * @return 1 if matrix is not a square matrix
 */
int powerMatrix(Matrix base, int exponent, Matrix* results_ptr);

/*!
 * A function to read a matrix from a line in csv file.
 * @param csv File pointer to a csv file. File pointer will be moved forward by one line.
 * @param matrix_ptr Pointer to the matrix which will contain the results. iniMatrix() is used to allocate memory.
 * If the read fails results_ptr will be set to NULL and no memory will be allocated.
 * @see iniMatrix()
 * @see freeMatrix()
 */
int readMatrix(FILE* csv, Matrix* matrix_ptr);

/*!
 * A function to write a matrix to a csv file.
 * @param csv File pointer to a csv file. File pointer will be moved forward by one line.
 * @param matrix matrix which will be written to a csv file.
 * @return 0 if matrix is read successfully
 * @return 1 if matrix cannot be read (dimension - value mismatch, etc.)
 */
void writeMatrix(FILE* csv, Matrix matrix);

_Bool checkSquare(Matrix base);

int transposeMatrix(Matrix base, Matrix* results_ptr);

float determinantMatrix(Matrix base);

int minor(Matrix base, int row, int col, Matrix* results_ptr);

float cofactor(Matrix base, int row, int col);

int cofactorMatrix(Matrix base, Matrix* results_ptr);

int adjugateMatrix(Matrix base, Matrix* results_ptr);

int inverseMatrix(Matrix base, Matrix* results_ptr);
#endif // MATRIX_H
