#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 100
#define LEN 50
#define LOW 5

void newbook(int isbns[], char titles[][LEN], float prices[], int quantities[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("\ninventory full. cannot add more books.\n");
        return;
    }
    
    int isbn;
    printf("Enter book's ISBN: ");
    scanf("%d", &isbn);
    for(int i = 0; i < *count; i++) {
        if(isbn == isbns[i]) {
            printf("ISBN already exists\n");
            return;
        }
    }
    isbns[*count] = isbn;
    printf("Enter book title: ");
    scanf("%s", titles[*count]);
    
    printf("Enter book's price: ");
    scanf("%f", &prices[*count]);
    
    printf("Enter book quantity: ");
    scanf("%d", &quantities[*count]);
    
    (*count)++;
    printf("book added\n");
}

void processSale(int isbns[], int quantities[], int count) {
    if (count == 0) {
        printf("No books in inventory.\n");
        return;
    }
    
    int isbn, quantity;
    printf("Enter ISBN: ");
    scanf("%d", &isbn);
    
    int found = -1;
    for(int i = 0; i < count; i++) {
        if(isbn == isbns[i]) {
            found = i;
            break;
        }
    }
    
    if(found == -1) {
        printf("ISBN not found.\n");
        return;
    }
    
    printf("Enter quantity to sell: ");
    scanf("%d", &quantity);
    
    if(quantities[found] < quantity) {
        printf("short  stock. only have %d \n", quantities[found]);
        return;
    }
    
    quantities[found]=quantities[found]- quantity;
    printf("Sale processed remaining quantity is : %d\n", quantities[found]);
}

void Report(int isbns[], char titles[][LEN], float prices[], int quantities[], int count) {
    printf("Low Stock Report Quantity < %d\n", LOW);
    
    int found = 0;
    for(int i = 0; i < count; i++) {
        if(quantities[i] < LOW) {
            printf("ISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: %.2f\n", prices[i]);
            printf("Quantity: %d\n\n", quantities[i]);
            found = 1;
        }
    }
    
    if(!found) {
        printf("No books under 5 quantity.\n");
    }
}

void displayMenu() {
    printf("Enter your choice. Add New Book(1),Process a Sale(2),Generate Low-Stock Report(3),Exit(4) ");
}

int main() {
    int count = 3; // for example 3 books are currently present
    int isbns[MAX_BOOKS] = {12, 23, 34};
    char titles[MAX_BOOKS][LEN] = {"Come", "Went", "Good"};
    float prices[MAX_BOOKS] = {500.1, 700.2, 600.3};
    int quantities[MAX_BOOKS] = {2, 30, 40};
    
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                newbook(isbns, titles, prices, quantities, &count);
                break;
            case 2:
                processSale(isbns, quantities, count);
                break;
            case 3:
                Report(isbns, titles, prices, quantities, count);
                break;
            case 4:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
    
    return 0;
}