#include <stdio.h>
#include <stdlib.h>

typedef struct dovat{
	char ten[10];
	int trongluong;
	int giatri;
	float dongia;
}dovat;

typedef struct node{
	dovat *data;
	struct node *next;
}node;

typedef struct list{
	node *head;
	node *tail;
}list;

void init(list *l){
	l->head=l->tail=NULL;
}


node *create(dovat *value){
	node *newnode = ((node*)malloc(sizeof(node)));
	if (newnode==NULL){
		exit(0);
	}
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}

void append(list *l, dovat *value){
	node *newnode=create(value);
	if(l->head==NULL){
		l->head=l->tail=newnode;
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
		if(p->data->dongia > pivot->data->dongia){
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

void daonguoc(list *l){
	node *prev=(node*)malloc(sizeof(node));
	node *cur=l->head;
	node *next=(node*)malloc(sizeof(node));
	while (cur!=NULL){
		next=cur->next;
		cur->next=prev;
		prev=cur;
		cur=next;
	}
}

void print(list *l){
	node *p=l->head;
	while(p!=NULL){
		printf("%s %d %d %.2f\n",p->data->ten,p->data->trongluong,p->data->giatri,p->data->dongia);
		p=p->next;
	}
}

void xuly(list *l, int max) {
    node *p = l->head;
    int tongGiaTri = 0;
    int conLai = max;
    while (p != NULL && conLai > 0) {
        int soluongdovat = conLai / p->data->trongluong;
        if (soluongdovat > 0) {
            conLai -= (soluongdovat * p->data->trongluong);
            tongGiaTri += (soluongdovat * p->data->giatri);
            
            printf("Lay %d do vat %s (Trong luong: %d, Gia tri: %d)\n", 
                    soluongdovat, p->data->ten, p->data->trongluong, p->data->giatri);
        }
        p = p->next;
    }
    printf("Tong gia tri lon nhat: %d\n", tongGiaTri);
    printf("Trong luong con du trong balo: %d\n", conLai);
}

int main(){
	int n,max;
	printf("Nhap so do vat: ");
	scanf("%d",&n);
	printf("Nhap trong luong toi da cua balo: ");
	scanf("%d",&max);
	list l;
	init(&l);
	for (int i=0; i<n; i++){
		dovat *value=((dovat*)malloc(sizeof(dovat)));
		fflush(stdin);
		printf("Nhap ten do vat: ");
			gets(value->ten);
		printf("Nhap trong luong: ");
			scanf("%d",&value->trongluong);
		printf("Nhap gia tri: ");
			scanf("%d",&value->giatri);
		value->dongia = (float)value->giatri / (float)value->trongluong;
		append(&l,value);
	}
	
	printf("\nDanh sach cac do vat:\n");
	print(&l);
	
	quicksort(&l);
	
	xuly(&l,max);
	
	
	daonguoc(&l);
	print(&l);
	return 0;
}
