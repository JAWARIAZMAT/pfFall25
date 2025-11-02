#include <stdio.h>
#define MAX_SIZE 5 //max stack size to check for overflow
int stack[MAX_SIZE];
int top = -1;  // means stack is initially empty


void showMenu() {
    printf("\n=== STACK OPERATIONS ===\n");
    printf("1. PUSH (Add element)\n");
    printf("2. POP (Remove element)\n");
    printf("3. PEEK (View top element)\n");
    printf("4. DISPLAY (Show all elements)\n");
    printf("5. EXIT\n");
}


void push() {
    int value;
    
    if(top >= MAX_SIZE - 1) {    //If MAX_SIZE = 5, valid indices are: 0, 1, 2, 3, 4
        printf("STACK OVERFLOW!\n");
        return;
    }
    
    printf("Enter element to push: ");
    scanf("%d", &value);
    
    top++;  
    stack[top] = value;  // Insert element
    printf("? Element %d pushed successfully!\n", value);
}


void pop() {
    
    if(top == -1) {
        printf("STACK UNDERFLOW!\n");
        return;
    }
    
    int poppedValue = stack[top];  // Get the top element
    top--;
    printf("? Element %d popped successfully!\n", poppedValue);
}


void peek() {
    // Check if stack is empty
    if(top == -1) {
        printf("? Stack is empty! No element to peek.\n");
        return;
    }
    
    printf("?? Top element is: %d\n", stack[top]);
}


void display() {
    if(top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf(" Stack elements from top to bottom:\n");
    printf("TOP->");
    
    // Display from top to bottom
    for(int i = top; i >= 0; i--) {
        printf("[%d]", stack[i]);
        if(i > 0) {
            printf("->");
        }
    }
    printf("\n");
}

int main() {
    int choice;
    
    printf("=== STACK OPERATIONS===\n");
    
    do {
        showMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch(choice) {
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
                printf("Invalid choice! Please enter 1-5.\n");
        }
    } while(choice != 5);
    
    return 0;
}