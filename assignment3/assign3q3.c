#include <stdio.h>
#include <string.h>

struct Employee {
    int employee_id;
    char name[50];
    char designation[100];
    float salary;
};

void enterDetails(struct Employee employees[], int n) {
    for(int i = 0; i < n; i++) {
        printf("Enter details for employee %d:\n", i+1);
        printf("ID: ");
        scanf("%d", &employees[i].employee_id); //& is used for int and float but not for charcater arrays
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
}

void displayDetails(struct Employee employees[], int n) {
    printf("\nEmployee Records:\n");
    printf("ID\tName\tDesignation\tSalary\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.2f\n", employees[i].employee_id, employees[i].name, 
               employees[i].designation, employees[i].salary);
    }
}

void findHighestSalary(struct Employee employees[], int n) {
    float max = employees[0].salary;
    int position = 0;
    
    for(int i = 1; i < n; i++) {
        if(employees[i].salary > max) {
            max = employees[i].salary;
            position = i;
        }
    }
    printf("\nHighest Salary Employee:\n");
    printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", 
           employees[position].employee_id, employees[position].name,
           employees[position].designation, employees[position].salary);
}

void searchEmployee(struct Employee employees[], int n) {
    int choice;
    printf("\nSearch by:ID(1) or Name(2): ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        int search_id;
        printf("Enter employee ID: ");
        scanf("%d", &search_id);
        
        for(int i = 0; i < n; i++) {
            if(employees[i].employee_id == search_id) {
                printf("Employee found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n",
                       employees[i].employee_id, employees[i].name,
                       employees[i].designation, employees[i].salary);
                return;
            }
        }
        printf("Employee with ID %d not found.\n", search_id);
    }
    else if(choice == 2) {
        char search_name[50];
        printf("Enter employee name: ");
        scanf("%s", search_name);
        
        for(int i = 0; i < n; i++) {
            if(strcmp(employees[i].name, search_name) == 0) {
                printf("Employee found:\n");
                printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n",
                       employees[i].employee_id, employees[i].name,
                       employees[i].designation, employees[i].salary);
                return;
            }
        }
        printf("Employee with name %s not found.\n", search_name);
    }
}

int main() {
    int n;
    printf("How many employees? ");
    scanf("%d", &n);
    
    struct Employee employees[n];
    
    enterDetails(employees, n);
    displayDetails(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);
    
    return 0;
}