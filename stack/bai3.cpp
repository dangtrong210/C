#include <stdio.h>
#include <stdlib.h>

void findNGE(int arr[], int n) {
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;
    int *result = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) result[i] = -1;

    for (int i = 0; i < n; i++) {
        while (top != -1 && arr[i] > arr[stack[top]]) {
            result[stack[top]] = arr[i];
            top--;
        }
        stack[++top] = i;
    }

    printf("\nKet qua:\n");
    for (int i = 0; i < n; i++) {
        printf("NGE cua %d la %d\n", arr[i], result[i]);
    }

    free(stack);
    free(result);
}

int main() {
    int n;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Nhap %d phan tu:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findNGE(arr, n);

    free(arr);
    return 0;
}
