#include <stdio.h>
#include <string.h>

//(new thing learned)--Structs are used to logically group together different pieces of information that describe a single entity. 
//inventory[0].name gives Product 001
//without struct, i will have to make 4 different arrays

#define PROMO_CODE "Eid2025"
#define DISCOUNT_RATE 0.25

struct product{
	int code;
	char name[50];
	int quantity;
	float price;
};
struct cartItem {
    int productCode;
    char productName[50];
    int quantity;
    float price;
    float total;
};
struct customer{
	char name[50];
	char cnic[20]; //CNIC has letters/dashes
};

struct product inventory[10];
struct cartItem cart[20];
struct customer currentCustomer;
int productCount = 4; // starting with 4 products
int cartCount = 0;
int customerRegistered = 0;

void initializeInventory(){
	inventory[0].code = 1;
    strcpy(inventory[0].name, "Product 001");
    inventory[0].quantity = 50;
    inventory[0].price = 100.0;
    
    inventory[1].code = 2;
    strcpy(inventory[1].name, "Product 002");
    inventory[1].quantity = 30;
    inventory[1].price = 299.0;
    
    inventory[2].code = 3;
    strcpy(inventory[2].name, "Product 003");
    inventory[2].quantity = 45;
    inventory[2].price = 150.0;
    
    inventory[3].code = 4;
    strcpy(inventory[3].name, "Product 004");
    inventory[3].quantity = 100;
    inventory[3].price = 50.0;
}

void displayMenu(){
	printf("\n=== MAIN MENU ===\n");
    printf("1. Customer Information\n");
    printf("2. Display Inventory\n");
    printf("3. Add Item to Cart\n");
    printf("4. Display Total Bill\n");
    printf("5. Show Invoice\n");
    printf("6. Update Inventory\n");
    printf("7. Exit\n");
}

int findProductByCode(int code) {
    for(int i = 0; i < productCount; i++) {
        if(inventory[i].code == code) {
            return i;
        }
    }
    return -1;
}

int findCartItemByCode(int code) {
    for(int i = 0; i < cartCount; i++) {
        if(cart[i].productCode == code) {
            return i;
        }
    }
    return -1;
}

void customerInfo(){
	 printf("\n=== CUSTOMER INFORMATION ===\n");
    printf("Enter customer name: ");
    scanf(" %[^\n]", currentCustomer.name); //information updated in the above structure
    printf("Enter CNIC number: ");
    scanf(" %[^\n]", currentCustomer.cnic);
    
    customerRegistered = 1;
    printf("Customer information saved successfully!\n");
}

void displayInventory(){
	printf("\n=== CURRENT INVENTORY ===\n");
    printf("Product Code\tProduct Name\t\tQuantity\tPrice\n");
    printf("------------------------------------------------------------\n");
    
    for(int i = 0; i < productCount; i++) {
        printf("%d\t\t%-20s\t%-10d\t$%.2f\n", 
               inventory[i].code, inventory[i].name, 
               inventory[i].quantity, inventory[i].price);
    }
}

void updateInventory(int productCode, int quantitySold) {//UPDATING INVENTORY IS RWLATED TO ADDING ITEMS IN CART, WE MAKE THIS FUNCTION FIRST
    int index = findProductByCode(productCode);
    if(index != -1) {
        inventory[index].quantity -= quantitySold;
        if(inventory[index].quantity < 0) {
            inventory[index].quantity = 0;
        }
    }
}

