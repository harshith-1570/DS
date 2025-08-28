#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

float st[MAX];
int top = -1;

void push(float st[], float val);
float pop(float st[]);
float evaluatePostfixExp(char exp[]);

int main() {
    float val;
    char exp[100];

    printf("\nEnter any postfix expression (tokens separated by space): ");
    fgets(exp, sizeof(exp), stdin);

    val = evaluatePostfixExp(exp);
    printf("\nValue of the postfix expression = %.2f\n", val);

    return 0;
}

float evaluatePostfixExp(char exp[]) {
    int i = 0;
    float op1, op2, value;
    char token[20];
    int pos = 0;

    while (exp[i] != '\0') {
        if (isdigit(exp[i]) || (exp[i] == '-' && isdigit(exp[i + 1]))) {
            // Extract full number (support multi-digit and negative)
            pos = 0;
            while (isdigit(exp[i]) || exp[i] == '.' || exp[i] == '-') {
                token[pos++] = exp[i++];
            }
            token[pos] = '\0';
            push(st, atof(token));
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%') {
            op2 = pop(st);
            op1 = pop(st);
            switch (exp[i]) {
                case '+': value = op1 + op2; break;
                case '-': value = op1 - op2; break;
                case '*': value = op1 * op2; break;
                case '/':
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    value = op1 / op2;
                    break;
                case '%':
                    value = (int)op1 % (int)op2;
                    break;
            }
            push(st, value);
            i++;
        } else if (isspace(exp[i])) {
            i++; // skip whitespace
        } else {
            printf("Error: Invalid character '%c' in expression\n", exp[i]);
            exit(1);
        }
    }

    return pop(st);
}

void push(float st[], float val) {
    if (top == MAX - 1)
        printf("\nSTACK OVERFLOW\n");
    else
        st[++top] = val;
}

float pop(float st[]) {
    if (top == -1) {
        printf("\nSTACK UNDERFLOW\n");
        exit(1);
    } else
        return st[top--];
}

