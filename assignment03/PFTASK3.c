#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};
int i;
void displayEmployees(struct Employee e[], int n) {
    printf("\n---- Employee Records ---\n");
    printf("ID\tName\tDesignation\tSalary\n");
    for ( i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.2f\n", e[i].id, e[i].name, e[i].designation, e[i].salary);
    }
}

void findHighestSalary(struct Employee e[], int n) {
    int maxIndex = 0;
    for ( i = 1; i < n; i++) {
        if (e[i].salary > e[maxIndex].salary) {
            maxIndex = i;
        }
    }
    printf("\n--- Highest Salary ---\n");
    printf("ID: %d\nName: %s\nSalary: %.2f\n", e[maxIndex].id, e[maxIndex].name, e[maxIndex].salary);
}

void searchEmployee(struct Employee e[], int n) {
    int choice;
    printf("\n--- Search Employee ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int found = 0;
    
    if (choice == 1) {
        int targetId;
        printf("Enter ID to search: ");
        scanf("%d", &targetId);
        
        for ( i = 0; i < n; i++) {
            if (e[i].id == targetId) {
                printf("Found: %s (%s) - %.2f\n", e[i].name, e[i].designation, e[i].salary);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        char targetName[50];
        printf("Enter Name to search: ");
        scanf("%s", targetName);
        
        for ( i = 0; i < n; i++) {
            if (strcmp(e[i].name, targetName) == 0) {
                printf("Found: ID %d (%s) - %.2f\n", e[i].id, e[i].designation, e[i].salary);
                found = 1;
                break;
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

void updateSalaries(struct Employee e[], int n) {
    for ( i = 0; i < n; i++) {
        if (e[i].salary < 50000) {
            e[i].salary = e[i].salary + (e[i].salary * 0.10);
        }
    }
    printf("\nSuccess: 10%% bonus applied to eligible employees.\n");
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee employees[100];

    for ( i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("Employee ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }

    displayEmployees(employees, n);
    findHighestSalary(employees, n);
    searchEmployee(employees, n);

    updateSalaries(employees, n);
    displayEmployees(employees, n);

    return 0;
}
