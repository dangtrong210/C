#include <stdio.h>
#include <stdlib.h>

int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int l, int r, int y) {
    while (l <= r) {
        int m = (l + (r - l)) / 2;
        if (arr[m] == y) {
            return m;
        }
        if (arr[m] < y ) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}

int main(){
    int n, arr[n], x;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter %d elements:\n", i);
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search for: ");
    scanf("%d", &x);

    if (linearSearch(arr, n, x) != -1) {
        printf("Element found at x: %d\n",linearSearch(arr, n, x));
    } else {
        printf("Element not found in the array.\n");
    }


    printf("\n Arrays for binary search:\n");
    int arr2[n],y;
    for (int i = 0; i < n; i++) {
        printf("Enter %d elements in sorted order:\n", i);
        scanf("%d", &arr2[i]);
    }
    printf("Enter the element to search for: ");
    scanf("%d",&y);
    if (binarySearch(arr2, 0, n - 1, y) != -1) {
        printf("Element found at y: %d\n", binarySearch(arr2, 0, n - 1, y));
    } else {
        printf("Element not found in the array.\n");
    }
    return 0;
}