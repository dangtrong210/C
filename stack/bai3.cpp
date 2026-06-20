#include <stdio.h>
#include <stdlib.h>

void findNextGreaterElements(int arr[], int n) {
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;
    
    // M?ng luu k?t qu?, kh?i t?o là -1 [cite: 21]
    int *result = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) result[i] = -1;

    for (int i = 0; i < n; i++) {
        // N?u ph?n t? hi?n t?i l?n hon ph?n t? t?i index trên d?nh stack
        while (top != -1 && arr[i] > arr[stack[top]]) {
            result[stack[top]] = arr[i]; // Tìm th?y NGE [cite: 20]
            top--; // Pop kh?i stack
        }
        // Push index hi?n t?i vào stack
        stack[++top] = i;
    }

    // In k?t qu?
    for (int i = 0; i < n; i++) {
        printf("NGE c?a %d là %d\n", arr[i], result[i]);
    }

    free(stack);
    free(result);
}

int main() {
    int arr[] = {4, 5, 2, 25}; // [cite: 24]
    int n = sizeof(arr) / sizeof(arr[0]);
    findNextGreaterElements(arr, n);
    return 0;
}
