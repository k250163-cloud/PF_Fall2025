#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int popularity;
} Book;
int i,j;

void moveToBack(Book *shelf, int index, int count) {
    Book temp = shelf[index];
    for ( i = index; i < count - 1; i++) {
        shelf[i] = shelf[i + 1];
    }
    shelf[count - 1] = temp;
}

int main() {
    int capacity, Q;
    printf("Enter capacity and number of operations: ");
    if (scanf("%d %d", &capacity, &Q) != 2) return 0;

    Book *shelf = (Book *)malloc(capacity * sizeof(Book));
    int count = 0;

    for ( i = 0; i < Q; i++) {
        char op[10];
        printf("Enter operation (ADD or ACCESS): ");
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            int x, y;
            printf("Enter book ID and popularity: ");
            scanf("%d %d", &x, &y);

            int found = -1;
            for (j = 0; j < count; j++) {
                if (shelf[j].id == x) {
                    found = j;
                    break;
                }
            }

            if (found != -1) {
                shelf[found].popularity = y;
                moveToBack(shelf, found, count);
            } else {
                if (count < capacity) {
                    shelf[count].id = x;
                    shelf[count].popularity = y;
                    count++;
                } else {
                    for ( j = 0; j < capacity - 1; j++) {
                        shelf[j] = shelf[j + 1];
                    }
                    shelf[capacity - 1].id = x;
                    shelf[capacity - 1].popularity = y;
                }
            }
        } else if (strcmp(op, "ACCESS") == 0) {
            int x;
            printf("Enter book ID: ");
            scanf("%d", &x);

            int found = -1;
            for ( j = 0; j < count; j++) {
                if (shelf[j].id == x) {
                    found = j;
                    break;
                }
            }

            if (found != -1) {
                printf("%d\n", shelf[found].popularity);
                moveToBack(shelf, found, count);
            } else {
                printf("-1\n");
            }
        }
    }

    free(shelf);
    return 0;
}
