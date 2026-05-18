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
	struct node *link;
}node;
 
typedef struct stack{
	node *top;
}stack;
 
void init(stack *s){
	s->top=NULL;
}

int empty(stack *s){
	return s->top==NULL?1:0;
}

void push(stack *s,int n){
	for (int i=0; i<n; i++){
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
		newnode->link=s->top;
		s->top=newnode;	
	}
}

void print(stack *s){
	printf("MSSV	ho va ten	tuoi\n");
	node *p=s->top;
	while(!empty(s)){
		s->top=p->link;
		printf("%s	%s		%d\n",p->data->mssv,p->data->hoten,p->data->tuoi);
		p=p->link;
	}
}
int main(){
	int n, x;
	stack s;
	init (&s);
	printf("nhap so sv: ");
	scanf("%d",&n);
	push(&s,n);
	print(&s);

}
