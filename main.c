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

    int longShip = rand() % 100;

    do {
        longShip = rand() % 100;
    } while (longShip % 10 > 7);

    // printf("Long ship: ");

    for (int i = 0; i < 4; i++) {
        table[longShip + i] = 'L';

        // printf("%d ", longShip + i);
    }

    // printf("\n");

    int mediumShip = rand() % 100;

    do {
        mediumShip = rand() % 100;
    } while (mediumShip % 10 > 8);

    // printf("Medium ship: ");

    for (int i = 0; i < 3; i++) {
        table[mediumShip + i] = 'M';

        // printf("%d ", mediumShip + i);
    }

    // printf("\n");

    int shortShip = rand() % 100;

    do {
        shortShip = rand() % 100;
    } while (shortShip % 10 > 9);

    // printf("Short ship: ");

    for (int i = 0; i < 3; i++) {
        table[shortShip + i] = 'S';

        // printf("%d ", shortShip + i);
    }

    // printf("\n");

    printTable(knownTable);

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