void addItem(){
	if(!customerRegistered) { //ONLY USER CAN ADD ITEMS TO THE CART
        printf("Please enter customer information first (Option 1)!\n");
        return;
    }
    int productCode, quantity;
    printf("\n=== ADD ITEM TO CART ===\n");
    displayInventory();
    
    printf("Enter product code to add to cart: ");
    scanf("%d", &productCode);
    int productIndex = findProductByCode(productCode);
    if(productIndex == -1) {
        printf("Product not found!\n");
        return;
    }
    
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    if(quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }
    
    if(inventory[productIndex].quantity < quantity) {
        printf("Insufficient stock! Only %d available.\n", inventory[productIndex].quantity);
        return;
    }
    
    int cartIndex = findCartItemByCode(productCode);
    if(cartIndex != -1) {
        // Update existing cart item
        cart[cartIndex].quantity += quantity;
        cart[cartIndex].total = cart[cartIndex].quantity * cart[cartIndex].price;
    } else {
        // Add new item to cart
        cart[cartCount].productCode = productCode;
        strcpy(cart[cartCount].productName, inventory[productIndex].name);
        cart[cartCount].quantity = quantity;
        cart[cartCount].price = inventory[productIndex].price;
        cart[cartCount].total = quantity * inventory[productIndex].price;
        cartCount++;
    }
    
    // Update inventory
    updateInventory(productCode, quantity);
    
    printf("Item added to cart successfully!\n");
}
    
void displayTotalBill() {
    if(cartCount == 0) {
        printf("Cart is empty! Add items first.\n");
        return;
    }
    
    printf("\n=== TOTAL BILL ===\n");
    float totalAmount = 0;
    
    printf("Product\t\tQuantity\tPrice\t\tTotal\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < cartCount; i++) {
        printf("%-15s\t%-10d\t$%-10.2f\t$%-10.2f\n", 
               cart[i].productName, cart[i].quantity, 
               cart[i].price, cart[i].total);
        totalAmount += cart[i].total;
    }
    
    printf("------------------------------------------------\n");
    printf("Total Amount: $%.2f\n", totalAmount);

    char promo[20];
    printf("\nDo you have a promo code? (Enter code or 'no' to skip): ");
    scanf(" %[^\n]", promo);
    
    float discountedAmount = totalAmount;
    
    if(strcmp(promo, PROMO_CODE) == 0) {
        float discount = totalAmount * DISCOUNT_RATE;
        discountedAmount = totalAmount - discount;
        printf("Promo code applied! 25%% discount: -$%.2f\n", discount);  //you need %% to display a single %
        printf("Discounted Amount: $%.2f\n", discountedAmount);
    } else if(strcmp(promo, "no") != 0) {
        printf("Invalid promo code!\n");
    }
}

void showInvoice() {
    if(!customerRegistered) {
        printf("No customer information available!\n");
        return;
    }
    
    if(cartCount == 0) {
        printf("No items in cart!\n");
        return;
    }
    
    printf("\n=== INVOICE ===\n");
    printf("Customer Name: %s\n", currentCustomer.name);
    printf("CNIC: %s\n", currentCustomer.cnic);
    printf("----------------------------------------\n");
    
    float totalAmount = 0;
    printf("Product\t\tQuantity\tPrice\t\tTotal\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < cartCount; i++) {
        printf("%-15s\t%-10d\t$%-10.2f\t$%-10.2f\n", 
               cart[i].productName, cart[i].quantity, 
               cart[i].price, cart[i].total);
        totalAmount += cart[i].total;
    }
    
    printf("------------------------------------------------\n");
    printf("Total Amount: $%.2f\n", totalAmount);
    
    // Calculate discount
    float discount = totalAmount * DISCOUNT_RATE;
    float discountedAmount = totalAmount - discount;
    
    printf("\n--- BILL SUMMARY ---\n");
    printf("Amount without discount: $%.2f\n", totalAmount);
    printf("Discount (25%%): -$%.2f\n", discount);
    printf("Final Amount: $%.2f\n", discountedAmount);
    printf("========================================\n");
    printf("Thank you for shopping with us!\n");
}








int main(){
	
	initializeInventory();
	int choice;
	printf("==== SUPERMARKET MANAGEMENT SYSTEM ====\n");
    
    do {
        displayMenu();
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                customerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                addItem();
                break;
            case 4:
                displayTotalBill();
                break;
            case 5:
                showInvoice();
                break;
            case 6:
                // Update inventory is automatically handled in addItemToCart
                printf("Inventory updated automatically when items are purchased.\n");
                break;
            case 7:
                printf("Thank you for using Supermarket System!\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-7.\n");
        }
    } while(choice != 7);
    return 0;
	
}


