#include "matrix.h"
#include <string.h>

#define MAX_LINE 1024

/*
int calculator(Matrix input)
{
    Matrix input2;
    Matrix resultsMatrix;
    printf("\n1. Addition / Subtraction\n");
    printf("2. Multiplication\n");
    printf("3. Scalar Multiplication\n");
    printf("4. Scalar Exponentiation\n");
    printf("0. Exit\n");
    printf("Please select the function: ");
    int select = getint();

    switch(select)
    {
        case 1: //add and sub
            printf("Add(1) or Subtract(2)?: ");
            int choice = getint();
            while(choice != 1 && choice != 2)
            {
                printf("Invalid input!\n");
                printf("Add(1) or Subtract(2)?: ");
                choice = getint();
            }
            getMatrix(&input2);
            if(input.col != input2.col || input.row != input2.row)
            {
                printf("Error: cannot add or subtract matrices of different dimensions!");
                return 1;
            }
            printf("Matrix 1 + Matrix 2");
            printMatrix(input);
            printMatrix(input2);
            if(choice == 1)
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
                return 1;
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
                return 1;
            }
            printf("Input a positive integer exponent: ");
            int expo;
            for(expo = getint(); expo < 1; expo = getint())
                printf("Invalid exponent! Please input again.\nInput a positive integer exponent: ");
            powerMatrix(input, expo, &resultsMatrix);
            printf("The matrix raised to the power of %i is:\n", expo);
            printMatrix(resultsMatrix);
            break;
        case 0:
            printf("Exiting program");
            return 0;
        default:
            printf("Selection error\nPlease select again\n");
            return calculator(input);
    }
    return 0;
}
*/

int main(void)
{
    /*
    Matrix matrix;
    getMatrix(&matrix);
    printf("The matrix you just input is:\n");
    printMatrix(matrix);
    return calculator(matrix); */

    FILE* matrixFile = fopen("matrix.csv", "r");
    char csvHeader[MAX_LINE];
    if(matrixFile == NULL)
        return 1;
    fgets(csvHeader, MAX_LINE, matrixFile);
    if(strcmp(csvHeader, "row,col,values\n") != 0)
        return 1;
    FILE* operandFile = fopen("operand.csv", "r");
    if(operandFile == NULL)
        return 1;
    fgets(csvHeader, MAX_LINE, operandFile);
    if(strcmp(csvHeader, "row,col,values\n") != 0)
        return 1;

    FILE* outputFile;

    Matrix matrix;
    Matrix operand;
    Matrix output;

    printf("What do you want to do with the matrix?\n");
    printf("1) Add\n2) Subtract\n3) Multiply with scalar\n4) Multiply with matrix\n5) Exponentiation\n"
           "6) Read CSV\n7) Create CSV\n8) Exit\nSelection: ");
    int selection = getint();
    switch(selection)
    {
        case 1:
            printf("Addition\n");
            readMatrix(operandFile, &operand);
            outputFile = fopen("output.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                readMatrix(matrixFile, &matrix);
                if(addMatrix(matrix, operand, &output) == 0)
                {
                    writeMatrix(outputFile, output);
                    freeMatrix(&output);
                }
                freeMatrix(&matrix);
            }
            freeMatrix(&operand);
            fclose(outputFile);
            break;

        case 2:
            printf("Subtraction\n");
            readMatrix(operandFile, &operand);
            outputFile = fopen("output.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                readMatrix(matrixFile, &matrix);
                if(subMatrix(matrix, operand, &output) == 0)
                {
                    writeMatrix(outputFile, output);
                    freeMatrix(&output);
                }
                freeMatrix(&matrix);
                freeMatrix(&matrix);
            }
            freeMatrix(&operand);
            fclose(outputFile);
            break;

        case 3:
            printf("Scalar Multiplication\n");
            printf("Input scalar: ");
            float scalar = getfloat();
            outputFile = fopen("output.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                readMatrix(matrixFile, &matrix);
                scalarMatrix(matrix, scalar, &output);
                writeMatrix(outputFile, output);
                freeMatrix(&matrix);
                freeMatrix(&output);
            }
            fclose(outputFile);
            break;

        case 4:
            printf("Matrix Multiplication\n");
            readMatrix(operandFile, &operand);
            outputFile = fopen("output.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                readMatrix(matrixFile, &matrix);
                if(multiplyMatrix(matrix, operand, &output) == 0)
                {
                    writeMatrix(outputFile, output);
                    freeMatrix(&output);
                }
                freeMatrix(&matrix);
            }
            freeMatrix(&operand);
            fclose(outputFile);
            break;

        case 5:
            printf("Exponentiation\n");
            printf("Input the power(int): ");
            int power = getint();
            outputFile = fopen("output.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                readMatrix(matrixFile, &matrix);
                if(powerMatrix(matrix, power, &output) == 0)
                {
                    writeMatrix(outputFile, output);
                    freeMatrix(&output);
                }
                freeMatrix(&matrix);
                freeMatrix(&matrix);
            }
            fclose(outputFile);
            break;

        case 6:
            printf("Read Matrix csv File\n");
            printf("Input the file name: ");
            char filename[20];
            getstring(filename, 19);
            FILE* csvFile = fopen(filename, "r");
            if(csvFile == NULL)
                return 1;
            fgets(csvHeader, MAX_LINE, csvFile);
            if(strcmp(csvHeader, "row,col,values\n") != 0)
                return 1;
            while(!feof(csvFile))
            {
                readMatrix(csvFile, &matrix);
                printMatrix(matrix);
                freeMatrix(&matrix);
            }
            break;

        case 7:
            printf("Create a new matrix csv file\n");
            printf("Input the file name: ");
            char newfile[20];
            getstring(newfile, 19);
            FILE* newCsv = fopen(newfile, "w");
            fputs("row,col,values", newCsv);
            char s[2];
            while(1)
            {
                getMatrix(&matrix);
                writeMatrix(newCsv, matrix);
                select:
                    printf("Add more?(Y/N): ");
                    getstring(s, 1);
                    if(s[0] == 'Y' || s[0] == 'y')
                        continue;
                    else if(s[0] == 'N' || s[0] == 'n')
                    {
                        fclose(newCsv);
                        break;
                    }
                    else
                    {
                        printf("Bad Selection\n");
                        goto select;
                    }
            }

        case 8:
            fclose(matrixFile);
            fclose(operandFile);
            return 0;

        default:
            printf("Invalid Selection");
    }
}
