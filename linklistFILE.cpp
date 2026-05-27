#include <stdio.h>
#include <stdlib.h>

typedef struct sinhvien{
	char mssv[20];
	char hoten[50];
	int gpa;
}sinhvien;

typedef struct node {
	sinhvien *data;
	struct node *next;
}node;

typedef struct list {
	node *head;
	node *tail;
}list;

void init(list *l){
	l->head=l->tail=NULL;
}

node *create(sinhvien *value){
	node *newnode=((node*)malloc(sizeof(node)));
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}

void append(list *l, sinhvien *value){
	node *newnode=create(value);
	if (l->head==NULL){
		l->head=newnode;
		l->tail=newnode;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}

void noilist(list *l1, list *l2){
	if(l2->head==NULL){
		return;
	}
	if (l1->head==NULL){
		l1->head=l2->head;
		l1->tail=l2->tail;
	}else{
		l1->tail->next=l2->head;
		l1->tail=l2->tail;
	}
}

void quicksort(list *l){
	if (l->head == NULL || l->head->next == NULL){
        return;
    }
	list l1, l2;
	init (&l1);
	init (&l2);
	node *pivot=l->head;
	node *p=pivot->next;
	pivot->next=NULL;
	while (p != NULL){
		node *nodenext=p->next;
		p->next=NULL;
		if(p->data->gpa > pivot->data->gpa){
			append(&l1,p->data);
		}else{
			append(&l2,p->data);
		}
		p=nodenext;
	}
	quicksort(&l1);
	quicksort(&l2);
	
	init(l);
	
	noilist(l,&l1);
	append(l, pivot->data);
	noilist(l,&l2);
}

void xuly(list *l, FILE *ptr){
	ptr=fopen("arr1.txt","w");
	node *p=l->head;
	while(p!=NULL){
		fprintf(ptr,"%s %s %d\n",p->data->mssv,p->data->hoten,p->data->gpa);
		p=p->next;
	}
	fclose(ptr);
}

void del(list *l, const char *value, FILE *ptr){
	node *p=l->head;
	node *q;
	if (l==NULL) return;
	while(atoi(value) != atoi(p->data->mssv)){
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("Khong co sinh vien can xoa");
	}else{
		if(p==l->head){
			l->head=q;
			free(p->data);
			free(p);
		}else{
			q->next=p->next;
			if (p==l->tail){
				q=l->tail;
			}
			free(p->data);
			free(p);
		}
	}
	xuly(l,ptr);
}

void print(list *l){
	node *p=l->head;
	while(p!=NULL){
		printf("%s	%s	%d\n",p->data->mssv,p->data->hoten,p->data->gpa);
		p=p->next;
	}
}

int main(){
	int n,m;
	char x[20];
	list l;
	init(&l);
	printf("Nhap so sinh vien: ");
	scanf("%d",&n);
	
	FILE *ptr;
	ptr=fopen("arr.txt","w");
	sinhvien *value=((sinhvien*)malloc(sizeof(sinhvien)));
	for (int i=0; i<n; i++){
		fflush(stdin);
		printf("Nhap mssv thu %d: ",i+1);
		gets(value->mssv);
		fflush(stdin);
		printf("Nhap ho va ten: ");
		gets(value->hoten);
		printf("Nhap diem: ");
		scanf("%d",&value->gpa);
		
		fprintf(ptr,"%s %s %d\n",value->mssv,value->hoten,value->gpa);
	}
	fclose(ptr);
	
	ptr=fopen("arr.txt","r");
	for (int i=0; i<n; i++){
		sinhvien *value=((sinhvien*)malloc(sizeof(sinhvien)));
		fscanf(ptr,"%s %s %d",&value->mssv,&value->hoten,&value->gpa);
		append(&l,value);
	}
	fclose(ptr);
	
	quicksort(&l);
	
	fflush(stdin);
	printf("Nhap mssv can xoa: ");
	gets(x);
	del(&l,x,ptr);
	
	print(&l);
}
