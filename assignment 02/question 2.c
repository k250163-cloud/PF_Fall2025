#include <stdio.h>

int productCodes[4] = {1, 2, 3, 4};
int quantities[4] = {50, 10, 20, 8};
int prices[4] = {100, 200, 300, 150};

char customerName[50];
char customerCNIC[15];

int cart[4] = {0};

void getCustomerInfo() {
    printf("Enter customer name: ");
    scanf("%s", customerName);
    printf("Enter customer CNIC: ");
    scanf("%s", customerCNIC);
    printf("Customer information saved.\n");
}

void displayInventory() {
    printf("\nProduct Code\tQuantity in stock\tPrice per product\n");
    for(int i = 0; i < 4; i++) {
        printf("%d\t\t%d\t\t\t%d\n", productCodes[i], quantities[i], prices[i]);
    }
}

void updateInventory(int code, int quantity) {
    for(int i = 0; i < 4; i++) {
        if(productCodes[i] == code) {
            quantities[i] = quantities[i] - quantity;
            break;
        }
    }
}
void addToCart() {
    int code, quantity;
    
    printf("Enter product code: ");
    scanf("%d", &code);
    
    int found = 0;
    for(int i = 0; i < 4; i++) {
        if(productCodes[i] == code) {
            found = 1;
            printf("Enter quantity: ");
            scanf("%d", &quantity);
            
            if(quantity <= quantities[i]) {
                cart[i] = cart[i] + quantity;
                updateInventory(code, quantity);
                printf("Item added to cart.\n");
            } else {
                printf("Not enough stock.\n");
            }
            break;
        }
    }
    
    if(!found) {
        printf("Invalid product code.\n");
    }
}
int checkPromoCode(char promo[]) {
    char correctPromo[] = "Etd2025";
    int i = 0;
    
    while(promo[i] != '\0' && correctPromo[i] != '\0') {
        if(promo[i] != correctPromo[i]) {
            return 0; 
        }
        i++;
    }
    
    if(promo[i] == '\0' && correctPromo[i] == '\0') {
        return 1; 
    }
    
    return 0; 
}

void displayTotalBill() {
    float total = 0;
    
    // Calculate total
    for(int i = 0; i < 4; i++) {
        total = total + (cart[i] * prices[i]);
    }
    
    
    char promo[20];
    printf("Do you have a promo code? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    
    float discount = 0;
    if(choice == 'y' || choice == 'Y') {
        printf("Enter promo code: ");
        scanf("%s", promo);
        
        if(checkPromoCode(promo) == 1) {
            discount = total * 0.25;
            printf("25%% discount given.\n");
        } else {
            printf("Invalid promo code.\n");
        }
    }
    
    printf("Total bill: %f\n", total);
    printf("Discount: %f\n", discount);
    printf("Amount to pay: %f\n", total - discount);
}

void showInvoice() {
    printf(" INVOICE\n");
    printf("Customer: %s\n", customerName);
    printf("CNIC: %s\n", customerCNIC);
    
    float total = 0;
    printf("\nItems:\n");
    for(int i = 0; i < 4; i++) {
        if(cart[i] > 0) {
            int itemTotal = cart[i] * prices[i];
            printf("Product %d - Quantity: %d - Price: %d\n", 
                   productCodes[i], cart[i], prices[i]);
            total = total + itemTotal;
        }
    }
    
    float discount = total * 0.25;
    
    printf("Bill without discount: %f\n", total);
    printf("Bill with discount: %f\n", total - discount);
}

int main() {
    int choice;
    
    do {
        printf("Enter choice: (1) Customer information, (2)Display inventory,(3)Add item to cart,(4)Display total bill,(5)Show invoice,(6)exit");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                getCustomerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                displayTotalBill();
                break;
            case 5:
                showInvoice();
                break;
            case 6:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 6);
    
    return 0;
}