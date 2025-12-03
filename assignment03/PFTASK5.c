#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TextBuffer {
    char **lines;
    int count;
    int capacity;
};
int i;

void initBuffer(struct TextBuffer *tb, int initialCapacity) {
    tb->lines = (char **)malloc(initialCapacity * sizeof(char *));
    if (tb->lines == NULL) {
        fprintf(stderr, "Memory allocation failed during initialization.\n");
        exit(1);
    }
    tb->count = 0;
    tb->capacity = initialCapacity;
}

void insertLine(struct TextBuffer *tb, int index, const char *text) {
    if (index < 0 || index > tb->count) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    if (tb->count >= tb->capacity) {
        int newCapacity = tb->capacity * 2;
        char **newLines = (char **)realloc(tb->lines, newCapacity * sizeof(char *));
        if (newLines == NULL) {
            fprintf(stderr, "Memory allocation failed during resize.\n");
            return;
        }
        tb->lines = newLines;
        tb->capacity = newCapacity;
    }

    for ( i = tb->count; i > index; i--) {
        tb->lines[i] = tb->lines[i - 1];
    }

    tb->lines[index] = (char *)malloc((strlen(text) + 1) * sizeof(char));
    if (tb->lines[index] == NULL) {
        fprintf(stderr, "Memory allocation failed for line text.\n");
        return;
    }
    strcpy(tb->lines[index], text);
    tb->count++;
}

void deleteLine(struct TextBuffer *tb, int index) {
    if (index < 0 || index >= tb->count) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    free(tb->lines[index]);

    for ( i = index; i < tb->count - 1; i++) {
        tb->lines[i] = tb->lines[i + 1];
    }

    tb->count--;
}

void printAllLines(struct TextBuffer *tb) {
    printf("\n--- Current Buffer ---\n");
    if (tb->count == 0) {
        printf("(empty)\n");
    } else {
        for (i = 0; i < tb->count; i++) {
            printf("%d: %s", i + 1, tb->lines[i]);
        }
    }
    printf("----------------------\n");
}

void shrinkToFit(struct TextBuffer *tb) {
    if (tb->count == 0) return;
    
    char **newLines = (char **)realloc(tb->lines, tb->count * sizeof(char *));
    if (newLines == NULL) {
        fprintf(stderr, "Memory reallocation failed during shrink.\n");
        return;
    }
    tb->lines = newLines;
    tb->capacity = tb->count;
    printf("Buffer shrunk to %d lines.\n", tb->capacity);
}

void saveToFile(struct TextBuffer *tb, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for ( i = 0; i < tb->count; i++) {
        fprintf(fp, "%s", tb->lines[i]);
    }

    fclose(fp);
    printf("Saved successfully to %s\n", filename);
}

void freeAll(struct TextBuffer *tb) {
    for (i = 0; i < tb->count; i++) {
        free(tb->lines[i]);
    }
    free(tb->lines);
    tb->lines = NULL;
    tb->count = 0;
    tb->capacity = 0;
}

void loadFromFile(struct TextBuffer *tb, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return;
    }

    freeAll(tb);
    initBuffer(tb, 2); 

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        insertLine(tb, tb->count, buffer);
    }

    fclose(fp);
    printf("Loaded successfully from %s\n", filename);
}

int main() {
    struct TextBuffer editor;
    initBuffer(&editor, 2);

    int choice;
    char buffer[1024];
    int index;
    char filename[100];

    while (1) {
        printf("\n1. Append Line\n2. Insert Line\n3. Delete Line\n4. View Buffer\n5. Save to File\n6. Load from File\n7. Shrink Memory\n8. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter text: ");
                fgets(buffer, sizeof(buffer), stdin);
                insertLine(&editor, editor.count, buffer);
                break;
            case 2:
                printf("Enter index (1-based): ");
                scanf("%d", &index);
                while (getchar() != '\n');
                printf("Enter text: ");
                fgets(buffer, sizeof(buffer), stdin);
                insertLine(&editor, index - 1, buffer);
                break;
            case 3:
                printf("Enter index to delete (1-based): ");
                scanf("%d", &index);
                deleteLine(&editor, index - 1);
                break;
            case 4:
                printAllLines(&editor);
                break;
            case 5:
                printf("Enter filename: ");
                scanf("%s", filename);
                saveToFile(&editor, filename);
                break;
            case 6:
                printf("Enter filename: ");
                scanf("%s", filename);
                loadFromFile(&editor, filename);
                break;
            case 7:
                shrinkToFit(&editor);
                break;
            case 8:
                freeAll(&editor);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
