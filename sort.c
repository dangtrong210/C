#include <stdio.h>
#include <stdlib.h>

void hoanvi(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void printArray(int arr[],int n){
    for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void seclectionSort(int arr[],int n){
    for (int i=0;i<n;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(arr[min]>arr[j]){
                min=j;
            }
        }
    hoanvi(&arr[min],&arr[i]);
    }
}

void insertionSort(int arr[],int n){
    for (int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void interchangeSort(int arr[],int n){
    for (int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                hoanvi(&arr[i],&arr[j]);
            }
        }
    }
}

void bubbleSort(int arr[],int n){
    for (int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                hoanvi(&arr[j],&arr[j+1]);
            }
        }
    }
}

int main(){
    int n, arr[n];
    printf("Nhap vao so phan tu trong mang: ");
    scanf("%d",&n);

    for (int i=0;i<n;i++){
        printf("arr[%d]: ",i);
        scanf("%d",&arr[i]);
    }
    printf("Mang truoc khi sap xep: ");
    printArray(arr, n);
    printf("\n");

    seclectionSort(arr,n);  //Có thể thay thế bằng insertionSort(arr,n), interchangeSort(arr,n) hoặc bubbleSort(arr,n)
    printf("Mang sau khi sap xep: ");
    printArray(arr, n);
    
    return 0;
}