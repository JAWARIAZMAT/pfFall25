#include <stdio.h>
#include <string.h>

struct shelf{
	int id;
	int popularity;
	int last_accessed; //to track how many times we accessed a book.
	
};

void add(int x , int y ,struct shelf books[], int shelf_capacity, int *bookcount){
	//first we will check if book exists or shelf is full and then add new book
	for(int i = 0; i < *bookcount; i++) {
        if(books[i].id == x) {
            books[i].popularity += y;
            books[i].last_accessed = 0; 
            return;
        }
    }
    
    if(*bookcount == shelf_capacity) {
        int leastused = 0;
        for(int i = 1; i < *bookcount; i++) {
            if(books[i].last_accessed > books[leastused].last_accessed) {
                leastused= i;
            }
        }
        //shift array to remove the book
        for(int i = leastused; i < *bookcount - 1; i++) {
            books[i] = books[i + 1];
        }
        (*bookcount)--;
    }
    
     books[*bookcount].id = x;
    books[*bookcount].popularity = y;
    books[*bookcount].last_accessed = 0; 
    (*bookcount)++;
    
	
	
}

int access(int x,struct shelf books[], int bookcount){
	for (int i=0;i<bookcount;i++){
		if(x==books[i].id){
			printf("book with id %d found",books[i].id);
			return books[i].popularity;
		}
	}
	return -1;		
}


int main(){
	int shelf_capacity=5,operations;
	int n,bookcount=0;
	printf("how many books do u want to add?:");
	scanf("%d",&n);
	printf("enter number of opeartions: ");
	scanf("%d",&operations);
	struct shelf books[shelf_capacity];
	int x,y;
	for(int i=0;i<n;i++){
	printf("enter book id: ");
	scanf("%d",&books[i].id);	
	printf("enter poularity of book:");
	scanf("%d",&books[i].popularity);
	bookcount++;  
    }
    
    for(int i = 0; i < operations; i++) {
        char operation1[10];
        int x, y;
        
        printf("Operation %d: ", i+1);
        scanf("%s", operation1);
        
        if(strcmp(operation1, "ADD") == 0) {
            scanf("%d %d", &x, &y);
            add(x, y, books, shelf_capacity, &bookcount);
        }
        else if(strcmp(operation1, "ACCESS") == 0) {
            scanf("%d", &x);
            int result = access(x, books, bookcount);
            printf("Result: %d\n", result);
        }
    }
	
}