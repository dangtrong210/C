#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct node{
	char data;
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

void push(stack *s,char value){
	node *newnode=((node*)malloc(sizeof(node)));
	if (newnode==NULL||value==NULL){
		exit(0);
	}
	newnode->data = value;
	newnode->link=s->top;
	s->top=newnode;	
}

char pop(stack *s){
	if (empty(s)){
		return '\0';
	}
	node *temp = s->top;
	char value=temp->data;
	s->top=s->top->link;
	free(temp);
	return value;
}

void print(stack *s){
	node *p=s->top;
	while(p!=NULL){
		printf("%c",p->data);
		p=p->link;
	}
}

int kiemtra(stack *s, char *t,int n){
	for (int i=0; i<n;i++){
		char c = *(t + i);
		if (c=='('||c=='{'||c=='['){
			push(s,c);
		}else{
			if(c==')'||c=='}'||c==']'){
				if (empty(s)){
					return 0;
				}
				char open=pop(s);
				if (!((open=='(' && c==')') || (open=='{' && c=='}') || (open=='[' && c==']'))){
					return 0;
				}
			}
		}
	}
	return empty(s);
}

int main(){
	stack s;
	init (&s);
	fflush(stdin);
	char *c=(char*)malloc(sizeof(char));
	printf("Nhap vao chuoi ky tu: ");
	gets(c);
	if (kiemtra(&s,c,strlen(c))==0){
		printf("Chuoi %s ko hop le",c);
	}else{
		printf("Chuoi %s hop le",c);
	}
	return 0;
}
