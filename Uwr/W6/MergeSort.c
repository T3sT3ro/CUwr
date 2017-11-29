//
// Created by i300791 on 29.11.17.
//

#include <stdlib.h>
#include <stdio.h>


void merge(int *A, int *B, int p, int k) {
    if (p < k) {
        int mid = (p + k) / 2;
        merge(A, B, p, mid);
        merge(A, B, mid + 1, k);
        //scalanie
        int i = p, j = mid + 1, it = p;
        while (i <= mid || j <= k) {
            if (i > mid) {
                B[it++] = A[j++];
                continue;
            }
            if (j > k) {
                B[it++] = A[i++];
                continue;
            }
            if (A[i] <= A[j])
                B[it++] = A[i++];
            else
                B[it++] = A[j++];
        }
        for (int i = p; i <= k; ++i)
            A[i] = B[i];
    }
}

/// table, start_index, end_index
void mergeSort(int *A, int p, int k) {
    int *B = calloc(k, sizeof(int));
    merge(A, B, p, k);
    free(B);
}

int main() {
    printf("---MergeSort by Ttr\n");
    printf("Input n p k x_0 x_1 ... x_n-1\n");
    printf("n: length, p: start index, k: end index, x_0..x_n-1: table elements. Index starts at 0\n");

    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);

    int *tab = calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &tab[i]);

    mergeSort(tab, p, k);
    for (int i = 0; i < n; ++i)
        printf("%d ", tab[i]);

    printf("\n");
    return 0;
}