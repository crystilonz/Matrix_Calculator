#include "functions.c"

void calculator(Matrix input)
{
    Matrix resultsMatrix;
    printf("\nCalculator Functions: \n");
    printf("1. Transpose\n");
    printf("2. Determinant\n");
    printf("3. Addition / Subtraction\n");
    printf("4. Multiplication\n");
    printf("5. Cofactor Matrix\n");
    printf("6. Adjunct Matrix\n");
    printf("7. Inverse Matrix\n");
    printf("8. Scalar Exponentiation\n");
    printf("9. Exit\n");
    printf("Please select the function: ");
    int select = getint();

    switch(select)
    {
        case 1:
            transpose(input, resultsMatrix);
            printf("The tranposed matrix is:\n");
            break;
        case 9:
            printf("Exiting program");
            exit(0);
        default:
            printf("Selection error\n");
            calculator(input);
    }
    printMatrix(resultsMatrix);
}

int main(void)
{
    Matrix matrix;
    getMatrix(matrix);
    printf("The matrix you just input is: \n");
    printMatrix(matrix);

    calculator(matrix);
}