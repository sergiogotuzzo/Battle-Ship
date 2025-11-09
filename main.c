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

bool isShipOverlaid(int ship, int shipLength, bool isShipVertical, int subShip, int subShipLenght, bool isSubShipVertical) {
    for (int i = 0; i < shipLength; i++) {
        for (int j = 0; j < subShipLenght; j++) {
            if ((ship + (isShipVertical ? i * 10 : i)) == (subShip + (isSubShipVertical ? j * 10 : j))) {
                return true;
            }
        }
    }

    return false;
}

bool isShipOverflow(int ship, int shipLength, bool shipIsVertical) {
    return shipIsVertical ? ship + (shipLength - 1) * 10 > 100 : ship % 10 > (10 - shipLength);
}

int generateShip(int shipLength, bool isShipVertical, int subShip, int subShipLength, bool isSubShipVertical) {
    int ship = rand() % 100;

    do {
        ship = rand() % 100;
    } while (isShipOverflow(ship, shipLength, isShipVertical) || isShipOverlaid(ship, shipLength, isShipVertical, subShip, subShipLength, isSubShipVertical));

    return ship;
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

    int longShipIsVertical = rand() % 2 == 1 ? true : false;
    int longShip = generateShip(4, longShipIsVertical, 0, 0, false);

    for (int i = 0; i < 4; i++) {
        cells[longShip + (longShipIsVertical ? i * 10 : i)] = 'L';
    }

    int mediumShipIsVertical = rand() % 2 == 1 ? true : false;
    int mediumShip = generateShip(3, mediumShipIsVertical, longShip, 4, longShipIsVertical);

    for (int i = 0; i < 3; i++) {
        cells[mediumShip + (mediumShipIsVertical ? i * 10 : i)] = 'M';
    }

    int shortShipIsVertical = rand() % 2 == 1 ? true : false;
    int shortShip = generateShip(2, shortShipIsVertical, mediumShip, 3, mediumShipIsVertical);

    for (int i = 0; i < 2; i++) {
        cells[shortShip + (shortShipIsVertical ? i * 10 : i)] = 'S';
    }

    printGame(knownCells);

    int attempts = 0;
    int longShipPartsFound = 0, mediumShipPartsFound = 0, shortShipPartsFound = 0;

    while (attempts < 40) {
        int x;
        char y;

        printf("Enter X (1-10) and Y (A-J)\n");
        scanf("%d %c", &x, &y);

        int cell = getCell(x, y);

        if (cells[cell] == '*') {
            knownCells[cell] = 'O';
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
        }

        attempts++;

        printGame(knownCells);

        if (longShipPartsFound == 4 && mediumShipPartsFound == 3 && shortShipPartsFound == 2) {
            printf("You won in %d attemps!", attempts);
            break;
        } else if (attempts == 40) {
            printf("You lose!");
            break;
        }
    }
}