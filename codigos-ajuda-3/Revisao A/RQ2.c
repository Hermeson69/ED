#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n, int *cont);

int main() {
    int T, N;

  
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
      
        scanf("%d", &N);
        int arr[N];

        
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }

        int cont = 0;
        selectionSort(arr, N, &cont);

        printf("%d\n", cont);
    }

    return 0;
}

void selectionSort(int arr[], int n, int *cont) {
    int i, j, min_idx;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if ((arr[i] != arr[min_idx])) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
            (*cont)++;
        }
    }
}