#include <stdio.h>
#include "triangle_routines.h"

#define NMOVES 36

int moves[NMOVES][3] = {
  {0, 1, 3},
  {0, 2, 5},
  {1, 3, 6},
  {1, 4, 8},
  {2, 4, 7},
  {2, 5, 9},
  {3, 1, 0},
  {3, 4, 5},
  {3, 6, 10},
  {3, 7, 12},
  {4, 7, 11},
  {4, 8, 13},
  {5, 2, 0},
  {5, 4, 3},
  {5, 8, 12},
  {5, 9, 14},
  {6, 3, 1},
  {6, 7, 8},
  {7, 4, 2},
  {7, 8, 9},
  {8, 4, 1},
  {8, 7, 6},
  {9, 5, 2},
  {9, 8, 7},
  {10, 6, 3},
  {10, 11, 12},
  {11, 7, 4},
  {11, 12, 13},
  {12, 7, 3},
  {12, 8, 5},
  {12, 11, 10},
  {12, 13, 14},
  {13, 8, 4},
  {13, 12, 11},
  {14, 13, 12},
  {14, 13, 12}
};
int npegs(int board[]);
int valid_move(int board[], int move[]);
void make_move(int board[], int move[]);
void unmake_move(int board[], int move[]);
int solve(int board[]);

int main(void) {
    int board[BOARD_SIZE];
    /* get board */
    triangle_input(board);
    /* solve board */
    solve(board);
    return 0;
}

/* Return the number of pegs on the board. */
int npegs(int board[]) {
  int i, pegs = 0;
  /* loop through and count pegs */
  for (i = 0; i < BOARD_SIZE; i++) {
    if (board[i] == 1) {
      pegs++;
    }
  }
  return pegs;
}

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]) {
  /* checks for valid move */
  if (board[move[0]] == 1 && board[move[1]] == 1 && board[move[2]] == 0) {
    return 1;
  }
  return 0;
}

/* Make this move on this board. */
void make_move(int board[], int move[]) {
  board[move[0]] = 0;
  board[move[1]] = 0;
  board[move[2]] = 1;
}

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]) {
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

/*
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order.
 */
int solve(int board[]) {
  int i;
  /* base case: solved board */
  if (npegs(board) == 1) {
    triangle_print(board);
    return 1;
  }
  /* recursive case: check each move for solved boards */
  for (i = 0; i < NMOVES; i++) {
    /* make sure the move is valid */
    if (valid_move(board, moves[i])) {
      /* perform move */
      make_move(board, moves[i]);
      /* recursively see if the board can be solved */
      if (solve(board)) {
        /* unmake the move */
        unmake_move(board, moves[i]);
        /* if the board can be solved print the board */
        triangle_print(board);
        return 1;
      }
      /* unmake the move */
      unmake_move(board, moves[i]);
    }
  }
  return 0;
}
