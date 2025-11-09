#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int getCell(int x, char y) {
    int A = 'A';
    int y1100 = (y - A + 1) * 10 - 10;

    return y1100 + x - 1;
}

void printGame(char cells[100]) {
    printf("  ");

    for (int i = 0; i < 10; i++) {
        printf("%d ", i + 1);

        if (i == 9) {
            printf("\n");
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%c ", i + 65);

        for (int j = 0; j < 10; j++) {
            printf("%c ", cells[i * 10 + j]);

            if (j == 9) {
                printf("\n");
            }
        }
    }
}

bool isShipOverlaid(int shipStart, int shipLength, bool isShipVertical, int subShipStart, int subShipLenght, bool isSubShipVertical) {
    for (int i = 0; i < shipLength; i++) {
        for (int j = 0; j < subShipLenght; j++) {
            if ((shipStart + (isShipVertical ? i * 10 : i)) == (subShipStart + (isSubShipVertical ? j * 10 : j))) {
                return true;
            }
        }
    }

    return false;
}

bool isShipOverflow(int shipStart, int shipLength, bool shipIsVertical) {
    return shipIsVertical ? shipStart / 10 + shipLength > 10 : shipStart % 10 + shipLength > 10;
}

int generateShip(int shipLength, bool isShipVertical, int subShipStart, int subShipLength, bool isSubShipVertical) {
    int shipStart = rand() % 100;

    do {
        shipStart = rand() % 100;
    } while (isShipOverflow(shipStart, shipLength, isShipVertical) || isShipOverlaid(shipStart, shipLength, isShipVertical, subShipStart, subShipLength, isSubShipVertical));

    return shipStart;
}

int main() {
    char cells[100];

    for (int i = 0; i < 100; i++) {
        cells[i] = '*';
    }

    char knownCells[100];

    for (int i = 0; i < 100; i++) {
        knownCells[i] = '*';
    }

    srand((unsigned) time(NULL));

    int longShipIsVertical = rand() % 2 == 1;
    int longShipStart = generateShip(4, longShipIsVertical, 0, 0, false);

    for (int i = 0; i < 4; i++) {
        cells[longShipStart + (longShipIsVertical ? i * 10 : i)] = 'L';
    }

    int mediumShipIsVertical = rand() % 2 == 1;
    int mediumShipStart = generateShip(3, mediumShipIsVertical, longShipStart, 4, longShipIsVertical);

    for (int i = 0; i < 3; i++) {
        cells[mediumShipStart + (mediumShipIsVertical ? i * 10 : i)] = 'M';
    }

    int shortShipIsVertical = rand() % 2 == 1;
    int shortShipStart = generateShip(2, shortShipIsVertical, mediumShipStart, 3, mediumShipIsVertical);

    for (int i = 0; i < 2; i++) {
        cells[shortShipStart + (shortShipIsVertical ? i * 10 : i)] = 'S';
    }

    printGame(knownCells);

    int attempts = 0;
    int longShipPartsFound = 0, mediumShipPartsFound = 0, shortShipPartsFound = 0;

    while (attempts < 40) {
        int x;
        char y;

        do {
            printf("Enter X (1-10) and Y (A-J)\n");
            scanf("%d %c", &x, &y);
        } while (x < 1 || x > 10 || y < 'A' || y > 'J');

        int cell = getCell(x, y);

        if (knownCells[cell] != '*') {
            printf("You already tried this cell!\n");
            continue;
        } else if (cells[cell] == '*') {
            knownCells[cell] = 'O';

            printf("Miss!\n");
        } else {
            switch (cells[cell]) {
                case 'L':
                    longShipPartsFound++;
                    break;
                case 'M':
                    mediumShipPartsFound++;
                    break;
                case 'S':
                    shortShipPartsFound++;
                    break;
            }

            knownCells[cell] = cells[cell];

            printf("Hit!\n");
        }

        attempts++;

        printf("Attempts: %d/40\n", attempts);

        printGame(knownCells);

        if (longShipPartsFound == 4 && mediumShipPartsFound == 3 && shortShipPartsFound == 2) {
            printf("You won!\n");
            break;
        } else if (attempts >= 40) {
            printf("You lose!\n");
            printGame(cells);
            break;
        }
    }
}