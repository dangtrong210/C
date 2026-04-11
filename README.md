# MỘT SỐ THUẬT TOÁN CƠ BẢN TRONG C
## 1. Tìm kiếm:
1.1. Tìm kiếm tuyến tính:
````
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}
````
1.2. Tìm kiếm nhị phân:
````
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
````
