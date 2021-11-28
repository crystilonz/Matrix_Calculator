# Matrix Calculator

# Brief
This program is a C program to do matrix arithmetics via both console and .csv files

>By Jetanat Sihanatkathakul (64011729)

# Capabilities
The program is able to process matrices in bulk(via .csv) or individually(via console command)
using the following operations:
- Addition
- Subtraction
- Matrix Multiplication
- Scalar Multiplication
- Exponentiation
- Determinant of the matrix
- Cofactor of the matrix
- Adjugate of the matrix
- Inverse of the matrix
- Transpose of the matrix
- Creating .csv files containing matrices
- Reading .csv files onto the console matrix by matrix

#Technical Information

###CSV files

Each matrix can be represented by its **dimension** (row x column) and the **values** in each cell.
The csv file for this program is thus in this format.

    row,col,values

For example this matrix

    [1, 2, 3]
    [4, 5, 6]
    [7, 8, 9]

can be represented with its dimension(3x3) and a list of 9(3x3) values like so

    row,col,values
    3,3,1;2;3;4;5;6;7;8;9

Each matrix will be contained within a single row in the csv file and the csv file can contain as many matrices
as there are lines(excluding the header).


###Console Matrix Notation

Common mathematical notation for each cell in the matrix is as:

    [a11, a12, a13]
    [a21, a22, a23]
    [a31, a32, a33]

for a 3x3 matrix. The general form is

    aij

in which `i` is the *row* and `j` is the *column*. The console command will follow this mathematical
notation for the console calculator and creating the csv file.


###Supplying the Second Operand

While the program is able to process the matrices in a csv file in bulk, the second operand matrix is limited to 
a single matrix.

When dealing with matrix addition, subtraction, and multiplication the program will ask the user to provide
another csv file as the operand. The program will only read the first matrix in the csv and it will ignore the rest.

> The matrix notation is not included in the csv files but is included here for demonstration purposes.
> They are supplied by the program's read function.

For example when adding these two csv files:

    
    Operand 1:
    row,col,values
    3,3,4.000;5.000;2.000;3.000;1.000;5.000;6.000;7.000;2.000;
    3,3,1.000;6.000;3.000;4.000;5.000;7.000;2.000;3.000;5.000;
    3,3,1.000;1.000;1.000;1.000;1.000;2.000;2.000;2.000;3.000;
    3,3,6.000;8.000;1.000;2.000;4.000;6.000;2.000;3.000;2.000;

    [     4.0,     5.0,    2.0 ]
    [     3.0,     1.0,    5.0 ]
    [     6.0,     7.0,    2.0 ]

    [     1.0,     6.0,    3.0 ]
    [     4.0,     5.0,    7.0 ]
    [     2.0,     3.0,    5.0 ]

    [     1.0,     1.0,    1.0 ]
    [     1.0,     1.0,    2.0 ]
    [     2.0,     2.0,    3.0 ]

    [     6.0,     8.0,    1.0 ]
    [     2.0,     4.0,    6.0 ]
    [     2.0,     3.0,    2.0 ]
    
    -------------------------------------------------------------

    Operand 2:
    row,col,values
    3,3,-5.000;-6.500;22.000;4.000;5.000;-17.000;-1.000;-1.000;4.000;
    3,3,1;2;3;4;1;2;3;4;5;

    [    -5.0,    -6.5,   22.0 ]
    [     4.0,     5.0,  -17.0 ]
    [    -1.0,    -1.0,    4.0 ]
    
    [     1.0,     2.0,    3.0 ]
    [     4.0,     1.0,    2.0 ]
    [     3.0,     4.0,    5.0 ]

will yield

    results:
    row,col,values
    3,3,-1.000;-1.500;24.000;7.000;6.000;-12.000;5.000;6.000;6.000;
    3,3,-4.000;-0.500;25.000;8.000;10.000;-10.000;1.000;2.000;9.000;
    3,3,-4.000;-5.500;23.000;5.000;6.000;-15.000;1.000;1.000;7.000;
    3,3,1.000;1.500;23.000;6.000;9.000;-11.000;1.000;2.000;6.000;

    [    -1.0,    -1.5,   24.0 ]
    [     7.0,     6.0,  -12.0 ]
    [     5.0,     6.0,    6.0 ]
    
    [    -4.0,    -0.5,   25.0 ]
    [     8.0,    10.0,  -10.0 ]
    [     1.0,     2.0,    9.0 ]
    
    [    -4.0,    -5.5,   23.0 ]
    [     5.0,     6.0,  -15.0 ]
    [     1.0,     1.0,    7.0 ]

    [     1.0,     1.5,   23.0 ]
    [     6.0,     9.0,  -11.0 ]
    [     1.0,     2.0,    6.0 ]


