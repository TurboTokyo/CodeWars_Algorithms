#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct Node {
    double data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void push(Stack* stack, double num) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: could not allocate memory for new node\n");
        return;
    }

    newNode->data = num;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: stack underflow. Can't pop from the stack.\n");
        return -1; // or some other value to indicate an error
    }

    Node* topNode = stack->top;
    double data = topNode->data;
    stack->top = topNode->next;

    free(topNode);
    return data;
}

double peek(Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: stack is empty.\n");
        return -1;
    }

    return stack->top->data;
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

char* preprocess(const char* expression) {
    char* newExpression = malloc(strlen(expression) + 1);
    int j = 0;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '-' && expression[i + 1] == ' ') {
            newExpression[j++] = expression[i++];
            while (expression[i] == ' ') i++;
        }
        newExpression[j++] = expression[i];
    }
    newExpression[j] = '\0';
    return newExpression;
}

double parseNumber(const char** expression) {
    double result = 0.0;
    int decimalPlace = 0;

    while (isdigit(**expression) || **expression == '.') {
        if (**expression == '.') {
            if (decimalPlace) {  // if decimalPlace is not 0, we have already encountered a decimal point
                printf("Error: Invalid number with multiple decimal points\n");
                exit(EXIT_FAILURE);
            }
            decimalPlace = 1;
        } else {
            if (decimalPlace) {
                decimalPlace *= 10;
                result += ((double)**expression - '0') / decimalPlace;
            } else {
                result = result * 10.0 + (**expression - '0');
            }
        }
        (*expression)++;
    }

    return result;
}

double calculate(const char* expression) {
    Stack operandStack;
    operandStack.top = NULL;
    Stack operatorStack;
    operatorStack.top = NULL;

    int isUnaryMinus = 0;

    while (*expression) {
        if (isspace(*expression)) {
            // Ignore white spaces
            expression++;
            continue;
        }
        if (*expression == '(') {
            isUnaryMinus = 1;
            push(&operatorStack, '(');
        } else if (*expression == ')') {
            while (operatorStack.top > 0 && top(&operatorStack) != '(') {
                processOperation(&operandStack, &operatorStack);
            }
            if (operatorStack.top == 0 || top(&operatorStack) != '(') {
                printf("Error: Mismatched parentheses.\n");
                freeStack(&operandStack);
                freeStack(&operatorStack);
                exit(EXIT_FAILURE);
            }
            pop(&operatorStack); // Pop the '(' from the stack
            isUnaryMinus = 0;
        } else if (isdigit(*expression)) {
            double number = parseNumber(&expression);
            if (isUnaryMinus) {
                push(&operandStack, -number);
                isUnaryMinus = 0;
            } else {
                push(&operandStack, number);
            }
            expression--;
        } else if (isOperator(*expression)) {
            while (operatorStack.top > 0 && top(&operatorStack) != '(' &&
                   hasHigherPrecedence(top(&operatorStack), *expression)) {
                processOperation(&operandStack, &operatorStack);
            }
            if (*expression == '-' && (isUnaryMinus || operatorStack.top == 0 ||
                                       top(&operatorStack) == '(')) {
                isUnaryMinus = 1;
            } else {
                push(&operatorStack, *expression);
                isUnaryMinus = 0;
            }
        } else {
            printf("Error: Invalid character %c\n", *expression);
            freeStack(&operandStack);
            freeStack(&operatorStack);
            exit(EXIT_FAILURE);
        }
        expression++;
    }

    while (operatorStack.top > 0) {
        if (top(&operatorStack) == '(') {
            printf("Error: Mismatched parentheses.\n");
            freeStack(&operandStack);
            freeStack(&operatorStack);
            exit(EXIT_FAILURE);
        }
        processOperation(&operandStack, &operatorStack);
    }

    if (operandStack.top != 1) {
        printf("Error: Invalid expression.\n");
        freeStack(&operandStack);
        freeStack(&operatorStack);
        exit(EXIT_FAILURE);
    }

    double result = pop(&operandStack);
    return result;
}

int main() {
	const char* expression = "2*(3+4)";
	double result = calculate(expression);
	printf("Result: %.21f\n", result);

	return 0;
}
