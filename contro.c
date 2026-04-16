#include <stdio.h>
int main() {
    int a = 5;
    int *p;
    p = &a; // Gán địa chỉ của biến a cho con trỏ p
    *p = 10; // Thay đổi giá trị của a thông qua con trỏ p
    printf("Value of a: %d\n", a); // In ra giá trị của a sau khi thay đổi qua con trỏ
    return 0;
}