#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdbool.h>

typedef struct Sudoku {
    char sudoku[9][9];
} Sudoku;


//Reads a file and returns a sudoku data type
Sudoku * readSudoku(char * sudokuFilename);

//Given a sudoku prints out into the terminal
void printSudoku(Sudoku * s);

//Checks if sudoku puzzle is solvable. 
bool checkSolved(Sudoku * s);

//Checks if sudoku puzzle is completely filled (no ".")
bool checkFilled(Sudoku *s);

//Checks if every row has unique numbers using unique function
bool differentRows(Sudoku * s);

//Checks if every column has unique numbers using unique function
bool differentColumns(Sudoku * s);

//Checks if every squares has unique numbers using unique function
bool differentSquares(Sudoku * s);

//Checks if the given char array has unique numbers excluding "."
bool isUnique(char * ch);

//Finds the next spot (".")
void getEmpty(Sudoku * s, int * r, int * c);

//The solving sudoku puzzle with DFS
bool depthFirstSolve(Sudoku * s);

//Writes sudoku puzzle into a passed in file
void writeSudoku(Sudoku * s, char * sudokuFilename);

#endif