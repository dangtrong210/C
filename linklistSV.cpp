#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct sinhvien{
	char mssv[50];
	char hoten[50];
	int tuoi;
}sinhvien;

typedef struct node{
	sinhvien *data;
	struct node *next;
}node;
 
typedef struct list{
	node *head;
	node *tail;
}list;
 
list *init(list *l){
	l->head=l->tail=NULL;
	return l;
}
 
node *create(){
	node *newnode=((node*)malloc(sizeof(node)));
	sinhvien *value=((sinhvien*)malloc(sizeof(sinhvien)));
	if (newnode==NULL||value==NULL){
		exit(0);
	}
	fflush(stdin);
	printf("Nhap mssv: ");
	gets(value->mssv);
	printf("nhap ho va ten: ");
	gets(value->hoten);
	printf("nhap tuoi: ");
	scanf("%d",&value->tuoi);
	printf("\n");
	newnode->data = value;
	newnode->next=NULL;

	return newnode;
}
 
void addhead(list *l,node *newnode){
	if (l->head==NULL){
		l->head=newnode;
		l->tail=newnode;
	}else{	
		newnode->next=l->head;
		l->head=newnode;
	}
}
 
void addtail(list *l, node *newnode){
	if (l->head==NULL){
		l->head=newnode;
		l->tail=newnode;
		newnode->next=NULL;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}

void interchange (list *l,int n){
	sinhvien *tam;
	for (node *p=l->head;p!=l->tail;p=p->next){
		for(node *q=p->next;q!=NULL;q=q->next){
			if(atoi(p->data->mssv) > atoi(q->data->mssv)){
				tam=p->data;
				p->data=q->data;
				q->data=tam;
			}
		}
	}
}

void noilist(list *l1, list *l2) {
    if (l2->head == NULL) return;
    if (l1->head == NULL) {
        l1->head = l2->head;
        l1->tail = l2->tail;
    } else {
        l1->tail->next = l2->head;
        l1->tail = l2->tail;
    }
    init(l2);
}

void quicksort(list *l) {
    if (l->head == NULL) {
        return;
    }

    list *l1, *l2;
    l1= init(l1);
    l2= init(l2);

    node *pivot = l->head;
    node *p = pivot->next;
    pivot->next = NULL;

    while (p != NULL) {
        node *next_node = p->next;
        p->next = NULL;

        if (atoi(p->data->mssv) < atoi(pivot->data->mssv)) {
            l1= addtail(l1, p);
        } else {
            l2= addtail(l2, p);
        }
        
        p = next_node;
    }

    quicksort(l1);
    quicksort(l2);

    l= init(l);
    
    noilist(l, &l1);
    addtail(l, pivot);
    noilist(l, &l2);
}

void append(list *l,int n){
	for(int i=0;i<n;i++){
		node *p=create();
		addhead(l,p);
	}
	quicksort(l);
}

list *del(list *l, const char *x){
	node *p=l->head;
	node *q;
	if (l==NULL) return l;
	while(atoi(p->data->mssv) != atoi(x)){
		q=p;
		p=p->next;
	}
	if(p==NULL){
		printf("ko tim thay sv");
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
	return l;
}

void print(list *l){
	printf("MSSV	ho va ten	tuoi\n");
	node *p;
	p=l->head;
	while(p!=NULL){
		printf("%s	%s		%d\n",p->data->mssv,p->data->hoten,p->data->tuoi);
		p=p->next;
	}
}

int main(){
	int n,m;
	char x[20];
	list *l;
	init (l);
	printf("nhap so sv: ");
	scanf("%d",&n);
	l= append(l,n);
	print(l);
	
	printf("Nhap so sinh vien can xoa: ");
	scanf("%d",&m);
	for (int i=0; i<m; i++){
		fflush(stdin);
		printf("nhap mssv thu %d can xoa: ",i+1);
		gets(x);
		l= del(l,x);
		printf("dssv sau khi xoa\n");
		print(l);
	}
	return 0;
}

