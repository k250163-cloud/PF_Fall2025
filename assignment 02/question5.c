#include <stdio.h>
#include <string.h>

void reversestring(char str[]) {
    int length = strlen(str);
    int j = length - 1;
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        j--;
    }
}

void togglebits(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
       
        int bit2 = (ch >> 1) & 1;
        int bit5 = (ch >> 4) & 1;
       
        if (bit2 == 1) {
            ch = ch & ~(1 << 1);
        } else {
            ch = ch | (1 << 1);
        }
       
        if (bit5 == 1) {
            ch = ch & ~(1 << 4);
        } else {
            ch = ch | (1 << 4);
        }
       
        str[i] = ch;
    }
}

void encodeMessage(char message[]) {
    printf("original message: %s\n", message);
    reversestring(message);
    togglebits(message);
    printf("encoded message: %s\n", message);
}

void decodeMessage(char message[]) {
    printf("encoded message: %s\n", message);
    togglebits(message);
    reversestring(message);
    printf("decoded message: %s\n", message);
}

void showMenu() {
    printf(" tcs message encoder/decoder\n");
    printf("(1) encode message (2), decode message, (3) exit\n");
    printf("enter your choice between 1 and 3: ");
}

int main() {
    int choice;
    char message[1000];
   
    printf("tcs secure message tool\n");
   
    do {
        showMenu();
        scanf("%d", &choice);
        getchar();
       
        switch (choice) {
            case 1:
                printf("enter message to encode: ");
                fgets(message, sizeof(message), stdin);
               
                int len = strlen(message);
                if (message[len-1] == '\n') {
                    message[len-1] = '\0';
                }
               
                encodeMessage(message);
                break;
               
            case 2:
                printf("enter message to decode: ");
                fgets(message, sizeof(message), stdin);
               
                len = strlen(message);
                if (message[len-1] == '\n') {
                    message[len-1] = '\0';
                }
               
                decodeMessage(message);
                break;
               
            case 3:
                printf("exiting tcs secure message tool.\n");
                break;
               
            default:
                printf("invalid choice please enter 1-3.\n");
        }
    } while (choice != 3);
   
    return 0;
}
