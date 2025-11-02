#include <stdio.h>


#define GRID_SIZE 5  // 5x5 grid

#define POWER_MASK 1        // 00000001 - Bit 0
#define OVERLOAD_MASK 2     // 00000010 - Bit 1  
#define MAINTENANCE_MASK 4  // 00000100 - Bit 2
//The numbers 1, 2, 4 are bit masks, they represent which specific bit we want to work with in the binary number.


void displayMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
}

void initializeGrid(int grid[][GRID_SIZE]) {
    // Initialize all sectors to 0,all flags OFF
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
    
    // Setting some initial values for testing
    grid[0][0] = 1;  // Power ON only (binary: 001)
    grid[1][1] = 3;  // Power ON + Overload (binary: 011)
    grid[2][2] = 5;  // Power ON + Maintenance (binary: 101)
    grid[3][3] = 7;  // All flags ON (binary: 111)
}

void updateSectorStatus(int grid[][GRID_SIZE]) {
    int row, col, flag, action;
    
    printf("\n=== UPDATE SECTOR STATUS ===\n");
    printf("Enter sector coordinates (row col, 0-%d): ", GRID_SIZE-1);
    scanf("%d %d", &row, &col);
    
    if(row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
        printf("Invalid coordinates!\n");
        return;
    }
    
    printf("Select flag to update:\n");
    printf("1. Power Status (Bit 0)\n");
    printf("2. Overload Warning (Bit 1)\n");
    printf("3. Maintenance Required (Bit 2)\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &flag);
    
    printf("Select action: 1=SET (ON), 0=CLEAR (OFF): ");
    scanf("%d", &action);
    
    int currentStatus = grid[row][col];
    
    switch(flag){
    	//| (OR): Sets a bit to 1
    	//& (AND): Can clear bits to 0
    	//~ (NOT): Flips all bits (1?0, 0?1)
    	case 1: 
            if(action == 1) {
                grid[row][col] = currentStatus | POWER_MASK;  // SET bit 0
            } else {
                grid[row][col] = currentStatus & ~POWER_MASK; // CLEAR bit 0
            }
            break;
            
        case 2: 
            if(action == 1) {
                grid[row][col] = currentStatus | OVERLOAD_MASK;  // SET bit 1
            } else {
                grid[row][col] = currentStatus & ~OVERLOAD_MASK; // CLEAR bit 1
            }
            break;
            
        case 3: 
            if(action == 1) {
                grid[row][col] = currentStatus | MAINTENANCE_MASK;  // SET bit 2
            } else {
                grid[row][col] = currentStatus & ~MAINTENANCE_MASK; // CLEAR bit 2
            }
            break;
            
        default:
            printf("Invalid flag selection!\n");
            return;
    }
    
    printf("Sector [%d][%d] updated successfully!\n", row, col);
    printf("New status: %d (binary: %03b)\n", grid[row][col], grid[row][col]);  //%03b is a format specifier that tells printf to display a number in binary format with 3 digits.
    	
	}
	
void querySectorStatus(int grid[][GRID_SIZE]) {
    int row, col;
    
    printf("\n=== QUERY SECTOR STATUS ===\n");
    printf("Enter sector coordinates (row col, 0-%d): ", GRID_SIZE-1);
    scanf("%d %d", &row, &col);
    
    if(row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE) {
        printf("Invalid coordinates!\n");
        return;
    }
    
    int status = grid[row][col];
    
    printf("\n--- SECTOR [%d][%d] STATUS REPORT ---\n", row, col);
    printf("Raw Status: %d (Binary: %03b)\n", status, status);
    printf("Power Status: %s\n", (status & POWER_MASK) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & OVERLOAD_MASK) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE_MASK) ? "YES" : "NO");
}



void runSystemDiagnostic(int grid[][GRID_SIZE]) {
    int overloadCount = 0;
    int maintenanceCount = 0;
    int poweredOnCount = 0;
    
    printf("\n=== SYSTEM DIAGNOSTIC REPORT ===\n");
    
    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            int status = grid[i][j];
            
            if(status & OVERLOAD_MASK) {
                overloadCount++;
            }
            if(status & MAINTENANCE_MASK) {
                maintenanceCount++;
            }
            if(status & POWER_MASK) {
                poweredOnCount++;
            }
        }
    }
    
    printf("Total Sectors: %d\n", GRID_SIZE * GRID_SIZE);
    printf("Sectors Powered ON: %d\n", poweredOnCount);
    printf("Sectors with Overload Warning: %d\n", overloadCount);
    printf("Sectors Requiring Maintenance: %d\n", maintenanceCount);
    printf("Sectors Powered OFF: %d\n", (GRID_SIZE * GRID_SIZE) - poweredOnCount);
}




int main() {
    int powerGrid[GRID_SIZE][GRID_SIZE];
    int choice;
    
    initializeGrid(powerGrid);
    printf("=== IESCO POWER GRID MONITORING SYSTEM ===\n");
    
    do {
        displayMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                updateSectorStatus(powerGrid);
                break;
            case 2:
                querySectorStatus(powerGrid);
                break;
            case 3:
                runSystemDiagnostic(powerGrid);
                break;
        
            case 4:
                printf("Exiting IESCO System\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-5\n");
        }
    } while(choice != 4);
    
    return 0;
}