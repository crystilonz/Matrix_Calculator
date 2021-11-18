#include "matrix.h"
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_INPUT 50


float getfloat()
{
    int character;
    char bufferString[MAX_INPUT + 1];
    int i = 0;
    while((character = getchar()) != '\n')
    {
        bufferString[i] = (char) character;
        ++i;
        if(i >= MAX_INPUT)
            break;
    }
    bufferString[i] = '\0';
    return strtof(bufferString, NULL);
}

int getint()
{
    int character;
    char bufferString[MAX_INPUT + 1];
    int i = 0;
    while((character = getchar()) != '\n')
    {
        bufferString[i] = (char) character;
        ++i;
        if(i >= MAX_INPUT)
            break;
    }
    bufferString[i] = '\0';
    return (int) strtol(bufferString, NULL, 10);
}

void getstring(char* string, int len)
{
    int c;
    int count = 0;
    while((c = getchar()) != '\n')
    {
        string[count] = (char) c;
        if(count >= len)
            break;
        ++count;
    }
    string[count] = '\0';
}

enum Bool checkMatrix(Matrix input)
{
    if(input.row <= 0 || input.col <= 0)
    {
        printf("Invalid row and/or column\n");
        return False;
    }
    if(input.index == NULL)
    {
        printf("Allocation Error\n");
        return False;
    }

    for(int row = 0; row < input.row; row++)
    {
        if(input.index[row] == NULL)
        {
            printf("Allocation Error\n");
            return False;
        }
    }
    return True;
}

void iniMatrix(Matrix* matrix_ptr, int row, int col)
{
    matrix_ptr->row = row;
    matrix_ptr->col = col;
    matrix_ptr->index = (float**) malloc(row * sizeof(float*));
    for(int i = 0; i < row; ++i)
    {
        matrix_ptr->index[i] = (float*) malloc(col * sizeof(float));
    }
    if(!checkMatrix(*matrix_ptr))
    {
        exit(1);
    }
}

void freeMatrix(Matrix* matrix_ptr)
{
    for(int i = 0; i < matrix_ptr->row; ++i)
        free(matrix_ptr->index[i]);
    free(matrix_ptr->index);
}

void getMatrix(Matrix* matrix_ptr)
{
    printf("Specify number of rows: ");
    int row = getint();
    printf("Specify number of columns: ");
    int col = getint();
    iniMatrix(matrix_ptr, row, col);
    printf("Input a %ix%i matrix by rows using Aij\n", matrix_ptr->row, matrix_ptr->col);
    for(int current_row = 0; current_row < row; ++current_row)
    {
        for(int current_col = 0; current_col < col; ++current_col)
        {
            printf("A%i%i = ", current_row + 1, current_col + 1);
            matrix_ptr->index[current_row][current_col] = getfloat();
        }
    }
}

void printMatrix(Matrix matrix)
{
    printf("\n");
    for(int current_row = 0; current_row < matrix.row; ++current_row)
    {
        printf("[");
        for(int current_col = 0; current_col < matrix.col - 1; ++current_col)
        {
            printf(" %7.1f,", matrix.index[current_row][current_col]);
        }
        printf("%7.1f ]\n", matrix.index[current_row][matrix.col - 1]);
    }
    printf("\n");
}


int addMatrix(Matrix base1, Matrix base2, Matrix* results_ptr)
{
    if(base1.row != base2.row || base1.col != base2.col)
    {
        return -1;
    }
    iniMatrix(results_ptr, base1.row, base1.col);
    for(int current_row = 0; current_row < base1.row; ++current_row)
        for(int current_col = 0; current_col < base1.col; ++current_col)
            results_ptr->index[current_row][current_col] = base1.index[current_row][current_col]
                                                           + base2.index [current_row][current_col];
    return 0;
}

int subMatrix(Matrix base1, Matrix base2, Matrix* results_ptr)
{
    if(base1.row != base2.row || base1.col != base2.col)
    {
        results_ptr = NULL;
        return -1;
    }
    iniMatrix(results_ptr, base1.row, base1.col);
    for(int current_row = 0; current_row < base1.row; ++current_row)
        for(int current_col = 0; current_col < base1.col; ++current_col)
            results_ptr->index[current_row][current_col] = base1.index[current_row][current_col]
                                                           - base2.index [current_row][current_col];
    return 0;
}

