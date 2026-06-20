#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
}node;

typedef struct list{
	node *head;
	node *tail;
}list;

void init(list *l){
	l->head=l->tail=NULL;
}

node* create(int value) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}

void append(list *l, int value){
	node *newnode=create(value);
	if(l->head==NULL){
		l->head=l->tail=newnode;
	}else{
		l->tail->next=newnode;
		l->tail=newnode;
	}
}

node* find_middle(list *l) {
    if (l->head == NULL) return NULL;

    node* slow = l->head;
    node* fast = l->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }    
    return slow;
}

void print(list *l) {
	node *p=l->head;
    while (p != NULL) {
        printf("%d -> ",p->data );
        p = p->next;
    }
    printf("null\n");
}

int main() {
	int n,data;
	list l;
	init(&l);
	printf("Nhap so phan tu: ");
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		printf("Nhap phan tu thu %d: ",i);
		scanf("%d",&data);
		append(&l,data);
	}
	print(&l);
	node *mid = find_middle(&l);
	printf("Gia tri nut o giua la: %d",mid->data);
	return 0;
}
