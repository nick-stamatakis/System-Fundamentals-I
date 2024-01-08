
#include "matrix.c"
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int iMax, int jMax, int** S) {
    for (int i = 0; i < iMax; i++) {
        for (int j = 0; j < jMax; j++) {
            printf("%d\t", S[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]){  

    printf("-------------------------------");
    printf("\n(SparseMatrix Test Cases)\n");
    printf("-------------------------------\n\n");
    //Test Case: 1
    int values[] = {0, 4, 0, 5, 0, 0, 2, 0};
    int **M = initializeMatrix(4, 2, values);
    int dimensions[2] = {4, 2};
    int *D = dimensions;
    int svalues[12] = {0};
    int** S = initializeMatrix(3, 4, svalues);
    int val = SparseMatrix(M, S, D);
    printf("S Matrix:\n");
    printMatrix(3, 4, S);
    printf("Return Value: %d\n\n", val);


    //Test Case: 2
    int dimensions2[2] = {4, 4};
    int *D2 = dimensions2;
    int values2[] = {2, 3, 0, 5, 3, 0, 3, 1, 4, 0, 3, 0, 0, 0, 6, 0};
    int **M2 = initializeMatrix(4, 4, values2);
    int svalues2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int **S2 = initializeMatrix(3, 4, svalues2);
    int newVal = SparseMatrix(M2, S2, D2);
    printf("S Matrix:\n");
    printMatrix(3, 4, S2);
    printf("Return Value: %d\n\n", newVal);

    // Test Case: 3
    int M_values[] = {0, 4, 0, 5, 3, 0, 2, 0};
    int** MM1 = initializeMatrix(4, 2, M_values);
    int dd1[] = {4, 2};
    int sval[8] = {0};
    int **SS1 = initializeMatrix(3, 4, sval);
    int result = SparseMatrix(MM1, SS1, dd1);
    printf("S Matrix:\n");
    printMatrix(3, 4, SS1);
    printf("Return Value: %d\n\n", result);

    // Test Case: 4
    int M2_values[] = {0, 0, 0, 0, 3, 0, 4, 0, 0, 0};
    int** MM2 = initializeMatrix(2, 5, M2_values);
    int dd2[] = {2, 5};
    int sval2[15] = {0};
    int **SS2 = initializeMatrix(3, 5, sval2);
    int result2 = SparseMatrix(MM2, SS2, dd2);
    printf("S Matrix:\n");
    printMatrix(3, 5, SS2);
    printf("Return Value: %d\n\n", result2);


    printf("-------------------------------");
    printf("\n(Addition Test Cases)\n");
    printf("-------------------------------\n\n");
    // Test Case: 1
    int mArray[] = {2, 3, 1, 3, 4, 5};
    int **M3 = initializeMatrix(3, 2, mArray);
    int nArray[] = {3, 3, 7, 2, 1, 5};
    int **N3 = initializeMatrix(3, 2, nArray);
    int aArray[] = {0, 0, 0, 0, 0, 0};
    int **A3 = initializeMatrix(3, 2, aArray);
    int dimensions3[6] = {3, 2, 3, 2, 3, 2};
    int *D3 = dimensions3;
    int value3 = Addition(M3, N3, A3, D3);
    printf("A Matrix:\n");
    printMatrix(3, 2, A3);
    printf("Return Value: %d\n\n", value3);

    // Test Case: 2
    int mArray2[] = {2, 3, 1, 3, 4, 5};
    int **M4 = initializeMatrix(3, 2, mArray2);
    int nArray2[] = {3, 3, 7, 2, 1, 5};
    int **N4 = initializeMatrix(3, 2, nArray2);
    int aArray2[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int **A4 = initializeMatrix(4, 3, aArray2);
    int dimension4[6] = {3, 2, 3, 2, 4, 2};
    int *D4= dimension4;
    int value4 = Addition(M4, N4, A4, D4);
    printf("A Matrix:\n");
    printMatrix(4, 2, A4);
    printf("Return Value: %d\n\n", value4);

    // Test Case: 3
    int mArray3[] = {2, 3, 1, 3, 4, 5};
    int **M5 = initializeMatrix(3, 2, mArray3);
    int nArray3 [] = {5, 6, 8, 5, 5, 10, 5, 10};
    int **N5 = initializeMatrix(4, 2, nArray3);
    int aArray3[] = {0, 0, 0};
    int **A5 = initializeMatrix(3, 1, aArray3);
    int dimension5[6] = {3, 2, 4, 2, 3, 1};
    int *D5 = dimension5;
    int value5 = Addition(M5, N5, A5, D5);
    printf("A Matrix:\n");
    printMatrix(3, 1, A5);
    printf("Return Value: %d\n\n", value5);

    // Test Case: 4
    int mArray6[] = {2, 3, 1, 3, 4, 5};
    int **M6 = initializeMatrix(3, 2, mArray6);
    int nArray6[] = {5, 6, 8, 5, 5, 10, 5, 10};
    int **N6 = initializeMatrix(4, 2, nArray6);
    int aArray6[10] = {0};
    int **A6 = initializeMatrix(5, 2, aArray6);
    int dimension6[6] = {3, 2, 4, 2, 5, 2};
    int *D6 = dimension6;
    int value6 = Addition(M6, N6, A6, D6);
    printf("A Matrix:\n");
    printMatrix(5, 2, A6);
    printf("Return Value: %d\n\n", value6);

    // Test Case: 5
    int mArray7[] = {2, 3, 1, 3, 4, 5};
    int **M7 = initializeMatrix(3, 2, mArray7);
    int nArray7[] = {3, 3, 7, 2, 1, 5};
    int **N7 = initializeMatrix(3, 2, nArray7);
    int aArray7[9] = {0};
    int **A7 = initializeMatrix(3, 3, aArray7);
    int dimension7[6] = {3, 2, 3, 2, 3, 3};
    int *D7 = dimension7;
    int value7 = Addition(M7, N7, A7, D7);
    printf("A Matrix:\n");
    printMatrix(3, 3, A7);
    printf("Return Value: %d\n\n", value7);


    printf("-------------------------------");
    printf("\n(Multiplication Test Cases)\n");
    printf("-------------------------------\n\n");

    // Test Case: 1
    int mArray11[] = {2, 3, 5, 4, 2, 3};
    int **M11 = initializeMatrix(3, 2, mArray11);
    int nArray11[] = {3, 2, 1, 1, 3, 4};
    int **N11 = initializeMatrix(2, 3, nArray11);
    int aArray11[9] = {0};
    int **A11 = initializeMatrix(3, 3, aArray11);
    int d11[6] = {3, 2, 2, 3, 3, 3};
    int *D11 = d11;
    int v11 = Multiplication(M11, N11, A11, D11);
    printf("A Matrix:\n");
    printMatrix(3, 3, A11);
    printf("Return Value: %d\n\n", v11);

    // Test Case: 2
    int **M22 = initializeMatrix(3, 2, mArray11);
    int nArray22[] = {3, 3, 7, 2, 1, 5};
    int **N22 = initializeMatrix(3, 2, nArray22);
    int aArray22[2] = {0};
    int **A22 = initializeMatrix(2, 1, aArray22);
    int d22[6] = {3, 2, 3, 2, 2, 1};
    int *D22 = d22;
    int v22 = Multiplication(M22, N22, A22, D22);
    printf("A Matrix:\n");
    printMatrix(2, 1, A22);
    printf("Return Value: %d\n\n", v22);

    // Test Case: 3
    int **M33 = initializeMatrix(3, 2, mArray11);
    int **N33 = initializeMatrix(3, 2, nArray22);
    int aArray33[6] = {0};
    int **A33 = initializeMatrix(3, 2, aArray33);
    int d33[6] = {3, 2, 3, 2, 3, 2};
    int *D33 = d33;
    int v33 = Multiplication(M33, N33, A33, D33);
    printf("A Matrix:\n");
    printMatrix(3, 2, A33);
    printf("Return Value: %d\n\n", v33);

    // Test Case: 4
    int **M44 = initializeMatrix(3, 2, mArray11);
    int **N44 = initializeMatrix(2, 3, nArray11);
    int aArray44[12] = {0};
    int **A44 = initializeMatrix(4, 3, aArray44);
    int d44[6] = {3, 2, 2, 3, 4, 3};
    int *D44 = d44;
    int v44 = Multiplication(M44, N44, A44, D44);
    printf("A Matrix:\n");
    printMatrix(4, 3, A44);
    printf("Return Value: %d\n\n", v44);

    // Test Case: 5
    int **M55 = initializeMatrix(3, 2, mArray11);
    int **N55 = initializeMatrix(2, 3, nArray11);
    int aArray55[6] = {0};
    int **A55 = initializeMatrix(3, 2, aArray55);
    int d55[6] = {3, 2, 2, 3, 3, 2};
    int *D55 = d55;
    int v55 = Multiplication(M55, N55, A55, D55);
    printf("A Matrix:\n");
    printMatrix(3, 2, A55);
    printf("Return Value: %d\n\n", v55);

    printf("-------------------------------");
    printf("\n(Transpose Test Cases)\n");
    printf("-------------------------------\n\n");

    int arr[] = {9, 9, 1, 2, 9, 3};
    int** Mtst = initializeMatrix(3, 2, arr);
    int arr2[] = {0, 0, 0, 0, 0, 0};
    int** A_act = initializeMatrix(2, 3, arr2);
    int arr3[] = {9, 1, 9, 9, 2, 3};
    int** A_exp = initializeMatrix(2, 3, arr3);
    int Dtst[4] = {3,2,2,3};
    int ret_act = Transpose(Mtst, A_act, Dtst);
    int ret_exp = 1;
    printf("AT Matrix:\n");
    printMatrix(2, 3, A_act);
    printf("Return Value: %d\n\n", ret_act);

    int a1[] = {9, 9, 1, 2, 9, 3};
    int** Mtst1 = initializeMatrix(3, 2, a1);
    int Aa1[8] = {0};
    int** A_act1 = initializeMatrix(2, 4, Aa1);
    int Dtst1[4] = {3,2,2,4};
    int ret_act1 = Transpose(Mtst1, A_act1, Dtst1);
    printf("AT Matrix:\n");
    printMatrix(2, 4, A_act1);
    printf("Return Value: %d\n\n", ret_act1);

    

    return 0;
}