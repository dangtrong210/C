#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

bool isValid(char* s) {
    int n = strlen(s);
    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];
        }
        else {
            if (top == -1 || !isMatchingPair(stack[top], s[i])) {
                free(stack);
                return false;
            }
            top--;
        }
    }
    bool result = (top == -1);
    free(stack);
    return result;
}
int main(){
	stack s;
	init (&s);
	fflush(stdin);
	char *c=(char*)malloc(sizeof(char));
	printf("Nhap vao chuoi ky tu: ");
	gets(c);
	printf("Chuoi %s: %s\n", c, isValid(c) ? "Hop le" : "Khong hop le");
	return 0;
}
