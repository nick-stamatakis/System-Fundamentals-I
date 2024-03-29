#include "../tests/unit_tests.h"
#include "global.h"
int main() { 
    int** M = initializeMatrix(3, 2, (int[]){9, 9, 1, 2, 9, 3});
    int** A_act = initializeMatrix(2, 3, (int[]){0, 0, 0, 0, 0, 0});
    int D[4] = {3,2,2,3};
    Transpose(M, A_act, D);
    freeMatrix(3, M); freeMatrix(2, A_act);
    return 0;
}
