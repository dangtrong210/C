#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#define TRUE 1
#define FALSE 0
#define NULLKEY -1
#define M 10
//Khai bao cau truc mot nut cua bang bam
struct node
{
	int key;	//khoa cua nut tren bam
};

//Khai bao bang bam co M nut
struct node hashtable[M];
int N;	//bien toan cuc chi so nut hien co tren bang bam

//ham bam
int hashfunc(int key)
{
	return(key % M);
}

//ham bam thu hai
int hashfunc2(int key)
{
	return (M-(key%M));
}
//Khoi dong bang bam
void initialize()
{
	int i;
	for(i=0;i<M;i++)
		hashtable[i].key = NULLKEY;
	N=0;	// so nut hien co khoi dong bang 0
}

//Tac vu empty : kiem tra ca bang bam co rong hay khong
int empty()
{
	return (N==0 ? TRUE : FALSE);
}

//Tac vu full : kiem tra bang bam co day chua
int full()
{
	return (N==M-1 ? TRUE : FALSE);
}
//Tac vu search : tim kiem nut co khoa k tren bang bam
int search(int k)
{
	int i,j;
	i=hashfunc(k);
	j=hashfunc2(k);
	while(hashtable[i].key!=k && hashtable[i].key!=NULLKEY)
		//bam lai(theo phuong phap bam kep
		i=(i+j)%M;
	if(hashtable[i].key==k)	//tim thay
		return(i);
	else
		return(M);

}

//tac vu insert : them nut co khoa k vao bang bam
int insert(int k)
{
	int i,j;
	if(full())
	{
		printf("Bang bam bi day khong the them nut co khoa %d duoc",k);
		return(M);
	}
	if(search(k)<M)
	{
		printf("So nay da co trong bang bam");
		return(M);
	}
	i=hashfunc(k);
	j=hashfunc2(k);
	while(hashtable[i].key!=NULLKEY)
		//bam lai theo phuong phap tuyen tinh
		i=(i+j)%M;
	hashtable[i].key=k;
	N=N+1;
	return(i);
}
//tac vu remove : xoa nut tai dia chi i tren bang bam
void remove(int i)
{
	int j, r, h, cont, a;
	cont= TRUE;

	do
	{
		h = hashfunc2(hashtable[i].key);
		hashtable[i].key=NULLKEY;
		j=i;
	   do
	   {
		i=(i+h)%M;
		if(hashtable[i].key==NULLKEY)
			cont=FALSE;
		else
		{
			r=hashfunc(hashtable[i].key);
			a=(j<r && r<=i) || (r<=i && i<j) || (i<j && j<r);
		}
	     }while (cont && a);
	     if(cont)
		 hashtable[j].key=hashtable[i].key;

	}while(cont);

}
//tac vu viewtable : xem chi tiet bang bam
void viewtable()
{
	int i;
	for(i=0;i<M;i++)
		printf("\nTable[%2d] : %4d\t",i,hashtable[i].key);
}
//chuong trinh chinh
int main()
{
	int i,n,p,q;
	int b, key, chucnang;
	char c;
	//khoi tao bang bam
	initialize();
	do
	{
		//menu chinh cua chuong tinh
		printf("\t\n\nCac chuc nang chinh cua chuong trinh : \n");
		printf("\t1.Them nut moi vao bang bam\n");
		printf("\t2.Them ngau nhien mot nut vao bang bam\n");
		printf("\t3.Xoa nut tren bang bam\n");
		printf("\t4.Xoa toan bo bang bam\n");
		printf("\t5.Xem chi tiet bang bam\n");
		printf("\t6.Tim kiem tren bang bam\n");
		printf("\t0.Ket thuc chuong trinh\n");
		printf("\tChuc nang ban chon : ");
		scanf("%d",&chucnang);
		switch(chucnang)
		{
		case 1:
			{
				printf("\nThem nut vao bang bam ");
				printf("\nKhoa cua nut moi : ");
				scanf("%d", &key);
				insert(key);
				break;
			}
		case 2:
			{
				srand(time(NULL));
				printf("\nThem ngau nhien nhieu nut vao bang bam");
				printf("\nBan muon them bao nhieu nut : ");
				scanf("%d", &n);
				for(i=0;i<n;i++)
				{
					key=rand()%(100);
					insert(key);
				}
				break;
			}
		case 3:
			{
				printf("\nXoa nut tren bang bam");
				printf("\nkhoa cua nut can xoa : ");
				scanf("%d", &key);
				i=search(key);
				if(i==M)
					printf("Khong co nut voi khoa can xoa");
				else
				{
					remove(i);
					N--;
				}
				break;
			}
		case 4:
			{
				printf("\nXoa toan bo bang bam");
				printf("\nBan co chat khong (c/k) : ");
				c=getch();
				if(c=='c'||c=='C')
					initialize();
				break;
			}
		case 5:
			{
				printf("\nXem chi tiet bang bam");
				viewtable();
				break;
			}
		case 6: 
			{
				printf("Tim kiem tren bang bam");
				printf("Khoa can tim : ");
				scanf("%d", &key);
				if(search(key)==M)
					printf("\nKhong tim thay");
				else
				{
					printf("Tim thay tai dia chi %d trong bang bam",search(key));
					break;
				}
			}
		     }
	}while(chucnang!=0);
}
