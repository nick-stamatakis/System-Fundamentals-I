#include "../include/global.h"

int SparseMatrix(int** M, int** S, int* D) {
    int numRows_M = *D;
    int numCols_M = *(D + 1);
    int m = (numRows_M > numCols_M) ? numRows_M : numCols_M;
    int nonZeroCount = 0;

    // Count the non-zero elements in M
    for (int row = 0; row < numRows_M; row++) {
        for (int col = 0; col < numCols_M; col++) {
            if (*(*(M + row) + col) != 0) {
                nonZeroCount++;
            }
        }
    }

    if (nonZeroCount <= m) {
        // The number of non-zero elements is less than or equal to m, so compact the matrix S
        int k = 0;
        for (int row = 0; row < numRows_M; row++) {
            for (int col = 0; col < numCols_M; col++) {
                if (*(*(M + row) + col) != 0) {
                    *(*(S + 0) + k) = row;
                    *(*(S + 1) + k) = col;
                    *(*(S + 2) + k) = *(*(M + row) + col);
                    k++;
                }
            }
        }
        // Fill the remaining elements of S with zeros
        for (int i = nonZeroCount; i < m; i++) {
            *(*(S + 0) + i) = 0;
            *(*(S + 1) + i) = 0;
            *(*(S + 2) + i) = 0;
        }

        return nonZeroCount; // Return the number of non-zero elements
    } else {
        // Matrix is not sparse, return -1
        return -1;
    }
}


int Addition(int **M, int **N, int **A, int *D) {
    int numRowsM = *D;
    int numColsM = *(D + 1);
    int numRowsN = *(D + 2);
    int numColsN = *(D + 3);
    int numRowsA = *(D + 4);
    int numColsA = *(D + 5);

    if (numRowsM != numRowsN || numColsM != numColsN) {
        // Incompatible dimensions of M and N
        if (numRowsA >= numRowsM && numColsA >= numColsM) {
            // A has enough space or dimension to hold the result
            for (int row = 0; row < numRowsM; row++) {
                for (int col = 0; col < numColsM; col++) {
                    *(*(A + row) + col) = *(*(M + row) + col) + *(*(N + row) + col);
                }
            }
            return -1; // A has the complete result of addition
        } else {
            // A does not have enough space or dimension
            for (int row = 0; row < numRowsA; row++) {
                for (int col = 0; col < numColsA; col++) {
                    *(*(A + row) + col) = *(*(M + row) + col) + *(*(N + row) + col);
                }
            }
            return -2; // A holds elements that overlap/intersect its dimension
        }
    }

    if (numRowsA < numRowsM || numColsA < numColsM) {
        // A is not compatible and doesn't have enough space to contain the whole result
        for (int row = 0; row < numRowsA; row++) {
            for (int col = 0; col < numColsA; col++) {
                *(*(A + row) + col) = *(*(M + row) + col) + *(*(N + row) + col);
            }
        }
        return -3; // Partial result in A
    }

    if (numRowsA == numRowsM && numColsA == numColsM) {
        // A is compatible with the exact dimension of the result
        for (int row = 0; row < numRowsM; row++) {
            for (int col = 0; col < numColsM; col++) {
                *(*(A + row) + col) = *(*(M + row) + col) + *(*(N + row) + col);
            }
        }
        return 1; // A has the exact result of addition
    }

    // A is oversized enough to contain the actual result
    for (int row = 0; row < numRowsM; row++) {
        for (int col = 0; col < numColsM; col++) {
            *(*(A + row) + col) = *(*(M + row) + col) + *(*(N + row) + col);
        }
    }
    return 2; // A is oversized
}

int Multiplication(int **M, int **N, int **A, int *D) {
    int numRowsM = *D;
    int numColsM = *(D + 1);
    int numRowsN = *(D + 2);
    int numColsN = *(D + 3);
    int numRowsA = *(D + 4);
    int numColsA = *(D + 5);

    if (numColsM != numRowsN) {
        // Incompatible dimensions of M and N for multiplication
        if (numRowsA >= numRowsM && numColsA >= numColsN) {
            // A has enough space or dimension to hold the result
            for (int row = 0; row < numRowsM; row++) {
                for (int col = 0; col < numColsN; col++) {
                    *(*(A + row) + col) = 0;
                    for (int k = 0; k < numColsM; k++) {
                        *(*(A + row) + col) += *(*(M + row) + k) * *(*(N + k) + col);
                    }
                }
            }
            return -1; // A has the complete result of multiplication
        } else {
            // A does not have enough space or dimension
            for (int row = 0; row < numRowsA; row++) {
                for (int col = 0; col < numColsA; col++) {
                    *(*(A + row) + col) = 0;
                    for (int k = 0; k < numColsM; k++) {
                        *(*(A + row) + col) += *(*(M + row) + k) * *(*(N + k) + col);
                    }
                }
            }
            return -2; // A holds elements that overlap/intersect its dimension
        }
    }

    // M and N are compatible
    if (numRowsA == numRowsM && numColsA == numColsN) {
        // A is compatible with the exact dimension of the result
        for (int row = 0; row < numRowsM; row++) {
            for (int col = 0; col < numColsN; col++) {
                *(*(A + row) + col) = 0;
                for (int k = 0; k < numColsM; k++) {
                    *(*(A + row) + col) += *(*(M + row) + k) * *(*(N + k) + col);
                }
            }
        }
        return 1; // A has the exact result of multiplication
    }

    if (numRowsA >= numRowsM && numColsA >= numColsN) {
        // A is oversized enough to contain the actual result
        for (int row = 0; row < numRowsM; row++) {
            for (int col = 0; col < numColsN; col++) {
                *(*(A + row) + col) = 0;
                for (int k = 0; k < numColsM; k++) {
                    *(*(A + row) + col) += *(*(M + row) + k) * *(*(N + k) + col);
                }
            }
        }
        return 2; // A is oversized
    }

    // A is not compatible, doesn't have enough space for the whole result
    for (int row = 0; row < numRowsA; row++) {
        for (int col = 0; col < numColsA; col++) {
            *(*(A + row) + col) = 0;
            for (int k = 0; k < numColsM; k++) {
                *(*(A + row) + col) += *(*(M + row) + k) * *(*(N + k) + col);
            }
        }
    }
    return -3; // Partial result in A
}

int Transpose(int** A, int** AT, int* D) {
    int numRows_A = *D;
    int numCols_A = *(D + 1);
    int numRows_AT = *(D + 2);
    int numCols_AT = *(D + 3);

    int result = 1; // Assume the transpose is possible.

    for (int i = 0; i < numRows_A; i++) {
        for (int j = 0; j < numCols_A; j++) {
            if (i < numCols_AT && j < numRows_AT) {
                *(*(AT + j) + i) = *(*(A + i) + j);
            }
            if (j >= numRows_AT || i >= numCols_AT) {
                result = -1; // Not enough space in AT for the full transpose
            }
        }
    }

    if (result == -1) {
        return -1;
    }

    return (numRows_A == numCols_AT && numCols_A == numRows_AT) ? 1 : 2;
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}