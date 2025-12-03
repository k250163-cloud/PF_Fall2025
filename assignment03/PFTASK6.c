#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char batch[20];
    char type[10];
    char regDate[15];
    char dob[15];
    char interest[10];
} Student;

Student *students = NULL;
int studentCount = 0;
const char *DB_FILE = "members.dat";

void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(Student s, const char *filename);
void updateStudent(int studentID);
void deleteStudent(int studentID);
void displayAll();
void generateReports();
int isDuplicate(int id);
void performStressTest();
void clearInputBuffer();
int i;
int main() {
    loadDatabase(DB_FILE);
    int choice;
    Student s;

    do {
        printf("\n--- IEEE/ACM Membership Manager ---\n");
        printf("1. Register New Student\n");
        printf("2. Update Student Info\n");
        printf("3. Delete Student\n");
        printf("4. View All Registrations\n");
        printf("5. Generate Batch Reports\n");
        printf("6. Perform Stress Test (Add Dummy Data)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = 0;
        }

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &s.id);
                if (isDuplicate(s.id)) {
                    printf("Error: Student ID %d already exists.\n", s.id);
                } else {
                    clearInputBuffer();
                    printf("Enter Full Name: ");
                    scanf("%[^\n]", s.name);
                    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
                    scanf("%s", s.batch);
                    printf("Enter Membership Type (IEEE/ACM): ");
                    scanf("%s", s.type);
                    printf("Enter Reg Date (YYYY-MM-DD): ");
                    scanf("%s", s.regDate);
                    printf("Enter DOB (YYYY-MM-DD): ");
                    scanf("%s", s.dob);
                    printf("Interest (IEEE/ACM/Both): ");
                    scanf("%s", s.interest);
                    addStudent(s, DB_FILE);
                }
                break;
            case 2:
                printf("Enter Student ID to update: ");
                int upId;
                scanf("%d", &upId);
                updateStudent(upId);
                break;
            case 3:
                printf("Enter Student ID to delete: ");
                int delId;
                scanf("%d", &delId);
                deleteStudent(delId);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                generateReports();
                break;
            case 6:
                performStressTest();
                break;
            case 7:
                saveDatabase(DB_FILE);
                printf("Database saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    if (students) {
        free(students);
    }
    return 0;
}

void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    if (fileSize > 0) {
        studentCount = fileSize / sizeof(Student);
        students = (Student *)malloc(studentCount * sizeof(Student));
        if (students == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        if (fread(students, sizeof(Student), studentCount, fp) != studentCount) {
            printf("Error reading file.\n");
        }
    }
    fclose(fp);
    printf("Loaded %d records from database.\n", studentCount);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    if (studentCount > 0) {
        fwrite(students, sizeof(Student), studentCount, fp);
    }
    fclose(fp);
}

void addStudent(Student s, const char *filename) {
    Student *temp = (Student *)realloc(students, (studentCount + 1) * sizeof(Student));
    if (!temp) {
        printf("Memory allocation failed during add.\n");
        return;
    }
    students = temp;
    students[studentCount] = s;
    studentCount++;
    
    saveDatabase(filename);
    printf("Student registered successfully.\n");
}

void updateStudent(int studentID) {
    int found = 0;
    for ( i = 0; i < studentCount; i++) {
        if (students[i].id == studentID) {
            found = 1;
            printf("Updating record for %s\n", students[i].name);
            printf("1. Update Batch\n2. Update Membership Type\nEnter choice: ");
            int c;
            scanf("%d", &c);
            if (c == 1) {
                printf("Enter new Batch: ");
                scanf("%s", students[i].batch);
            } else if (c == 2) {
                printf("Enter new Membership Type: ");
                scanf("%s", students[i].type);
            } else {
                printf("Invalid option.\n");
            }
            break;
        }
    }
    if (found) {
        saveDatabase(DB_FILE);
        printf("Record updated.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void deleteStudent(int studentID) {
    int foundIndex = -1;
    for ( i = 0; i < studentCount; i++) {
        if (students[i].id == studentID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for ( i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        Student *temp = (Student *)realloc(students, studentCount * sizeof(Student));
        if (studentCount > 0 && temp != NULL) {
            students = temp;
        } else if (studentCount == 0) {
            free(students);
            students = NULL;
        }
        saveDatabase(DB_FILE);
        printf("Student deleted successfully.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void displayAll() {
    if (studentCount == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\n%-10s %-20s %-15s %-10s %-12s\n", "ID", "Name", "Batch", "Type", "Interest");
    printf("--------------------------------------------------------------------------\n");
    for (i = 0; i < studentCount; i++) {
        printf("%-10d %-20s %-15s %-10s %-12s\n", 
            students[i].id, students[i].name, students[i].batch, 
            students[i].type, students[i].interest);
    }
}

void generateReports() {
    char batchFilter[20];
    printf("Enter Batch to filter (CS/SE/Cyber Security/AI): ");
    clearInputBuffer();
    scanf("%[^\n]", batchFilter);

    printf("\nReport for Batch: %s\n", batchFilter);
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Type", "Interest");
    int count = 0;
    for ( i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batchFilter) == 0) {
            printf("%-10d %-20s %-10s %-10s\n", 
                students[i].id, students[i].name, students[i].type, students[i].interest);
            count++;
        }
    }
    if (count == 0) printf("No students found in this batch.\n");
}

int isDuplicate(int id) {
    for ( i = 0; i < studentCount; i++) {
        if (students[i].id == id) return 1;
    }
    return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void performStressTest() {
    printf("Adding 25 dummy records...\n");
    char *batches[] = {"CS", "SE", "AI", "Cyber Security"};
    char *types[] = {"IEEE", "ACM"};
    char *interests[] = {"IEEE", "ACM", "Both"};
    
    for ( i = 0; i < 25; i++) {
        int tempID = 1000 + i;
        if (!isDuplicate(tempID)) {
            Student s;
            s.id = tempID;
            sprintf(s.name, "Student_%d", i);
            strcpy(s.batch, batches[i % 4]);
            strcpy(s.type, types[i % 2]);
            strcpy(s.regDate, "2023-01-01");
            strcpy(s.dob, "2002-01-01");
            strcpy(s.interest, interests[i % 3]);
            
            Student *temp = (Student *)realloc(students, (studentCount + 1) * sizeof(Student));
            if (temp) {
                students = temp;
                students[studentCount] = s;
                studentCount++;
            }
        }
    }
    saveDatabase(DB_FILE);
    printf("Stress test data added and saved.\n");
}
