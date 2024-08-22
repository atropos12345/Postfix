#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct StackNode {
	float data;
	struct StackNode* next;
} StackNode;

typedef struct {
	StackNode* top;
} Stack;

Stack* createStack() {
	Stack* stack = malloc(sizeof(Stack));
	stack->top = NULL;
	return stack;
}

void push(Stack* stack, float data) {
	StackNode* new_node = (StackNode*) malloc(sizeof(StackNode));
	new_node->data = data;
	new_node->next = stack->top;
	stack->top = new_node;
}

float pop(Stack* stack) {
	if (stack->top == NULL) {
		printf("Stack is Empty!\n");
		return -1.0;
	}
	float data = stack->top->data;
	StackNode* temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
	return data;
}

int isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

float evaluatePostfix(char* postfix) {
	Stack* stack = createStack();
	int i, len = strlen(postfix);
	for (i = 0; i < len; i++) {
		if (isdigit(postfix[i])) {
			float operand = 0;
			while (isdigit(postfix[i])) {
				operand = operand * 10.0 + (postfix[i] - '0');
				i++;
			}
			i--; // decrement i to compensate for the extra increment in the loop
			push(stack, operand);
		} else if (isOperator(postfix[i])) {
			float op2 = pop(stack);
			float op1 = pop(stack);
			switch (postfix[i]) {
			case '+':
				push(stack, op1 + op2);
				break;
			case '-':
				push(stack, op1 - op2);
				break;
			case '*':
				push(stack, op1 * op2);
				break;
			case '/':
				if (op2 == 0) {
					printf("Error: Division by zero\n");
					exit(EXIT_FAILURE);
				}
				push(stack, op1 / op2);
				break;
			}
		}
	}
	float result = pop(stack);
	free(stack);
	return result;
}

int main() {
	char postfix[100];
	printf("Enter the postfix expression: ");
	scanf(" %99[^\n]", postfix);
	float result = evaluatePostfix(postfix);
	printf("Result: %f\n", result);
	return 0;
}