The matrices in the resulting csv files are the sum of all the matrices in the
first csv file `Operand 1` with the first matrix in the second csv file `Operand 2`
which is

    row,col,values
    3,3,-5.000;-6.500;22.000;4.000;5.000;-17.000;-1.000;-1.000;4.000;

    [    -5.0,    -6.5,   22.0 ]
    [     4.0,     5.0,  -17.0 ]
    [    -1.0,    -1.0,    4.0 ]


###Output Filename

The output file name is different depending on the selected function.

| Command | Output filename|
| --- | --- |
| Addition | add.csv |
| Subtraction | subtract.csv |
| Matrix Multiplication | multply.csv |
| Scalar Multiplication | smultiply.csv |
| Exponentiation | expo.csv |
| Determinant | det.csv |
| Cofactor | cofactor.csv |
| Adjugate | adj.csv |
| Inverse | inv.csv |
| Transpose | transpose.csv |
| Creating .csv file | *user-defined* |


###Output File Characteristics

The output files are in the same csv form are guaranteed to have the same number of lines as the first operand file.
In case that there are:
- Incompatible matrices (Dimension mismatch)
- Non-square matrices for square matrix operations
- Bad lines / Erroneous matrix lines
- etc.

The program will process the matrices that can be processed.
It will put helpful error messages in the output files for the matrices that cannot be processed.

For example, suppose we have the csv file

    row,col,values
    3,2,5.000;1.000;2.000;3.000;5.000;2.000;
    2,2,6.000;1.000;2.000;5.000;
    3,3,2.000;5.000;1.000;4.000;7.000;5.000;5.000;4.000;3.000;
    3,3,0.000;0.000;0.000;4.000;7.000;5.000;5.000;4.000;3.000;
    1,1,6.000;
    2,2,6.000;1.000;2.000;4.000;
    2,1,4.000;6.000;
    3,3,9.000;7.000;1.000;4.000;2.000;5.000;1.000;2.000;4.000;
    something
    4,4,3.000;2.000;

    [     5.0,    1.0 ]
    [     2.0,    3.0 ]
    [     5.0,    2.0 ]

    [     6.0,    1.0 ]
    [     2.0,    5.0 ]
    
    [     2.0,     5.0,    1.0 ]
    [     4.0,     7.0,    5.0 ]
    [     5.0,     4.0,    3.0 ]
    
    [     0.0,     0.0,    0.0 ]
    [     4.0,     7.0,    5.0 ]
    [     5.0,     4.0,    3.0 ]

    [    6.0 ]

    [     6.0,    1.0 ]
    [     2.0,    4.0 ]
    
    [    4.0 ]
    [    6.0 ]

    [     9.0,     7.0,    1.0 ]
    [     4.0,     2.0,    5.0 ]
    [     1.0,     2.0,    4.0 ]
    
    Failed to read matrix
    
    Failed to read matrix

The last two lines are erroneous because the second to last is just a string `something`
and the last matrix is `4,4,3.000;2.000;` which specifies 4 rows and 4 columns which in turn needs 16 values to 
supply the matrix. The csv file, however, supplies only two.

The inverse of a matrix only exists for non-singular square matrix. Therefore, for the matrices that do not have an
inverse, the program will specify why the inverse does not exist.

>A square matrix is a matrix with equal numbers of rows and columns.

>A singular matrix is a square matrix with determinant = 0. 

