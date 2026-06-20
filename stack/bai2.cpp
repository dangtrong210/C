#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// C?u trúc Stack
struct Stack {
    int top;
    int capacity;
    char *array;
};

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) { return stack->top == -1; }
char peek(struct Stack* stack) { return stack->array[stack->top]; }
void push(struct Stack* stack, char op) { stack->array[++stack->top] = op; }
char pop(struct Stack* stack) { 
    if (!isEmpty(stack)) return stack->array[stack->top--]; 
    return '$'; 
}

// Xác d?nh d? uu tiên
int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}

void infixToPostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));

    for (int i = 0; exp[i]; ++i) {
        if (isalnum(exp[i])) {
            printf("%c", exp[i]);
        } 
        else if (exp[i] == '(') {
            push(stack, exp[i]);
        } 
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                printf("%c", pop(stack));
            pop(stack); // Xóa '('
        } 
        else { // Toán t?
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(exp[i])) {
                printf("%c", pop(stack));
            }
            push(stack, exp[i]);
        }
    }
    while (!isEmpty(stack)) printf("%c", pop(stack));
    printf("\n");
}

int main() {
    char exp1[] = "A+B*C";
    char exp2[] = "(A+B)*C";
    
    printf("Infix: %s -> Postfix: ", exp1);
    infixToPostfix(exp1);
    
    printf("Infix: %s -> Postfix: ", exp2);
    infixToPostfix(exp2);
    
    return 0;
}
