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

bool isShipOverlaid(char ship, int shipStart, int shipLength, bool isShipVertical, char cells[100]) {
    for (int i = 0; i < shipLength; i++) {
        char cell = cells[shipStart + (isShipVertical ? i * 10 : i)];

        if (cell != ship && cell != '*') {
            return true;
        }
    }

    return false;
}

bool isShipOverflow(int shipStart, int shipLength, bool shipIsVertical) {
    return shipIsVertical ? shipStart / 10 + shipLength > 10 : shipStart % 10 + shipLength > 10;
}

int generateShip(char ship, int shipLength, bool isShipVertical, char cells[100]) {
    int shipStart = rand() % 100;

    do {
        shipStart = rand() % 100;
    } while (isShipOverflow(shipStart, shipLength, isShipVertical) || isShipOverlaid(ship, shipStart, shipLength, isShipVertical, cells));

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

    int totalShips = 3;
    char ships[] = {'L', 'M', 'S'};
    int shipLengths[] = {4, 3, 2};
    int shipPartsFound[] = {0, 0, 0};

    for (int i = 0; i < totalShips; i++) {
        char ship = ships[i];
        int shipLength = shipLengths[i];
        bool isShipVertical = rand() % 2 == 1;
        int shipStart = generateShip(ship, shipLength, isShipVertical, cells);

        for (int j = 0; j < shipLength; j++) {
            cells[shipStart + (isShipVertical ? j * 10 : j)] = ship;
        }
    }

    printGame(knownCells);

    int attempts = 0;

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
            for (int i = 0; i < 3; i++) {
                char ship = ships[i];

                if (cells[cell] == ship) {
                    shipPartsFound[i]++;
                }
            }

            knownCells[cell] = cells[cell];

            printf("Hit!\n");
        }

        attempts++;

        printf("Attempts: %d/40\n", attempts);
        printGame(knownCells);

        bool allShipPartsSunk = true;

        for (int i = 0; i < totalShips; i++) {
            if (shipPartsFound[i] < shipLengths[i]) {
                allShipPartsSunk = false;
            }
        }

        if (allShipPartsSunk) {
            printf("You won!\n");
            break;
        } else if (attempts >= 40) {
            printf("You lose!\n");
            printGame(cells);
            break;
        }
    }
}