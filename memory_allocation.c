#include <stdio.h>

int block[20], process[20], isAllocated[20] = {0}, allocated[20];
int b, p, choice, flag = 0;

void firstFit();
void bestFit();
void worstFit();
int bwFinder(int startIndex, int pSize, int curValue, int mode);
void display();

int main() {
    printf("Enter the number of blocks: ");
    scanf("%d", &b);

    printf("Enter the size of each block\n");
    for (int i = 0; i < b; i++) {
        printf("B%d: ", i);
        scanf("%d", &block[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the size of each process\n");
    for (int i = 0; i < p; i++) {
        printf("P%d: ", i);
        scanf("%d", &process[i]);
    }

    while (choice != 4) {
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit();
                display();
                break;
            case 2:
                bestFit();
                display();
                break;
            case 3:
                worstFit();
                display();
                break;
            case 4:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

void display() {
    printf("\nProcess\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < p; i++) {
        if (allocated[i] == -999) {
            printf("P%d\t%d\t\tNot Allocated\n", i, process[i]);
        } else {
            printf("P%d\t%d\t\t%d\n", i, process[i], allocated[i]);
        }
    }
}

void firstFit() {
    for (int i = 0; i < b; i++) isAllocated[i] = 0;

    for (int i = 0; i < p; i++) {
        flag = 0;
        for (int j = 0; j < b; j++) {
            if (process[i] <= block[j] && isAllocated[j] == 0) {
                allocated[i] = block[j];
                isAllocated[j] = 1;
                flag = 1;
                break;
            }
        }
        if (!flag) allocated[i] = -999;
    }
}

void bestFit() {
    for (int i = 0; i < b; i++) isAllocated[i] = 0;

    for (int i = 0; i < p; i++) {
        int small = 0;
        for (int j = 0; j < b; j++) {
            if (process[i] <= block[j] && isAllocated[j] == 0) {
                small = block[j];
                isAllocated[j] = 1;
                small = bwFinder(j, process[i], small, 1);
                allocated[i] = small;
                break;
            }
        }
        if (small == 0) allocated[i] = -999;
    }
}

void worstFit() {
    for (int i = 0; i < b; i++) isAllocated[i] = 0;

    for (int i = 0; i < p; i++) {
        int big = 0;
        for (int j = 0; j < b; j++) {
            if (process[i] <= block[j] && isAllocated[j] == 0) {
                big = block[j];
                isAllocated[j] = 1;
                big = bwFinder(j, process[i], big, 2);
                allocated[i] = big;
                break;
            }
        }
        if (big == 0) allocated[i] = -999;
    }
}

// Helper function for Best Fit (mode = 1) and Worst Fit (mode = 2)
int bwFinder(int startIndex, int pSize, int curValue, int mode) {
    int lastBlock = startIndex;
    for (int i = startIndex + 1; i < b; i++) {
        if (pSize <= block[i] && (mode == 1 ? block[i] < curValue : block[i] > curValue) && isAllocated[i] == 0) {
            isAllocated[lastBlock] = 0;
            lastBlock = i;
            curValue = block[i];
            isAllocated[i] = 1;
        }
    }
    return curValue;
}
