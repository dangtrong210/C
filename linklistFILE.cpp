#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}node;

typedef struct list {
	node *head;
	node *tail;
}list;

void init(list *l){
	l->head=l->tail=NULL;
}

node *create(int value){
	node *newnode=((node*)malloc(sizeof(node)));
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}

void append(list *l, int value){
	node *newnode=create(value);
	if (l->head==NULL){
		l->head=newnode;
		l->tail=newnode;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}
void del(list *l, int value){
	node *p=l->head;
	node *q;
	if (l==NULL) return;
	while(value != p->data){
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("Khong co so can xoa");
	}else{
		if(p==l->head){
			l->head=q;
			free(p);
		}else{
			q->next=p->next;
			if (p==l->tail){
				q=l->tail;
			}
			free(p);
		}
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
		if(p->data < pivot->data){
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
		fprintf(ptr,"%d	",p->data);
		p=p->next;
	}
	fclose(ptr);
}

void del(list *l, int value, FILE *ptr){
	node *p=l->head;
	node *q;
	if (l==NULL) return;
	while(value != p->data){
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("Khong co so can xoa");
	}else{
		if(p==l->head){
			l->head=q;
			free(p);
		}else{
			q->next=p->next;
			if (p==l->tail){
				q=l->tail;
			}
			free(p);
		}
	}
	xuly(l,ptr);
}

void print(list *l){
	node *p=l->head;
	while(p!=NULL){
		printf("%d	",p->data);
		p=p->next;
	}
}

int main(){
	int n,m,x, value;
	list l;
	init(&l);
	printf("Nhap so phan tu trong danh sach: ");
	scanf("%d",&n);
	
	FILE *ptr;
	ptr=fopen("arr.txt","w");
	for (int i=0; i<n; i++){
		printf("Nhap phan tu thu %d: ",i+1);
		scanf("%d",&value);
		fprintf(ptr,"%d ",value);
	}
	fclose(ptr);
	
	ptr=fopen("arr.txt","r");
	for (int i=0; i<n; i++){
		fscanf(ptr,"%d",&value);
		append(&l,value);
	}
	fclose(ptr);
	
	quicksort(&l);
	
	printf("Nhap vao gia tri can xoa: ");
	scanf("%d",&x);
	del(&l,x,ptr);
	
	print(&l);
}
