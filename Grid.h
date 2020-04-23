#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 100
#define COLS 100
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define WHITE "\033[m"

class Grid
{
public:
    Grid();

    typedef struct {
        char token;
        int  weight;
        bool isInfected;
    } Position;

    void initialize_grid(Position grid[][COLS]) {
        for (int r = 0; r < ROWS; r++)
            for (int c = 0; c < COLS; c++) {
                grid[r][c].token = '0';
                grid[r][c].weight = rand() % 100;
                grid[r][c].isInfected = false;
            }
    };

    void print_grid(Position grid[][COLS]) {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (grid[r][c].weight < 20)
                    printf(YELLOW);
                else if (grid[r][c].isInfected)
                    printf(RED);
                printf(" %c", grid[r][c].token);
                printf(WHITE);
            }
            printf("\n");
        }
    };

private:

};



Grid::Grid()
{
    srand((unsigned)time(NULL));
    Position grid[ROWS][COLS];
    initialize_grid(grid);
    print_grid(grid);
}
