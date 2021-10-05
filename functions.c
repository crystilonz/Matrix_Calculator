#include <stdio.h>
#include <stdlib.h>

typedef float Matrix[3][3];

void getMatrix(Matrix);
void printMatrix(Matrix);
float getfloat();
void copyMatrix(Matrix, Matrix);
void transpose(Matrix, Matrix);

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
    }
    bufferstring[i] = '\0';
    return strtol(bufferstring, NULL, 10);
}

void getMatrix(Matrix input)
{
    printf("Input a 3x3 matrix by rows using Aij\n");
    printf("A11: ");
    input[0][0] = getfloat();

    printf("A12: ");
    input[0][1] = getfloat();

    printf("A13: ");
    input[0][2] = getfloat();

    printf("A21: ");
    input[1][0] = getfloat();

    printf("A22: ");
    input[1][1] = getfloat();

    printf("A23: ");
    input[1][2] = getfloat();

    printf("A31: ");
    input[2][0] = getfloat();

    printf("A32: ");
    input[2][1] = getfloat();

    printf("A33: ");
    input[2][2] = getfloat();

    printf("\n");
}

void printMatrix(Matrix matrix)
{
    printf("\n[ %5.1f, %5.1f, %5.1f ]\n", matrix[0][0], matrix[0][1], matrix[0][2]);
    printf("[ %5.1f, %5.1f, %5.1f ]\n", matrix[1][0], matrix[1][1], matrix[1][2]);
    printf("[ %5.1f, %5.1f, %5.1f ]\n", matrix[2][0], matrix[2][1], matrix[2][2]);
}

void copyMatrix(Matrix from, Matrix to)
{
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            to[i][j] = from[i][j];
}

void transpose(Matrix base, Matrix results)
{
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            results[i][j] = base[j][i];
}