void copyMatrix(Matrix from_matrix, Matrix* to_ptr)
{
    iniMatrix(to_ptr, from_matrix.row, from_matrix.col);
    for(int current_row = 0; current_row < from_matrix.row; ++current_row)
        for(int current_col = 0; current_col < from_matrix.col; ++current_col)
            to_ptr->index[current_row][current_col] = from_matrix.index[current_row][current_col];
}

int multiplyMatrix(Matrix base, Matrix multiply, Matrix* results_ptr)
{
    if(base.col != multiply.row)
        return -1;
    float buffer;
    iniMatrix(results_ptr, base.row, multiply.col);
    for(int resultsRow = 0; resultsRow < base.row; ++resultsRow)
    {
        for(int resultsCol = 0; resultsCol < multiply.col; ++resultsCol)
        {
            buffer = 0;
            for(int index = 0; index < base.col; index++)
            {
                buffer = buffer + (base.index[resultsRow][index] * multiply.index[index][resultsCol]);
            }
            results_ptr->index[resultsRow][resultsCol] = buffer;
        }
    }
    return 0;
}

void scalarMatrix(Matrix base, float scalar, Matrix* results_ptr)
{
    iniMatrix(results_ptr, base.row, base.col);
    for(int current_row = 0; current_row < base.row; ++current_row)
        for(int current_col = 0; current_col < base.col; ++current_col)
            results_ptr->index[current_row][current_col] = base.index[current_row][current_col] * scalar;
}

int powerMatrix(Matrix base, int exponent, Matrix* results_ptr)
{
    if(base.row != base.col)
        return -1;
    if(exponent == 0)
    {
        iniMatrix(results_ptr, base.row, base.col);
        for(int i = 0; i < base.row; i++)
        {
            for(int j = 0; j < base.col; j++)
            {
                if(i == j)
                    results_ptr->index[i][j] = 1;
                else
                    results_ptr->index[i][j] = 0;
            }
        }
    }
    else
    {
        exponent = abs(exponent);
        Matrix bufferMatrix;
        copyMatrix(base, &bufferMatrix); // initiate buffer
        for(int i = 1; i < exponent; ++i)
        {
            multiplyMatrix(bufferMatrix, base, results_ptr); //memory allocated to results_ptr
            freeMatrix(&bufferMatrix);
            copyMatrix(*results_ptr, &bufferMatrix);
            freeMatrix(results_ptr);
        }
        copyMatrix(bufferMatrix, results_ptr);
        freeMatrix(&bufferMatrix);
    }
    return 0;
}

// file handling section
void readMatrix(FILE* csv, Matrix* matrix_ptr)
{
    // csv in format of row, column, values(1;2;3;4;5..)
    char line_buffer[MAX_LINE + 1];
    char* itr;
    fgets(line_buffer, MAX_LINE, csv);

    // get row
    int row = (int) strtol(line_buffer, &itr, 10);

    // forward by one character then get column
    if(*itr != ',')
    {
        printf("Error getting matrix");
        return;
    }
    itr += 1;
    int column = (int) strtol(itr, &itr, 10);

    // forward by one character then get values
    if(*itr != ',')
    {
        printf("Error getting matrix");
        return;
    }
    itr += 1;
    iniMatrix(matrix_ptr, row, column);
    for(int i = 0; i < matrix_ptr->row; i++)
    {
        for(int j = 0; j < matrix_ptr->col; j++)
        {
            matrix_ptr->index[i][j] = strtof(itr, &itr);
            if(*itr == ';')
                itr += 1;
            else
            {
                printf("Error getting matrix");
                freeMatrix(matrix_ptr);
                return;
            }
        }
    }
}

void writeMatrix(FILE* csv, Matrix matrix)
{
    char row[MAX_INPUT + 1];
    char col[MAX_INPUT + 1];
    sprintf(row, "%d", matrix.row);
    sprintf(col, "%d", matrix.col);
    fputc('\n', csv);
    fputs(row, csv);
    fputc(',', csv);
    fputs(col, csv);
    fputc(',', csv);

    char buffer[MAX_INPUT + 1];
    for(int i = 0; i < matrix.row; i++)
    {
        for(int j = 0; j < matrix.col; j++)
        {
            sprintf(buffer, "%.3f", matrix.index[i][j]);
            fputs(buffer, csv);
            fputc(';', csv);
        }
    }
}
