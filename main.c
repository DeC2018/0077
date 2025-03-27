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
    int i, count = 0, total = C(n, k);
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
    int n = 4, k = 2;
    int returnSize;
    int* returnColumnSizes;
    
    int** result = combine(n, k, &returnSize, &returnColumnSizes);
    printf("Input: n = %d, k = %d\n", n, k);
    printf("Output: ");
    printCombinations(result, returnSize, returnColumnSizes);
    
    // Example for n = 1, k = 1
    n = 1; k = 1;
    result = combine(n, k, &returnSize, &returnColumnSizes);
    printf("Input: n = %d, k = %d\n", n, k);
    printf("Output: ");
    printCombinations(result, returnSize, returnColumnSizes);
    
    // Free allocated memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);
    
    return 0;
}
