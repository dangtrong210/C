#include <stdio.h>
#include <stdlib.h>

typedef struct hanghoa{
	char mahg[10];
	char tenhg[10];
	int solg;
	int dongia;
	int thanhtien;
}hanghoa;

typedef struct node{
	hanghoa *data;
	struct node *next;
}node;

typedef struct list{
	node *head;
	node *tail;
}list;

void init(list *l){
	l->head=l->tail=NULL;
}

node *create(hanghoa *value){
	node *newnode=(node*)malloc(sizeof(node));
	if(newnode!=NULL){
		newnode->data=value;
		newnode->next=NULL;
	}
	return newnode;
}

void append(list *l, hanghoa *value){
	node *newnode=create(value);
	if (l->head==NULL){
		l->head=l->tail=newnode;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}

void print(list *l){
	node *p=l->head;
	printf("Danh sach hang hoa\n");
	printf("---------------------------------------------------------\n");
	printf("|STT	|Mahg	|Tenhg		|Solg	|Dongia	|Thanhtien	|\n");
	
	int i=1;
	while(p!=NULL){
		printf("|%d	|%s	|%s	|%d	|%d	|%d		|\n",i,p->data->mahg,p->data->tenhg,p->data->solg,p->data->dongia,p->data->thanhtien);
		p=p->next;
		i++;
	}
	printf("---------------------------------------------------------");
}

int main(){
	int n;
	list l;
	init(&l);
	printf("Nhap so hang: ");
	scanf("%d",&n);
	for (int i=0; i<n;i++){
		hanghoa *value=(hanghoa*)malloc(sizeof(hanghoa));
		fflush(stdin);
		printf("Nhap ma hang: ");
		gets(value->mahg);
		printf("Nhap ten hang: ");
		gets(value->tenhg);
		printf("Nhap so luong: ");
		scanf("%d",&value->solg);
		printf("Nhap don gia: ");
		scanf("%d",&value->dongia);
		value->thanhtien=value->solg*value->dongia;
		append(&l,value);	
	}
	print(&l);
}
