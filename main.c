#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int getCell(char x, int y) {
    int iX = (x - 64) * 10 - 10;

    return iX + y;
}

void printTable(char table[100]) {
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
            printf("%c ", table[i * 10 + j]);

            if (j == 9) {
                printf("\n");
            }
        }
    }
}

bool isShipOverlaid(int indexShip, int indexShipLength, int ship, bool shipIsVertical) {
    if (shipIsVertical) {
        for (int i = 0; i < indexShipLength; i++) {
            if (indexShip + i * 10 == ship) {
                return true;
            }
        }
    } else return indexShip + indexShipLength == ship;
}

bool isShipOverflow(int ship, int shipLength, bool shipIsVertical) {
    return shipIsVertical ? ship + (shipLength - 1) * 10 > 100 : ship % 10 > (10 - shipLength);
}

int generateLongShip(bool longShipIsVertical) {
    int longShip = rand() % 100;

    do {
        longShip = rand() % 100;
    } while (isShipOverflow(longShip, 4, longShipIsVertical));

    return longShip;
}

int generateMediumShip(bool mediumShipIsVertical, int longShip, bool longShipIsVertical) {
    int mediumShip = rand() % 100;

    do {
        mediumShip = rand() % 100;
    } while (isShipOverflow(mediumShip, 3, mediumShipIsVertical) || isShipOverlaid(mediumShip, 3, longShip, longShipIsVertical));

    return mediumShip;
}

int generateShortShip(bool shortShipIsVertical, int mediumShip, bool mediumShipIsVertical) {
    int shortShip = rand() % 100;

    do {
        shortShip = rand() % 100;
    } while (isShipOverflow(shortShip, 2, shortShipIsVertical) || isShipOverlaid(shortShip, 2, mediumShip, mediumShipIsVertical));

    return shortShip;
}

int main() {
    char table[100];

    for (int i = 0; i < 100; i++) {
        table[i] = '*';
    }

    char knownTable[100];

    for (int i = 0; i < 100; i++) {
        knownTable[i] = '*';
    }

    srand((unsigned) time(NULL));

    int longShipIsVertical = rand() % 2 == 1 ? true : false;
    int longShip = generateLongShip(longShipIsVertical);

    for (int i = 0; i < 4; i++) {

        table[longShip + (longShipIsVertical ? i * 10 : i)] = 'L';

        printf("L: %d\n", longShip + i);
    }

    int mediumShipIsVertical = rand() % 2 == 1 ? true : false;
    int mediumShip = generateMediumShip(mediumShipIsVertical, longShip, longShipIsVertical);

    for (int i = 0; i < 3; i++) {
        table[mediumShip + (mediumShipIsVertical ? i * 10 : i)] = 'M';

        printf("M: %d\n", mediumShip + i);
    }

    int shortShipIsVertical = rand() % 2 == 1 ? true : false;
    int shortShip = generateShortShip(shortShipIsVertical, mediumShip, mediumShipIsVertical);

    for (int i = 0; i < 2; i++) {
        table[shortShip + (shortShipIsVertical ? i * 10 : i)] = 'S';

        printf("S: %d\n", shortShip + i);
    }

    printTable(table);

    int attempts = 0;

    while (attempts < 40) {
        char x;
        int y;

        printf("Enter Y (A-J) and X (1-10)\n");
        scanf("%c %d", &x, &y);

        int cell = getCell(x, y) - 1;

        // printf("%d\n", cell);
        // printf("%c\n", table[cell - 1]);

        int longShipPartsFound = 0, mediumShipPartsFound = 0, shortShipPartsFound = 0;

        if (table[cell] == '*') {
            knownTable[cell] = 'O';
        } else {
            switch (table[cell]) {
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

            knownTable[cell] = table[cell];
        }

        printTable(knownTable);

        if (longShipPartsFound == 4 && mediumShipPartsFound == 3 && shortShipPartsFound == 2) {
            break;
        }

        attempts++;
    }
}

/**
 *   1 2 3 4 5 6 7 8 9 10
 * A * * * * * * * * * *
 * B * * * * * * * * * * 
 * C * * * * * * * * * *
 * D * * * * * * * * * *
 * E * * * * * * * * * *
 * F * * * * * * * * * *
 * G * * * * * * * * * *
 * H * * * * * * * * * *
 * I * * * * * * * * * *
 * J * * * * * * * * * *
 */

//per buttare giù la nave lunga devi colpire tutti i 4 punti.
//per buttare giù la nave media devi colpire tutti i 3 punti.
//per buttare giù la nave corta devi colpire tutti i 2 punti.

// table[100] = {1...100}

// LUNGA = L
// MEDIA = M
// CORTA = C

// printTable(bool mostraNavi, int lunga[], int )