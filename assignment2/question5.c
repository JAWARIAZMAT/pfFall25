#include <stdio.h>
#include <string.h>

#define MAX_MESSAGE 1000
void displayMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Encode Message\n");
    printf("2. Decode Message\n");
    printf("3. Exit\n");
}


void reverseString(char str[]) {
    int length = strlen(str);
    for(int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}


char toggleBits(char ch) {
    // Toggle 2nd bit (bit position 1) and 5th bit (bit position 4)
      
    int bit1_mask = 2;  
    int bit4_mask = 16;  
    
    ch = ch ^ bit1_mask;  
    ch = ch ^ bit4_mask;  
    
    return ch;
}

void encodeMessage(char message[]) {
    printf("\n=== ENCODING PROCESS ===\n");
    printf("Original message: %s\n", message);
    
    reverseString(message);
    printf("After reversal: %s\n", message);
    
    for(int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]);
    }
    
    printf("Encoded message: %s\n", message);
}

void decodeMessage(char message[]) {
    printf("\n=== DECODING PROCESS ===\n");
    printf("Encoded message: %s\n", message);
    
    // Toggle bits for each character (undoes the toggle)
    for(int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]);
    }
    printf("After bit untoggle: %s\n", message);
    
    // Reverse the string (undoes the reversal)
    reverseString(message);
    
    printf("Decoded message: %s\n", message);
}





int main() {
    int choice;
    char message[MAX_MESSAGE];
    
    printf("=== TCS SECURE MESSAGE SYSTEM ===\n");
    
    do {
        displayMenu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        
        // Clear input buffer
        while(getchar() != '\n');
        //Clearing the input buffer prevents leftover characters from messing up your next input operation.
        
        switch(choice) {
            case 1:
                printf("Enter message to encode: ");
                fgets(message, MAX_MESSAGE, stdin);  //fgets(variable, size, stdin);
                // Remove newline character
                if(message[strlen(message)-1] == '\n') { //checks last characterr
                    message[strlen(message)-1] = '\0'; //replaces last character
                }
                encodeMessage(message);
                break;
                
            case 2:
                printf("Enter message to decode: ");
                fgets(message, MAX_MESSAGE, stdin);
                if(message[strlen(message)-1] == '\n') {
                    message[strlen(message)-1] = '\0';
                }
                decodeMessage(message);
                break;
                
            case 3:
                printf("Exiting TCS System\n");
                break;
                
            default:
                printf("Invalid choice! Please enter 1-3.\n");
        }
    } while(choice != 3);
    
    return 0;
}
