#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define M 26


typedef struct tudien
{
	char tu[10];
	char nghia[100];
}tudien;
typedef struct node
{
	tudien data;
	node *link;
}node;
node bucket[M];
int hambam(char tu[])
{
	char ch;
	ch=toupper(tu[0]);
	return ((ch-65)%M);
}
void khoitao(node bucket[])
{
	int i;
	for(i=0;i<M;i++)
	bucket[i].link=NULL;
}
void themtu(tudien x)
{
	node *p;int i;
	i=hambam(x.tu);
	p=new (node);
	p->data=x;
	p->link=bucket[i].link;
	bucket[i].link=p;
}
node *timtu(char tu[])
{
	int tim=1;
	int i=hambam(tu);
	node *p=bucket[i].link;
	while((tim==1)&&(p!=NULL))
	{
		if(strcmp(p->data.tu,tu)==0)
			tim=0;
		else
			p=p->link;
	}
	if(tim==0)
		return p;
	else
		return NULL;
}
int kiemtra(char tu[])
{
	int tim=1;
	int i=hambam(tu);
	node *p=bucket[i].link;
	while((tim==1)&&(p!=NULL))
	{
		if(strcmp(p->data.tu,tu)==0)
			tim=0;
		else
			p=p->link;
	}
	if(tim==0)
		return 1;
	else
		return 0;
}


void khoi_tao()
{
		printf("\nCHUONG TRINH TU DIEN \n");
		printf("\n1.Them mot tu moi");
		printf("\n2.Tra tu ");
		printf("\n3.In tu dien ");
		printf("\n4.Xoa tu ");
		printf("\n5.Ghi tu dien vao file");
		printf("\n6.Doc file vao tu dien ");
		printf("\n7.Thoat");
		printf("\nChon chuc nang : ");
}
void intudien()
{
	int i;  node *p;
	for(i=0;i<M;i++)
	{
		p=bucket[i].link;
		printf("\nDanh muc tu %c :",i+65);
		while(p!=NULL)
		{ printf("\n Tu : %s  nghia : %s ",p->data.tu,p->data.nghia);
		  p=p->link;
		}

	}
}
void xoatu(char tu[])
{
	int i;node *p,*q;
	i=hambam(tu);
	p=bucket[i].link;
	while((p!=NULL)&&(strcmp(p->data.tu,tu)!=0))
	{
		q=p;
		p=p->link;
	 }
	if(p==NULL)
		printf("\ntu tren khong co trong tu dien ");
	else
		if(p==bucket[i].link)
		{
			bucket[i].link=p->link;
			delete(p);
		}
		else
		{
			q->link=p->link;
			delete(p);
		}
      }
void ghifile(char *filename)
{       FILE *f;
	int i;  node *p;
	f=fopen(filename,"wb");
	for(i=0;i<M;i++)
	{
		p=bucket[i].link;
		while(p!=NULL)
		{ fwrite(&p->data,sizeof(p->data),1,f);
		  p=p->link;
		}
	}
	fclose(f);
}
void docfile(char *filename)
{       FILE *f;
	tudien tam;
	f=fopen(filename,"rb");
	while(!feof(f))
	 {
	 fread(&tam,sizeof(tam),1,f);
	 if(kiemtra(tam.tu)==0) themtu(tam);

	}
	fclose(f);
}

int main()
{
		int chon;tudien x;char ch[10];node *p;int t;
docfile((char *)"e:\\tudien.txt");
       nhan:
       khoi_tao();
       scanf("%d",&chon);
		if(chon==7)
			{
			ghifile((char *)"e:\\tudien.txt");
			exit(1);
			}
		switch(chon)
		{
			case 1:
			{
				printf("\nBan muon them bao nhieu tu ?");
				scanf("%d",&t);
				for(int i=0;i<t;i++)
				{
					printf("\nNhap tu moi thu %d : ",i+1);
					fflush(stdin);gets(x.tu);
					if(kiemtra(x.tu)==1)
					 printf("\n Tu: %s da co trong tu dien");
					else
					{
					printf("\nNhap nghia cua tu: ");
					fflush(stdin);gets(x.nghia);
					themtu(x);
					}				}
				printf("\n Nhan phim bat ky de tiep tuc!");
				getch();
				break;
			}
			case 2:
			{
				printf("\nNhap tu can tra ");
				fflush(stdin);
				gets(ch);
				p=timtu(ch);
				if(p!=NULL)
					printf("\nTu : %s co nghia la :%s",p->data.tu,p->data.nghia);
				else
					printf("tu tren khong co trong tu dien");getch();
				printf("\n Nhan phim bat ky de tiep tuc!");
				getch();
				break;

			}
			case 3:
				intudien();
				printf("\n Nhan phim bat ky de tiep tuc!");
				getch();
				break;
			case 4:
			{
				printf("\nNhap tu can xoa : ");
				fflush(stdin);
				gets(ch);
				xoatu(ch);
				break;
			}
			case 5:
				ghifile((char *)"e:\\tudien.txt");
				printf("\n Nhan phim bat ky de tiep tuc!");
				getch();
				break;
			case 6:
				docfile((char *)"e:\\tudien.txt");
				printf("\n Nhan phim bat ky de tiep tuc!");
				getch();
				break;

	 }
	 goto nhan;
}	
