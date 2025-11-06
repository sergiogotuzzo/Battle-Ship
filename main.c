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

int generateLongShip() {
    int longShip = rand() % 100;

    do {
        longShip = rand() % 100;
    } while (longShip % 10 > 6);

    return longShip;
}

int generateMediumShip(int longShip) {
    int mediumShip = rand() % 100;

    do {
        mediumShip = rand() % 100;
    } while (mediumShip % 10 > 7 || longShip + 3 == mediumShip);

    return mediumShip;
}

int generateShortShip(int mediumShip) {
    int shortShip = rand() % 100;

    do {
        shortShip = rand() % 100;
    } while (shortShip % 10 > 8 || mediumShip + 2 == shortShip);

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

    int longShip = generateLongShip();

    for (int i = 0; i < 4; i++) {
        table[longShip + i] = 'L';

        printf("L: %d\n", longShip + i);
    }

    int mediumShip = generateMediumShip(longShip);

    for (int i = 0; i < 3; i++) {
        table[mediumShip + i] = 'M';

        printf("M: %d\n", mediumShip + i);
    }

    int shortShip = generateShortShip(mediumShip);

    for (int i = 0; i < 2; i++) {
        table[shortShip + i] = 'S';

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