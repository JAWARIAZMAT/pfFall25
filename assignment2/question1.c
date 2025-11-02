#include <stdio.h>
#define MAX_BOOKS 100



//--------------------------FUNCTIONS----------------//
void menu(){
	printf("====MAIN MENU====\n");
	printf("Enter 1 for adding new book\n");
	printf("Enter 2 to process a sale\n");
	printf("Enter 3 to generate a low stock report\n");
	printf("Enter 4 to exit\n");
}

int duplicate_isbn(int isbns[],int books,int enterISBN){
	for(int i=0;i<books;i++){
		if(isbns[i]==enterISBN){
			printf("this isbn already exists!\n");
			return i;
		}
	}
	return -1;
}


void addBook(int isbns[],char titles[][50],float prices[],int quantities[],int *books){
	if(*books>=MAX_BOOKS){
		printf("inventory is full!\n");
		return; //if we dont use return, the code will still run , return stops the function here
	}
	printf("---ADDING NEW BOOK----\n");
	int enterISBN;
	printf("Enter ISBN:");
	scanf("%d",&enterISBN);
	
	if(duplicate_isbn(isbns,*books,enterISBN)!=-1){
		printf("book with %d isbn already exists\n",enterISBN);
		return;
	}
	
	isbns[*books]=enterISBN; //ADDING THE ISBNS IN THE ARRAY
	
	printf("enter book title: \n");
	scanf(" %[^\n]",titles[*books]); //add space before percentage
	
	printf("enter book price:$ \n");
	scanf("%f",&prices[*books]);

	printf("enter quantity: \n");
	scanf("%d",&quantities[*books]);
	
	(*books)++;
}


void saleProcess(int isbns[],char titles[][50],float prices[],int quantities[],int books){
	if(books==0){
		printf("no books!first add the books\n");
		return;
	}
	printf("----PROCESS SALE----\n");
	int saleISBN;
	printf("Enter ISBN to proceed:");
	scanf("%d",&saleISBN);
	
	int bookIndex= duplicate_isbn(isbns,books,saleISBN);
	if(bookIndex==-1){    //-1 is a common "error code" or "not found" indicator in C
		printf("book at isbn %d is not found\n",saleISBN);
		return;
	}
	printf("book:%s",titles[bookIndex]);
	printf("quantity:%d",quantities[bookIndex]);
	int copies;
	printf("enter number of copies to sell:");
	scanf("%d",&copies);
	
	if(copies<0){
		printf("enter a positive number\n");
		return;
	}
	if(quantities[bookIndex]<copies){
		printf("insufficient stock. only %d copies are available",quantities[bookIndex]);
		return;
	}
	quantities[bookIndex]=quantities[bookIndex]-copies;
	float total_price= prices[bookIndex]*copies;
	
	printf("\n✅ Sale processed successfully!\n");
    printf("Book: %s\n", titles[bookIndex]);
    printf("Price per copy: $%.2f\n", prices[bookIndex]);
    printf("Copies sold: %d\n", copies);
    printf("Total amount: $%.2f\n", total_price);
    printf("Remaining stock: %d\n", quantities[bookIndex]);
}


void generateReport(int isbns[],char titles[][50],float prices[],int quantities[],int books){
	if(books==0){
		printf("no books in inventory\n");
		return;
	}
	printf("----low stock report----");
	printf("ISBN\ttitle\tprice\tquantity\t\n");
	printf("\n_____________________________________________________________\n");
	int lowstock=0;
	for(int i=0;i<books;i++){
		if(quantities[i]<5){
			printf("%d\t\t%-25s\t$%-10.2f\t%d\n",isbns[i],titles[i],prices[i],quantities[i]); //%-25s = Print string, LEFT-aligned, in 25-character wide field
			//%-10.2f   = Float, LEFT-aligned, 10 chars wide, 2 decimal places
			lowstock++;	
		}
	}
	if (lowstock==0){
		printf("there are sufficient books in inventory\n");
	}
	else{
		printf("total books with low stock are %d",lowstock);
	}
}



int main(){
  	//Each array stores a different attribute of the same set of entities.
  	
  	
	int isbns[MAX_BOOKS];
	char titles[MAX_BOOKS][50];
	float prices[MAX_BOOKS];
	int quantities[MAX_BOOKS];
	int books=0; //we will use pointer for books because it needs to be updated permanently,or else it will disappear when the function ends
	//variable books is the "memory" that tracks what parts of your arrays actually contain real book data
	int choice;
	
	printf("====LIBERTY BOOKS INVENTORY MANAGEMENT====");
	
	do{
	menu();
	printf("enter your choice (1-4):");
	scanf("%d",&choice);
	
	
	switch(choice){
	case 1:
		addBook(isbns,titles,prices,quantities,&books);
		break;
	
	case 2:
		saleProcess(isbns,titles,prices,quantities,books); //this is not a database, you have to update all the avlues
		break;

	case 3:
		generateReport(isbns,titles,prices,quantities,books);
		break;
		
	case 4:
		printf("exiting function\n");
	
	default:
		printf("Choose 1/2/3 only\n");
    }
    }while(choice!=4); //display menu repeatedly till user dosen't select exit
    
		
		
		
}
