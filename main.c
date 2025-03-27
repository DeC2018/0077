#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int C(int n, int k) {
    if (k > 1)
        return n * C(n - 1, k - 1) / k;
    else
        return n;
}

void create(int num, int n, int *ans) {
    int i, j;
    for (i = 0, j = 0; i < n; i++) {
        if ((num & (1 << i)) > 0)
            ans[j++] = i + 1;
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int i, total = C(n, k), count = 0;
    int **ans = (int**)malloc(total * sizeof(int*));
    int *col = (int*)malloc(total * sizeof(int));
    for (i = 0; i < total; i++) {
        ans[i] = (int*)calloc(k, sizeof(int));
        col[i] = k;
    }
    *returnColumnSizes = col;
    *returnSize = total;

    for (i = 1; i < (1 << n); i++) {
        if (__builtin_popcount(i) == k) {
            create(i, n, ans[count]);
            count++;
        }
    }

    return ans;
}

void printCombinations(int** combinations, int returnSize, int* returnColumnSizes) {
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", combinations[i][j]);
            if (j < returnColumnSizes[i] - 1) {
                printf(",");
            }
        }
        printf("]");
        if (i < returnSize - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

int main() {
    int n1 = 4, k1 = 2;
    int returnSize1;
    int* returnColumnSizes1;
    printf("Input: n = %d, k = %d\n", n1, k1);
    int** result1 = combine(n1, k1, &returnSize1, &returnColumnSizes1);
    printf("Output: ");
    printCombinations(result1, returnSize1, returnColumnSizes1);

    for (int i = 0; i < returnSize1; i++) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes1);

    int n2 = 1, k2 = 1;
    int returnSize2;
    int* returnColumnSizes2;
    printf("Input: n = %d, k = %d\n", n2, k2);
    int** result2 = combine(n2, k2, &returnSize2, &returnColumnSizes2);
    printf("Output: ");
    printCombinations(result2, returnSize2, returnColumnSizes2);

    for (int i = 0; i < returnSize2; i++) {
        free(result2[i]);
    }
    free(result2);
    free(returnColumnSizes2);

    return 0;
}
