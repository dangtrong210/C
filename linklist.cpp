#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node;

typedef struct list{
	node *head=NULL;
	node *tail=NULL;
}list;

void init(list *l){
	l->head = l->tail=NULL;
}

node *create(int value){
	node *newnode = ((node*)malloc(sizeof(node)));
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}

void append(list *l, int value){
	node *newnode = create(value);
	if (l->head==NULL){
		l->head = l->tail= newnode;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}

void del(list *l, int value){
	node *p=l->head;
	node *q=NULL;
	while (p != NULL && value != p->data){
		q=p;
		p=p->next;
	}
	if (p==NULL){
		printf("Khong tim thay so can xoa\n");
	}else{
		if(p==l->head){
			l->head=p->next;
			if(l->head==NULL){
				l->tail=NULL;
			}
			free(p);
		}else{
			q->next=p->next;
			if (p->next==NULL){
				l->tail=q;
			}
			free(p);
		}
	}
}



int print(list *l){
	if (l->head==NULL){
		return 0;
	}
	node *p=l->head;
	while(p != NULL){
		printf("%d",p->data);
		p=p->next;
	}
}

int main (){
	list l;
	init(&l);
	int n, value, x;
	printf("Nhap vao so node: ");
	scanf("%d", &n);
	for (int i=0; i<n; i++){
		printf("Nhap so thu %d", i+1);
		scanf("%d",&value);
		append(&l,value);
	}
	
	printf("Nhap vao so can xoa: ");
	scanf("%d", &x);
	del(&l,x);
	
	print(&l);
	
	return 0;
}
