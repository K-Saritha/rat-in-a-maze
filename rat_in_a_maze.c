
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROW 6
#define COL 8

typedef struct {
    int row;
    int col;
} POS;

typedef struct {
    POS data[ROW * COL];
    int top;
} STACK;

STACK* create_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->top = -1;
    return stack;
}

bool is_empty(STACK* stack) {
    return stack->top == -1;
}

void push(STACK* stack, POS spot) {
    stack->top++;
    stack->data[stack->top] = spot;
}

POS pop(STACK* stack) {
    POS spot = stack->data[stack->top];
    stack->top--;
    return spot;
}


MAZE PROGRAM:

#include "stack_h.h"

bool isValidSpot(int maze[][COL], int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL && maze[row][col] == 0);
}

void mouse_simulation(int maze[][COL], POS start, POS end) {
    STACK* visitStack = create_stack();
    STACK* altStack = create_stack();
    bool trap = false;
    bool goal = false;
    POS currentSpot = start;
    printf("(%d, %d)\n", currentSpot.row, currentSpot.col);
    while (!trap && !goal) {
        if (currentSpot.row == end.row && currentSpot.col == end.col) {
            goal = true;
            break;
        }
        maze[currentSpot.row][currentSpot.col] = 5;
        push(visitStack, currentSpot);
        int c = 0;
        POS nextSpot;

        if (isValidSpot(maze, currentSpot.row + 1, currentSpot.col)) {
            nextSpot.row = currentSpot.row + 1;
            nextSpot.col = currentSpot.col;
            push(altStack, nextSpot);
            c++;
        }
        if (isValidSpot(maze, currentSpot.row, currentSpot.col + 1)) {
            nextSpot.row = currentSpot.row;
            nextSpot.col = currentSpot.col + 1;
            push(altStack, nextSpot);
            c++;
        }
        if (isValidSpot(maze, currentSpot.row - 1, currentSpot.col)) {
            nextSpot.row = currentSpot.row - 1;
            nextSpot.col = currentSpot.col;
            push(altStack, nextSpot);
            c++;
        }
        if (isValidSpot(maze, currentSpot.row, currentSpot.col - 1)) {
            nextSpot.row = currentSpot.row;
            nextSpot.col = currentSpot.col - 1;
            push(altStack, nextSpot);
            c++;
        }
        if (c == 0) {
            if (is_empty(altStack)) {
                trap = true;
                break;
            }
            else {
                printf("\nBacktracking: (%d, %d) ", currentSpot.row, currentSpot.col);
                maze[currentSpot.row][currentSpot.col] = 0;
                while (!is_empty(altStack)) {
                    POS temp = pop(altStack);
                    currentSpot = temp;
                    printf("(%d, %d) ", currentSpot.row, currentSpot.col);
                    maze[currentSpot.row][currentSpot.col] = 0;
                }
                printf("\n");
            }
        }
        else {
            POS temp = pop(altStack);
            currentSpot = temp;
            printf("(%d, %d)\n", currentSpot.row, currentSpot.col);
        }
    }
    free(visitStack);
    free(altStack);

    if (trap) {
        printf("The mouse is trapped and cannot find the exit.\n");
    }
    else if (goal) {
        printf("Exit found! The mouse is free and receives a piece of cheese as a reward.\n");
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (maze[i][j] == 5) {
                    printf("* ");
                }
                else {
                    printf("%d ", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("The End point:(%d ,%d)",end.row,end.col);
    }
}

int main() {
    printf("Rat in the Maze:\n\n");
    int maze[ROW][COL] = {
        {1,1,1, 1, 1, 1, 1, 1, 1, 1},
        {1,0, 1, 0, 0, 0, 0, 0, 0,1},
        {1,0, 1, 0, 1, 1, 1, 1, 0,1},
        {1,0, 1, 0, 0, 0, 0, 1, 0,1},
        {1,0, 1, 1, 1, 1, 0, 1, 0,1},
        {1,0, 0, 0, 0, 0, 0, 1, 0,1},
        {1,0, 1, 1, 1, 1, 1, 1, 0,0},
        {1,1,1, 1, 1, 1, 1, 1, 1, 1}
    };
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++){
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    POS start;
    l1:printf("Enter starting point: ");
    scanf("%d %d", &(start.row), &(start.col));
    if(maze[start.row][start.col]==1){
        printf("Enter a Valid Position!!!\n");
        goto l1;
    }
    POS end = {6, 9};

    mouse_simulation(maze, start, end);

    return 0;
}

/*OUTPUT:

Enter starting point: 5
5
(5, 5)
(5, 4)
(5, 3)
(5, 2)
(5, 1)
(4, 1)
(3, 1)
(2, 1)
(1, 1)

Backtracking: (1, 1) (6, 1) (5, 6) 
(4, 6)
(3, 6)
(3, 5)
(3, 4)
(3, 3)
(2, 3)
(1, 3)
(1, 4)
(1, 5)
(1, 6)
(1, 7)
(1, 8)
(2, 8)
(3, 8)
(4, 8)
(5, 8)
(6, 8)
(6, 9)
Exit found! The mouse is free and receives a piece of cheese as a reward.
1 1 1 1 1 1 1 1 1 1 
1 0 1 * * * * * * 1 
1 * 1 * 1 1 1 1 * 1 
1 * 1 * * * * 1 * 1 
1 * 1 1 1 1 * 1 * 1 
1 * * * * * * 1 * 1 
1 0 1 1 1 1 1 1 * 0 
1 1 1 1 1 1 1 1 1 1 
The End point:(6 ,9)*/