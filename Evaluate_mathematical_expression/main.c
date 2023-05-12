#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct Stack {
    double arr[MAX_SIZE];
    int top;
} Stack;

void push(Stack* stack, double num) {
    if(stack->top < MAX_SIZE - 1) {
        stack->arr[(stack->top)++] = num;
    } else {
        printf("Stack overflow. Can't push %lf onto the stack.\n", num);
        exit(1);
    }
}

double pop(Stack* stack) {
    if(stack->top != -1) {
        return stack->arr[(stack->top)--];
    } else {
        printf("Stack underflow. Can't pop from the stack.\n");
        exit(1);
    }
}

double peek(Stack* stack) {
    if(stack->top != -1) {
        return stack->arr[stack->top];
    } else {
        printf("Stack underflow. Can't peek the stack.\n");
        exit(1);
    }
}

int precedence(char operator) {
    switch(operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;  // Return 0 for other characters (like '.')
    }
}

void performOperation(Stack* stack, Stack* opStack) {
    if(stack->top < 1) {
        printf("Not enough operands for operation.\n");
        exit(1);
    }
    double num1 = pop(stack);
    double num2 = pop(stack);
    char operator = pop(opStack);
    switch(operator) {
        case '+':
            push(stack, num2 + num1);
            break;
        case '-':
            push(stack, num2 - num1);
            break;
        case '*':
            push(stack, num2 * num1);
            break;
        case '/':
            if(num1 != 0) {
                push(stack, num2 / num1);
            } else {
                printf("Error: Division by zero.\n");
                exit(1);
            }
            break;
        default:
            printf("Error: Invalid operator %c.\n", operator);
            exit(1);
    }
}

double calculate(const char* expression) {
    Stack stack;
    stack.top = -1;
    Stack opStack;
    opStack.top = -1;
    char currentToken[MAX_SIZE];
    int tokenIndex = 0;
    int exprLength = strlen(expression);

    for (int i = 0; i <= exprLength; i++) {
        char currentChar = expression[i];

        // Check if currentChar is a digit, a decimal point, or a negative sign followed by a digit or parenthesis
        if (isdigit(currentChar) || currentChar == '.' ||
            (currentChar == '-' && (isdigit(expression[i + 1]) || expression[i + 1] == '.' || expression[i + 1] == '('))) {
            currentToken[tokenIndex++] = currentChar;
            continue;
        }

        if (tokenIndex > 0) {
            currentToken[tokenIndex] = '\0';
            push(&stack, atof(currentToken));
            tokenIndex = 0;
        }

        if (strchr("+-*/", currentChar) != NULL) {
            while (opStack.top != -1 && precedence(peek(&opStack)) >= precedence(currentChar)) {
                if(stack.top >= 1) {
                    performOperation(&stack, &opStack);
                } else {
                    break;
                }
            }
            push(&opStack, currentChar);
        } else if (currentChar == '(') {
            push(&opStack, currentChar);
        } else if (currentChar == ')') {
            while (opStack.top != -1 && peek(&opStack) != '(') {
                if(stack.top >= 1) {
                    performOperation(&stack, &opStack);
                } else {
                    break;
                }
            }
            if(opStack.top != -1) {
                pop(&opStack); // Pop the '('
            } else {
                printf("Mismatched parentheses in expression.\n");
                exit(1);
            }
        } else if (currentChar != '\0' && currentChar != ' ') {
            printf("Error: Invalid character %c in expression.\n", currentChar);
            exit(1);
        }
    }

    while (opStack.top != -1) {
        if(stack.top >= 1) {
            performOperation(&stack, &opStack);
        } else {
            break;
        }
    }

    if(stack.top > 0) {
        printf("Invalid expression. Remaining operands in stack.\n");
        exit(1);
    }

    if(stack.top < 0) {
        printf("Not enough operands for operation.\n");
        exit(1);
    }

    return pop(&stack);
}

int main() {
	const char* expression = "2*(3+4)";
	double result = calculate(expression);
	printf("Result: %.21f\n", result);

	return 0;
}
