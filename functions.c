#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
    float** index;
}Matrix;

float getfloat();
int getint();
void iniMatrix(Matrix*, int, int);
int checkMatrix(Matrix);
void getMatrix(Matrix*);
void printMatrix(Matrix);
void addMatrix(Matrix, Matrix, Matrix*);
void subMatrix(Matrix, Matrix, Matrix*);
void scalarMatrix(Matrix, float, Matrix*);
void copyMatrix(Matrix, Matrix*);
void powerMatrix(Matrix, int, Matrix*);


float getfloat()
{
    int character;
    char bufferstring[20];
    int i = 0;
    while((character = getchar()) != '\n')
    {
        bufferstring[i] = (char) character;
        ++i;
    }
    bufferstring[i] = '\0';
    return strtof(bufferstring, NULL);
}

int getint()
{
    int character;
    char bufferstring[20];
    int i = 0;
    while((character = getchar()) != '\n')
    {
        bufferstring[i] = (char) character;
        ++i;
        if(i >= 18)
            break;
    }
    bufferstring[i] = '\0';
    return (int) strtol(bufferstring, NULL, 10);
}

int checkMatrix(Matrix input)
{
    if(input.row == 0 || input.col == 0 || input.index == NULL)
        return 0;

    for(int row = 0; row < input.row; row++)
    {
        if(input.index[row] == NULL)
            return 0;
    }

    return 1;
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
        printf("Initialisation failed! Cannot allocate memory");
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
    iniMatrix(to, from.row, from.col);
    for(int current_row = 0; current_row < from.row; ++current_row)
        for(int current_col = 0; current_col < from.col; ++current_col)
            to->index[current_row][current_col] = from.index[current_row][current_col];
}

void multiplyMatrix(Matrix base, Matrix mult, Matrix* results)
{
    float buffer;
    iniMatrix(results, base.row, mult.col);
    for(int resultsRow = 0; resultsRow < base.row; ++resultsRow)
    {
        for(int resultsCol = 0; resultsCol < mult.col; ++resultsCol)
        {
            buffer = 0;
            for(int index = 0; index < base.col; index++)
            {
                buffer = buffer + (base.index[resultsRow][index] * mult.index[index][resultsCol]);
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