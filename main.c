#include "functions.c"

void calculator(Matrix input)
{
    Matrix input2;
    Matrix resultsMatrix;
    printf("\n1. Addition / Subtraction\n");
    printf("2. Multiplication\n");
    printf("3. Scalar Multiplication\n");
    printf("4. Scalar Exponentiation\n");
    printf("9. Exit\n");
    printf("Please select the function: ");
    int select = getint();

    switch(select)
    {
        case 1: //add and sub
            printf("Add(1) or Subtract(2)?: ");
            int addsub = getint();
            while(addsub != 1 && addsub != 2)
            {
                printf("Invalid input!\n");
                printf("Add(1) or Subtract(2)?: ");
                addsub = getint();
            }
            getMatrix(&input2);
            if(input.col != input2.col || input.row != input2.row)
            {
                printf("Error: cannot add or subtract matrices of different dimensions!");
                break;
            }
            printf("Matrix 1 + Matrix 2");
            printMatrix(input);
            printMatrix(input2);
            if(addsub == 1)
                addMatrix(input, input2, &resultsMatrix);
            else
                subMatrix(input, input2, &resultsMatrix);
            printf("The result matrix is:\n");
            printMatrix(resultsMatrix);
            break;
        case 2: // multiplication
            printf("Input the matrix you want to multiply with:\n" );
            getMatrix(&input2);
            if(input.col != input2.row)
            {
                printf("Incompatible matrix! Cannot multiply %ix%i matrix with %ix%i matrix!",
                       input.row, input.col, input2.row, input2.col);
                break;
            }
            printf("Matrix 1 x Matrix 2");
            printMatrix(input);
            printMatrix(input2);
            multiplyMatrix(input, input2, &resultsMatrix);
            printf("The result of multiplication is:\n");
            printMatrix(resultsMatrix);
            break;
        case 3: // scalar multiplication
            printf("Input a number to multiply the matrix with: ");
            float scalar = getfloat();
            scalarMatrix(input, scalar, &resultsMatrix);
            printf("The matrix times %.2f\n", scalar);
            printMatrix(input);
            printf("equals\n");
            printMatrix(resultsMatrix);
            break;
        case 4: // scalar expo
            if(input.row != input.col)
            {
                printf("Matrix must be a square matrix!\n");
                break;
            }
            printf("Input a positive integer exponent: ");
            int expo;
            for(expo = getint(); expo < 1; expo = getint())
                printf("Invalid exponent! Please input again.\nInput a positive integer exponent: ");
            powerMatrix(input, expo, &resultsMatrix);
            printf("The matrix raised to the power of %i is:\n", expo);
            printMatrix(resultsMatrix);
            break;
        case 9:
            printf("Exiting program");
            exit(0);
        default:
            printf("Selection error\nPlease select again\n");
            calculator(input);
    }
}

int main(void)
{
    Matrix matrix;
    getMatrix(&matrix);
    printf("The matrix you just input is:\n");
    printMatrix(matrix);
    calculator(matrix);
}