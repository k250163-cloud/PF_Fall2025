#include <stdio.h>

#define ROWS 5
#define COLS 5

void updateSector(int grid[ROWS][COLS]) {
    int row, col, flag, value;
   
    printf("Enter row (0-%d): ", ROWS-1);
    scanf("%d", &row);
    printf("Enter column (0-%d): ", COLS-1);
    scanf("%d", &col);
   
    if(row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates\n");
        return;
    }
   
    printf("input flag to update like Power(0), overload(1), maintenance(2): ");
    scanf("%d", &flag);
    printf("Enter value (0 or 1): ");
    scanf("%d", &value);
   
    if(flag == 0) {
    if(value == 1)
        grid[row][col] = grid[row][col] | (1 << 0);
    else
        grid[row][col] = grid[row][col] & ~(1 << 0);
}
else if(flag == 1) {
    if(value == 1)
        grid[row][col] = grid[row][col] | (1 << 1);
    else
        grid[row][col] = grid[row][col] & ~(1 << 1);
}
else if(flag == 2) {
    if(value == 1)
        grid[row][col] = grid[row][col] | (1 << 2);
    else
        grid[row][col] = grid[row][col] & ~(1 << 2);
}
    else {
        printf("ivalid flag\n");
    }
   
    printf("sector updated \n");
}

void querySector(int grid[ROWS][COLS]) {
    int row, col;
   
    printf("Enter row (0-%d): ", ROWS-1);
    scanf("%d", &row);
    printf("Enter column (0-%d): ", COLS-1);
    scanf("%d", &col);
   
    if(row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }
   
    int status = grid[row][col];
   
    printf("\n--- Sector [%d][%d] Status Report ---\n", row, col);
   
    if(status & (1 << 0))
        printf("Power is : ON\n");
    else
        printf("Power is: OFF\n");
   
    if(status & (1 << 1))
        printf("Overload Warning: OVERLOADED\n");
    else
        printf("Overload Warning: Normal\n");
   
    if(status & (1 << 2))
        printf("Maintenance: REQUIRED\n");
    else
        printf("Maintenance: Not Required\n");
}

void runDiagnostic(int grid[ROWS][COLS]) {
    int overloaded = 0;
    int maintenance = 0;
   
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(grid[i][j] & (1 << 1))
                overloaded++;
            if(grid[i][j] & (1 << 2))
                maintenance++;
        }
    }
    printf("Overloaded sectors: %d\n", overloaded);
    printf("Sectors requiring maintenance: %d\n", maintenance);
    printf("Total sectors scanned: %d\n", ROWS * COLS);
}

void displayGrid(int grid[ROWS][COLS]) {
    printf("\nCurrent Grid Status\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int grid[ROWS][COLS] = {0};
    int choice;
   
    printf("IESCO power grid monitoring system n");
   
    do {
        printf("update secotr(1),query sector(2),run diagnostic(3),display grid(4), exit(5)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                updateSector(grid);
                break;
            case 2:
                querySector(grid);
                break;
            case 3:
                runDiagnostic(grid);
                break;
            case 4:
                displayGrid(grid);
                break;
            case 5:
                printf("Exiting system.\n");
                break;
            default:
                printf("wrong choice\n");
        }
    } while(choice != 5);
   
    return 0;
}