The output of running this csv file through the inverse function is:

    row,col,values
    Non-square matrix
    2,2,0.179;-0.036;-0.071;0.214;
    3,3,0.021;-0.229;0.375;0.271;0.021;-0.125;-0.396;0.354;-0.125;
    Singular Matrix
    1,1,0.167;
    2,2,0.182;-0.045;-0.091;0.273;
    Non-square matrix
    3,3,0.022;0.292;-0.371;0.124;-0.393;0.461;-0.067;0.124;0.112;
    Failed to read matrix
    Failed to read matrix

    Failed to read matrix

    [   0.179, -0.036 ]
    [  -0.071,  0.214 ]

    [   0.021,  -0.229,  0.375 ]
    [   0.271,   0.021, -0.125 ]
    [  -0.396,   0.354, -0.125 ]
    
    Failed to read matrix

    [  0.167 ]

    [   0.182, -0.045 ]
    [  -0.091,  0.273 ]
    
    Failed to read matrix
    
    [   0.022,   0.292, -0.371 ]
    [   0.124,  -0.393,  0.461 ]
    [  -0.067,   0.124,  0.112 ]
    
    Failed to read matrix
    
    Failed to read matrix

with the same file. Multiplying the matrices with another matrix of 3x3 dimension yields:
>Multiplication between matrices is only defined iff for A x B:
>col(A) = row(B)

    Operand for multiplication:
    row,col,values
    3,3,2.000;3.000;1.000;4.000;5.000;2.000;4.000;3.000;4.000;

    [   2.000,   3.000,  1.000 ]
    [   4.000,   5.000,  2.000 ]
    [   4.000,   3.000,  4.000 ]
    
    -------------------------------------------------------------

    Results:
    row,col,values
    Failed to multiply matrix
    Failed to multiply matrix
    3,3,28.000;34.000;16.000;56.000;62.000;38.000;38.000;44.000;25.000;
    3,3,0.000;0.000;0.000;56.000;62.000;38.000;38.000;44.000;25.000;
    Failed to multiply matrix
    Failed to multiply matrix
    Failed to multiply matrix
    3,3,50.000;65.000;27.000;36.000;37.000;28.000;26.000;25.000;21.000;
    Failed to read matrix
    Failed to read matrix

    Failed to read matrix
    
    Failed to read matrix
    
    [  28.000,  34.000, 16.000 ]
    [  56.000,  62.000, 38.000 ]
    [  38.000,  44.000, 25.000 ]

    [   0.000,   0.000,  0.000 ]
    [  56.000,  62.000, 38.000 ]
    [  38.000,  44.000, 25.000 ]

    Failed to read matrix
    
    Failed to read matrix
    
    Failed to read matrix
    
    [  50.000,  65.000, 27.000 ]
    [  36.000,  37.000, 28.000 ]
    [  26.000,  25.000, 21.000 ]
    
    Failed to read matrix
    
    Failed to read matrix

###Determinant

Since the result of the determinant is not a matrix, the output file is in this form instead:
> A determinant of a matrix is only defined for a square matrix.
    
    Determinant
    |matrix 1|
    |matrix 2|
    ...

By common notation, `|A|` denotes determinant of matrix A.

using the same input file as before

    row,col,values
    3,2,5.000;1.000;2.000;3.000;5.000;2.000;
    2,2,6.000;1.000;2.000;5.000;
    3,3,2.000;5.000;1.000;4.000;7.000;5.000;5.000;4.000;3.000;
    3,3,0.000;0.000;0.000;4.000;7.000;5.000;5.000;4.000;3.000;
    1,1,6.000;
    2,2,6.000;1.000;2.000;4.000;
    2,1,4.000;6.000;
    3,3,9.000;7.000;1.000;4.000;2.000;5.000;1.000;2.000;4.000;
    something
    4,4,3.000;2.000;

    [     5.0,    1.0 ]
    [     2.0,    3.0 ]
    [     5.0,    2.0 ]

    [     6.0,    1.0 ]
    [     2.0,    5.0 ]
    
    [     2.0,     5.0,    1.0 ]
    [     4.0,     7.0,    5.0 ]
    [     5.0,     4.0,    3.0 ]
    
    [     0.0,     0.0,    0.0 ]
    [     4.0,     7.0,    5.0 ]
    [     5.0,     4.0,    3.0 ]

    [    6.0 ]

    [     6.0,    1.0 ]
    [     2.0,    4.0 ]
    
    [    4.0 ]
    [    6.0 ]

    [     9.0,     7.0,    1.0 ]
    [     4.0,     2.0,    5.0 ]
    [     1.0,     2.0,    4.0 ]
    
    Failed to read matrix
    
    Failed to read matrix

The results from running this file via the determinant function is:

    Determinant
    Non-square matrix
    28.000000
    48.000000
    0.000000
    6.000000
    22.000000
    Non-square matrix
    -89.000000
    Failed to read matrix
    Failed to read matrix