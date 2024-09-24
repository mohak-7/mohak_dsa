#include <stdio.h>
#include <stdlib.h>

// implementation of stack data structure in c
#define MAX 10

int stack[MAX];
int top = -1;

// to push an element into the stack
void push() {
    if (top == MAX - 1) {
        printf("Stack is full\n");
        return;
    }
    int data;
    printf("Enter the data to push\n");
    scanf("%d", &data);
    stack[++top] = data;
}

// to pop an element from the stack
void pop() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Popped element is %d\n", stack[top--]);
}

// to get the top element of the stack
int peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}

// to print the elements in the stack
void print_stack() {
        printf("Elements in the stack are: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
}

// to print the number of elements in the stack
void print_stack_size() {
    printf("Number of elements in the stack is %d\n", top + 1);
}

// to check if the stack is empty
void check_empty() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack is not empty\n");
    }
}

int main() {
    while(1) {
        char ch;
        printf("\nUse the following commands\n p : push,\n y : pop,\n q : quit,\n n : print the number of elements,\n i : check if the stack is empty\n\n");
        scanf(" %c", &ch);
        if (ch == 'p') {
            push();                 // push an element into the stack
        } else if (ch == 'y') {
            pop();                  // pop an element from the stack
        } else if (ch == 'q') {
            break;                 // quit the program
        } else if (ch == 'n') {
            print_stack_size();     // print the number of elements in the stack
            char temp;
            scanf(" %c", &temp);    // to hold the screen 
        } else if (ch == 'i') {
            check_empty();        // check if the stack is empty
            char temp;
            scanf(" %c", &temp);    // to hold the screen
        }
        system("clear");
        printf("\n\n\n");
        print_stack();           // print the elements in the stack
        
    }
}

