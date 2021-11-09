#include "matrix.h"
#include <stdio.h>
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

void iniMatrix(Matrix* ini, int row, int col)
{
    ini->row = row;
    ini->col = col;
    ini->index = (float**) malloc(row * sizeof(float*));
    for(int i = 0; i < row; ++i)
    {
        ini->index[i] = (float*) malloc(col * sizeof(float));
    }
    if(!checkMatrix(*ini))
    {
        exit(1);
    }
}

void getMatrix(Matrix* input)
{
    printf("Specify number of rows: ");
    int row = getint();
    printf("Specify number of columns: ");
    int col = getint();
    iniMatrix(input, row, col);
    printf("Input a %ix%i matrix by rows using Aij\n", input->row, input->col);
    for(int current_row = 0; current_row < row; ++current_row)
    {
        for(int current_col = 0; current_col < col; ++current_col)
        {
            printf("A%i%i = ", current_row + 1, current_col + 1);
            input->index[current_row][current_col] = getfloat();
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


void addMatrix(Matrix base1, Matrix base2, Matrix* results)
{
    iniMatrix(results, base1.row, base1.col);
    for(int current_row = 0; current_row < base1.row; ++current_row)
        for(int current_col = 0; current_col < base1.col; ++current_col)
            results->index[current_row][current_col] = base1.index[current_row][current_col]
                    + base2.index [current_row][current_col];
}

void subMatrix(Matrix base1, Matrix base2, Matrix* results)
{
    iniMatrix(results, base1.row, base1.col);
    for(int current_row = 0; current_row < base1.row; ++current_row)
        for(int current_col = 0; current_col < base1.col; ++current_col)
            results->index[current_row][current_col] = base1.index[current_row][current_col]
                    - base2.index [current_row][current_col];
}

void copyMatrix(Matrix from, Matrix* to)
{
    for(int current_row = 0; current_row < from.row; ++current_row)
        for(int current_col = 0; current_col < from.col; ++current_col)
            to->index[current_row][current_col] = from.index[current_row][current_col];
}

void multiplyMatrix(Matrix base, Matrix multiply, Matrix* results)
{
    float buffer;
    iniMatrix(results, base.row, multiply.col);
    for(int resultsRow = 0; resultsRow < base.row; ++resultsRow)
    {
        for(int resultsCol = 0; resultsCol < multiply.col; ++resultsCol)
        {
            buffer = 0;
            for(int index = 0; index < base.col; index++)
            {
                buffer = buffer + (base.index[resultsRow][index] * multiply.index[index][resultsCol]);
            }
            results->index[resultsRow][resultsCol] = buffer;
        }
    }
}

void scalarMatrix(Matrix base, float scalar, Matrix* results)
{
    iniMatrix(results, base.row, base.col);
    for(int current_row = 0; current_row < base.row; ++current_row)
        for(int current_col = 0; current_col < base.col; ++current_col)
            results->index[current_row][current_col] = base.index[current_row][current_col] * scalar;
}

void powerMatrix(Matrix base, int exponent, Matrix* results)
{
    Matrix bufferMatrix;
    copyMatrix(base, &bufferMatrix);
    copyMatrix(base, results);
    for(int i = 1; i < exponent; ++i)
    {
        multiplyMatrix(bufferMatrix, base, results);
        copyMatrix(*results, &bufferMatrix);
    }
}

// file handling section
void readMatrix(FILE* csv, Matrix* matrix)
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
    iniMatrix(matrix, row, column);
    for(int i = 0; i < matrix->row; i++)
    {
        for(int j = 0; j < matrix->col; j++)
        {
            if(*itr != '\0' && *itr != '\n')
            {
                matrix->index[i][j] = strtof(itr, &itr);
                itr += 1;
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
