#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct node{
	char *data;
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

void push(stack *s,char *value){
	node *newnode=((node*)malloc(sizeof(node)));
	if (newnode==NULL||value==NULL){
		exit(0);
	}
	newnode->data = value;
	newnode->link=s->top;
	s->top=newnode;	
}

char *pop(stack *s){
	node *temp=s->top;
	char *pop=temp->data;
	s->top=temp->link;
	free(temp);
	return pop;
}

void print(stack *s){
	node *p=s->top;
	while(!empty(s)){
		s->top=p->link;
		printf("%s	",p->data);
		p=p->link;
	}
}

int kt(char *a, char *b){
	if(a!=NULL && b!=NULL){
		if (a=="(" && b==")") return 1;
		else if (a=="{" && b=="}") return 1;
		else if (a=="[" && b=="]") return 1;
	}
	return 0;
}

int kiemtra(stack *s, char *c){
	node *p=s->top;
	if (empty(s)){
		return 1;
	}
	if ((c=="("||c=="{"||c=="[") && (p->data!=")"||p->data!="}"||p->data!="]")){
		return 1;
	}else{
		char *top=pop(s);
		if(kt(top,c)==1){
			
		}
	}
	return 0;
}

int main(){
	int n;
	stack s;
	init (&s);
	printf("Nhap vao so ki tu: ");
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		fflush(stdin);
		char *c=(char*)malloc(sizeof(char));
		printf("Nhap vao ky tu thu %d: ",i);
		gets(c);
		if(kiemtra(&s,c)==1){
			push(&s,c);
		}
	}
	
	printf("Chuoi ban dau la: ");
	print(&s);
}
