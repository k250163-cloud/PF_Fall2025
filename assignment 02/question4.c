#include <stdio.h>

#define MAX_SIZE 5

int stack[MAX_SIZE];
int top = -1;

void push() {
    if (top == MAX_SIZE - 1) {
        printf("stack1 is overflow Cannot push element.\n");
        return;
    }
   
    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);
   
    top++;
    stack[top] = value;
    printf("Element  pushed \n");
}

void pop() {
    if (top == -1) {
        printf("stack undr flow Cannot pop element.\n");
        return;
    }
   
    printf("Element popped \n");
    top--;
}

void peek() {
    if (top == -1) {
        printf("Stack is empty! No top element.\n");
        return;
    }
   
    printf("top element is: %d\n", stack[top]);
}
void display() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements from top to bottom: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void showMenu() {
    printf("stack operations\n");
    printf("1. push\n");
    printf("2. pop\n");
    printf("3. peek\n");
    printf("4. Display\n");
    printf("5. exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
   
    printf("Stack Implementation slect choice: push(1) pop(2), peek(3), display(4), exit program(5)\n");
    printf("Maximum stack size: %d\n", MAX_SIZE);
   
    do {
        showMenu();
        scanf("%d", &choice);
       
        switch (choice) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter between 1-5.\n");
        }
    } while (choice != 5);
   
    return 0;
}
