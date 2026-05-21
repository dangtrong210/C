#include <stdio.h>
#include <stdlib.h>

int linearsearch(int *arr, int n, int x){
	for (int i=0; i<n; i++){
		if (x == *(arr + i)){
			return 1;
		}
	}
	return 0;
}

int binarysearch(int *arr,int n, int x){
	int left=0, right=n-1, mid = (left+right)/2;
	if (*(arr + mid)=x){
		return *(arr + mid);
	}
	if (*(arr + mid)<x){
		return binarysearch(arr + right, mid+1, x);
	}else{
		return binarysearch(arr + left, mid-1, x);
	}
	return 0;
}

void hoanvi(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void selectionsort(int *arr, int n){
	int min;
	for (int i=0; i<n; i++){
		min=i;
		for(int j=i+1; j<n; j++){
			if (*(arr + min)> *(arr + j)){
				min=j;
			}
		}
		hoanvi(arr + i,arr + min);
	}	
}

void insectionsort(int *arr, int n){
	int x,pos;
	for (int i=1; i<n; i++){
		x=*(arr + i);
		pos= i-1;
		while (pos>=0 && x < *(arr + pos)){
			*(arr + pos + 1)=*(arr + pos);
			pos--;
		}
		*(arr + pos + 1)=x;
	}
}

void interchangesort(int *arr, int n){
	for (int i=0; i<n; i++){
		for (int j=i+1; j<n; j++){
			if(*(arr + i) > *(arr + j)){
				hoanvi(arr + i,arr + j);
			}
		}
	}
}

void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                hoanvi((arr + j), (arr + j + 1));
            }
        }
    }
}

void print(int *arr, int n){
	for (int i=0; i<n; i++){
		printf("%d	", *(arr + i));
	}
}

int main(){
	int n,x;
	int *arr = ((int*)malloc(sizeof(int)));
	printf("Nhap so phan tu trong mang: ");
	scanf("%d", &n);
	for (int i=0; i<n; i++){
		printf("a[%d]: ", i);
		scanf("%d", arr + i);
	}
	//	selectionsort(arr,n);
	//	insectionsort(arr, n);
	//	interchangesort(arr, n);
		bubbleSort(arr,n);
	
	printf("Nhap vao gia tri can tim: ");
	scanf ("%d",&x);

	if (linearsearch(arr, n, x) != 0){
		printf("Trong mang co so %d\n", x);
	}else{
		printf("Trong mang khong co so can tim\n");
	}
	
	print(arr, n);

	free(arr);

	return 0;
}
