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

typedef struct {
    char symbol;
    int length;
    bool isVertical;
    int hits;
} Ship;

bool isShipOverlaid(int shipStart, Ship ship, char cells[100]) {
    for (int i = 0; i < ship.length; i++) {
        char cell = cells[shipStart + (ship.isVertical ? i * 10 : i)];

        if (cell != ship.symbol && cell != '*') {
            return true;
        }
    }

    return false;
}

bool isShipOverflow(int shipStart, Ship ship) {
    return ship.isVertical ? shipStart / 10 + ship.length > 10 : shipStart % 10 + ship.length > 10;
}

int generateShip(Ship ship, char cells[100]) {
    int shipStart = rand() % 100;

    do {
        shipStart = rand() % 100;
    } while (isShipOverflow(shipStart, ship) || isShipOverlaid(shipStart, ship, cells));

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

    Ship ships[] = {
        {'L', 4, rand() % 2 == 1, 0},
        {'M', 3, rand() % 2 == 1, 0},
        {'S', 2, rand() % 2 == 1, 0}
    };
    int totalShips = sizeof(ships) / sizeof(Ship);

    for (int i = 0; i < totalShips; i++) {
        int shipStart = generateShip(ships[i], cells);

        for (int j = 0; j < ships[i].length; j++) {
            cells[shipStart + (ships[i].isVertical ? j * 10 : j)] = ships[i].symbol;
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
                if (cells[cell] == ships[i].symbol) {
                    ships[i].hits++;
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
            if (ships[i].hits < ships[i].length) {
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