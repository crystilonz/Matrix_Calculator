#include "matrix.h"
#include <string.h>

#define MAX_LINE 1024
#define MAX_FILE_LENGTH 30


void calculator(Matrix input)
{
    Matrix input2;
    Matrix resultsMatrix;
    while(1)
    {
        printf("\n1) Addition / Subtraction\n");
        printf("2) Multiplication\n");
        printf("3) Scalar Multiplication\n");
        printf("4) Scalar Exponentiation\n");
        printf("5) Determinant\n");
        printf("6) Cofactor Matrix\n");
        printf("7) Adjugate Matrix\n");
        printf("8) Inverse Matrix\n");
        printf("9) Transpose Matrix\n");
        printf("0. Return to main menu\n");
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
                    printf("Error: cannot add or subtract matrices of different dimensions!\n");
                    break;
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
                freeMatrix(&resultsMatrix);
                break;

            case 2: // multiplication
                printf("Input the matrix you want to multiply with:\n" );
                getMatrix(&input2);
                if(input.col != input2.row)
                {
                    printf("Incompatible matrix! Cannot multiply %ix%i matrix with %ix%i matrix!\n",
                           input.row, input.col, input2.row, input2.col);
                    break;
                }
                printf("Matrix 1 x Matrix 2");
                printMatrix(input);
                printMatrix(input2);
                multiplyMatrix(input, input2, &resultsMatrix);
                printf("The result of multiplication is:\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
                break;

            case 3: // scalar multiplication
                printf("Input a number to multiply the matrix with: ");
                float scalar = getfloat();
                scalarMatrix(input, scalar, &resultsMatrix);
                printf("The matrix times %.2f\n", scalar);
                printMatrix(input);
                printf("equals\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
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
                freeMatrix(&resultsMatrix);
                break;

            case 5: // Determinant
                if(input.row != input.col)
                {
                    printf("Matrix must be a square matrix!\n");
                    break;
                }
                float det = determinantMatrix(input);
                printf("The determinant of the matrix is %f\n", det);
                break;

            case 6:  // Cofactor Matrix
                if(input.row != input.col)
                {
                    printf("Matrix must be a square matrix!\n");
                    break;
                }
                if(input.row < 2)
                {
                    printf("Matrix is too small\n");
                    break;
                }
                cofactorMatrix(input, &resultsMatrix);
                printf("The cofactor matrix is:\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
                break;

            case 7:  // Adjugate Matrix
                if(input.row != input.col)
                {
                    printf("Matrix must be a square matrix!\n");
                    break;
                }
                adjugateMatrix(input, &resultsMatrix);
                printf("The adjugate matrix is:\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
                break;

            case 8:  // Inverse Matrix
                if(input.row != input.col)
                {
                    printf("Matrix must be a square matrix!\n");
                    break;
                }
                if(determinantMatrix(input) == 0)
                {
                    printf("Matrix is a singular matrix.\n");
                    break;
                }
                inverseMatrix(input, &resultsMatrix);
                printf("The inverse matrix is:\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
                break;

            case 9:  // Transpose
                transposeMatrix(input, &resultsMatrix);
                printf("The tranpose matrix is:\n");
                printMatrix(resultsMatrix);
                freeMatrix(&resultsMatrix);
                break;

            case 0:
                printf("Returning to main menu\n");
                return;

            default:
                printf("Selection error\nPlease select again\n");
                break;
        }
    }
}


void csv_matrix(void)
{
    char file_name[MAX_FILE_LENGTH + 1];
    printf("Input the matrix CSV file name: ");
    getstring(file_name, MAX_FILE_LENGTH);
    FILE* matrixFile = fopen(file_name, "r");
    char csvHeader[MAX_LINE];
    if(matrixFile == NULL)
    {
        printf("Cannot open file. Returning to main menu\n");
        fclose(matrixFile);
        return;
    }
    fgets(csvHeader, MAX_LINE, matrixFile);
    if(strcmp(csvHeader, "row,col,values\n") != 0)
    {
        printf("CSV file header is missing and/or not a matrix csv file. Returning to main menu.\n");
        fclose(matrixFile);
        return;
    }

    FILE* outputFile;
    FILE* operandFile;
    Matrix matrix;
    Matrix operand;
    Matrix output;
    printf("What do you want to do with the matrix?\n");
    printf("1) Add\n");
    printf("2) Subtract\n");
    printf("3) Multiply with scalar\n");
    printf("4) Multiply with matrix\n");
    printf("5) Exponentiation\n");
    printf("6) Determinant\n");
    printf("7) Cofactor Matrix\n");
    printf("8) Adjugate Matrix\n");
    printf("9) Inverse Matrix\n");
    printf("10) Transpose Matrix\n");
    printf("0) Exit\nSelection: ");
    int selection = getint();
    switch(selection)
    {
        case 1:
            printf("Addition\n");
            printf("Input the operand CSV file name: ");
            getstring(file_name, MAX_FILE_LENGTH);
            operandFile = fopen(file_name, "r");
            if(operandFile == NULL)
            {
                printf("Cannot open file\n");
                fclose(operandFile);
                break;
            }
            fgets(csvHeader, MAX_LINE, operandFile);
            if(strcmp(csvHeader, "row,col,values\n") != 0)
            {
                printf("CSV file header is missing and/or not a matrix csv file.\n");
                fclose(operandFile);
                break;
            }
            if(readMatrix(operandFile, &operand) != 0)
            {
                printf("Failed to read the operand matrix.\n");
                fclose(operandFile);
                break;
            }
            outputFile = fopen("add.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)  // matrix is read successfully
                {
                    if(addMatrix(matrix, operand, &output) == 0)  // addition is performed successfully
                    {
                        writeMatrix(outputFile, output);  // write to output file
                        freeMatrix(&output);
                    }
                    else  // cannot perform addition
                    {
                        fprintf(outputFile, "\nFailed to add matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            freeMatrix(&operand);
            fclose(operandFile);
            fclose(outputFile);
            break;

        case 2:
            printf("Subtraction\n");
            printf("Input the operand CSV file name: ");
            getstring(file_name, MAX_FILE_LENGTH);
            operandFile = fopen(file_name, "r");
            if(operandFile == NULL)
            {
                printf("Cannot open file\n");
                fclose(operandFile);
                break;
            }
            fgets(csvHeader, MAX_LINE, operandFile);
            if(strcmp(csvHeader, "row,col,values\n") != 0)
            {
                printf("CSV file header is missing and/or not a matrix csv file.\n");
                fclose(operandFile);
                break;
            }
            if(readMatrix(operandFile, &operand) != 0)
            {
                printf("Failed to read the operand matrix.\n");
                fclose(operandFile);
                break;
            }
            outputFile = fopen("subtract.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if(subMatrix(matrix, operand, &output) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else
                    {
                        fprintf(outputFile, "\nFailed to subtract matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            freeMatrix(&operand);
            fclose(operandFile);
            fclose(outputFile);
            break;

        case 3:
            printf("Scalar Multiplication\n");
            printf("Input scalar: ");
            float scalar = getfloat();
            outputFile = fopen("s_multply.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    scalarMatrix(matrix, scalar, &output);
                    writeMatrix(outputFile, output);
                    freeMatrix(&matrix);
                    freeMatrix(&output);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 4:
            printf("Matrix Multiplication\n");
            printf("Input the operand CSV file name: ");
            getstring(file_name, MAX_FILE_LENGTH);
            operandFile = fopen(file_name, "r");
            if(operandFile == NULL)
            {
                printf("Cannot open file\n");
                fclose(operandFile);
                break;
            }
            fgets(csvHeader, MAX_LINE, operandFile);
            if(strcmp(csvHeader, "row,col,values\n") != 0)
            {
                printf("CSV file header is missing and/or not a matrix csv file.\n");
                fclose(operandFile);
                break;
            }
            if(readMatrix(operandFile, &operand) != 0)
            {
                printf("Failed to read the operand matrix.\n");
                fclose(operandFile);
                break;
            }
            outputFile = fopen("multiply.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {

                    if(multiplyMatrix(matrix, operand, &output) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else
                    {
                        fprintf(outputFile, "\nFailed to multiply matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            freeMatrix(&operand);
            fclose(operandFile);
            fclose(outputFile);
            break;

        case 5:
            printf("Exponentiation\n");
            printf("Input the power(int): ");
            int power = getint();
            outputFile = fopen("expo.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if(powerMatrix(matrix, power, &output) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else
                    {
                        fprintf(outputFile, "\nNon-square matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 6:
            printf("Determinant\n");
            outputFile = fopen("det.csv", "w");
            fputs("Determinant", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if(checkSquare(matrix))
                        fprintf(outputFile, "\n%f", determinantMatrix(matrix));
                    else
                        fprintf(outputFile, "\nNon-square matrix");
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 7:
            printf("Cofactor\n");
            outputFile = fopen("cofactor.csv", "w");
            fputs("row,col,values", outputFile);
            int func;
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if((func = cofactorMatrix(matrix, &output)) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else if(func == 1)
                    {
                        fprintf(outputFile, "\nNon-square matrix");
                    }
                    else if(func == 2)
                    {
                        fprintf(outputFile, "\nMatrix too small");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 8:
            printf("Adjugate\n");
            outputFile = fopen("adj.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if(adjugateMatrix(matrix, &output) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else
                    {
                        fprintf(outputFile, "\nNon-square matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 9:
            printf("Inverse\n");
            outputFile = fopen("inv.csv", "w");
            fputs("row,col,values", outputFile);
            int func_return;
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    if((func_return = inverseMatrix(matrix, &output)) == 0)
                    {
                        writeMatrix(outputFile, output);
                        freeMatrix(&output);
                    }
                    else if(func_return == 1)
                    {
                        fprintf(outputFile, "\nNon-square matrix");
                    }
                    else if(func_return == 2)
                    {
                        fprintf(outputFile, "\nSingular Matrix");
                    }
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;

        case 10:
            printf("Transpose\n");
            outputFile = fopen("transpose.csv", "w");
            fputs("row,col,values", outputFile);
            while(!feof(matrixFile))
            {
                if(readMatrix(matrixFile, &matrix) == 0)
                {
                    transposeMatrix(matrix, &output);
                    writeMatrix(outputFile, output);
                    freeMatrix(&output);
                    freeMatrix(&matrix);
                }
                else
                    fprintf(outputFile, "\nFailed to read matrix");
            }
            fclose(outputFile);
            break;
        case 0:
            fclose(matrixFile);
            return;

        default:
            printf("Invalid Selection!\n");
    }

}

int main()
{
    while(1)
    {
        printf("\nWelcome to Matrix Calculator program!\n");
        printf("Choose the function you wish to use:\n");
        printf("1) Console matrix calculator\n");
        printf("2) CSV matrix processor\n");
        printf("3) Read a matrix csv file\n");
        printf("4) Create a matrix csv file\n");
        printf("0) Quit program\n");
        printf("Selection: ");
        int select = getint();
        switch(select)
        {
            case 1:
                printf("Console matrix calculator\n");
                printf("Input the first matrix\n");
                Matrix matrix;
                getMatrix(&matrix);
                printf("The matrix you just input is:\n");
                printMatrix(matrix);
                calculator(matrix);
                break;

            case 2:
                csv_matrix();
                break;

            case 3:
                printf("Read Matrix csv File\n");
                printf("Input the file name: ");
                char filename[MAX_FILE_LENGTH + 1];
                char csvHeader[MAX_LINE];
                getstring(filename, MAX_FILE_LENGTH);
                FILE* csvFile = fopen(filename, "r");
                if(csvFile == NULL)
                {
                    printf("Cannot open file\n");
                    fclose(csvFile);
                    break;
                }
                fgets(csvHeader, MAX_LINE, csvFile);
                if(strcmp(csvHeader, "row,col,values\n") != 0)
                {
                    printf("CSV file header is missing and/or not a matrix csv file.\n");
                    fclose(csvFile);
                    break;
                }
                while(!feof(csvFile))
                {
                    if(readMatrix(csvFile, &matrix) == 0)
                    {
                        printMatrix(matrix);
                        freeMatrix(&matrix);
                    }
                    else
                    {
                        printf("\nFailed to read matrix\n");
                    }
                }
                break;

            case 4:
                printf("Create a new matrix csv file\n");
                printf("Input the file name: ");
                char new_file[MAX_FILE_LENGTH + 1];
                getstring(new_file, MAX_FILE_LENGTH);
                FILE* newCsv = fopen(new_file, "w");
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
                fclose(newCsv);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid Selection! Please select again.\n");
                break;
        }
    }
}