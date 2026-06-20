#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int getPrecedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* infix) {
    int n = strlen(infix);
    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = infix[i];
        if (isalnum(c)) {	//Neu la toan hang in ra truc tiep
            printf("%c", c);
        }
        else if (c == '(') {
            stack[++top] = c;
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                printf("%c", stack[top--]);
            }
            top--;
        }
        else {
            while (top != -1 && getPrecedence(stack[top]) >= getPrecedence(c)) {
                printf("%c", stack[top--]);
            }
            stack[++top] = c;
        }
    }
    while (top != -1) {
        printf("%c", stack[top--]);
    }
    printf("\n");
    free(stack);
}
int main(){
	stack s;
	init (&s);
	fflush(stdin);
	char *c=(char*)malloc(sizeof(char));
	printf("Nhap vao chuoi ky tu: ");
	gets(c);
	printf("Infix: %s -> Postfix: ",c);
    infixToPostfix(c);
	return 0;
}
