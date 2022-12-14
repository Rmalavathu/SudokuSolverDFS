#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"

//Reads a file and returns a sudoku data type
Sudoku* readSudoku(char * sudokuFilename){

    //Open file
    FILE* inSudoku = fopen(sudokuFilename, "r");


    //Error check for opening file
    if (inSudoku == NULL) {
		fprintf(stderr, "Could not open sudoku file for reading\n");
		exit(1);
	}


    //Instantiate Sudokou to return
    Sudoku* s = malloc(sizeof(Sudoku));


    //Reads files using fscanf and does it row by row
    for (int i = 0; i < 9; i++) {
        fscanf(inSudoku, "%9c\n", s->sudoku[i]);
    }
    return s;
}

//Given a sudoku prints out into the terminal
void printSudoku(Sudoku * s){

    //Two loops to iterate through the sudoku array
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c", s->sudoku[i][j]);
        }
        printf("\n");
    }
}

//Checks if sudoku puzzle is solvable. Does this by checking if 
//All columns, rows and squares are unique using their respective functions.
//Unique means all different numbers excluding "."
bool checkSolved(Sudoku * s){
    // if (checkFilled(s) != true){
    //     return false;
    // }

    //Checks columns, rows and squares are all unique
    if (differentColumns(s) && differentRows(s) && differentSquares(s)){
        return true;
    }
    return false;
}

//Checks if sudoku puzzle is completely filled (no "."). Uses for loops and checks every value of sudoku puzzle.
bool checkFilled(Sudoku *s){

    char c;

    //Uses two for loops to iterate through the sudoku array to see that all values are between 1-9 if they are not empty values "."
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            c = s->sudoku[i][j];
            if( !(c >= '1' && c <= '9') ){
                return false;
            }
        }
    }

    return true;
}

//Checks if every row has unique numbers using unique function
bool differentRows(Sudoku * s){

    //uses two for loops and stores each row and checks if they are unique using isUnique function
    char temp[9];

    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++){
            temp[j] = s->sudoku[i][j];
        }
        if(!isUnique(temp)){
            return false;
        }
    }

    return true;
}

//Checks if every column has unique numbers using unique function
bool differentColumns(Sudoku * s){

        //uses two for loops and stores each column and checks if they are unique using isUnique function

        char temp[9];

    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++){
            temp[j] = s->sudoku[j][i];
        }
        if(!isUnique(temp)){
            return false;
        }
    }

    return true;
}

//Checks if every squares has unique numbers using unique function
bool differentSquares(Sudoku * s){

     //first two for loops finds the starting row and column for each square and the other two for loops iterate throught the squares and puts the values in a temporary array and checks if they are unique using isUnique function

    char temp[9];

    for(int row = 0; row < 9; row = row + 3){
        for(int col = 0; col < 9; col = col + 3){
            for(int r = row; r < row + 3; r++){
                for(int c = col; c < col + 3; c++){
                    temp[3*(r%3)+c%3] = s->sudoku[r][c];
                }
            }
            if(!isUnique(temp)){
                return false;
            }
        }
    }

    return true;
}

//Checks if the given char array has unique numbers excluding "."
bool isUnique(char * ch){

    //uses to loops to check values with each other to no check for dups and ignores "."

    for (int i = 0; i < 8; i++) {
        for (int j = i+1; j < 9; j++) {
            if (ch[i] != '.' && ch[i] == ch[j]){
                return false;
            }
        }
    }

    return true;
}

//Finds the next spot ("."). Gets the row and column position and changes the r and c variables
//passed in. 
void getEmpty(Sudoku * s, int * r, int * c){

    //uses 2 for loops to find the next location of "."
    //rather than returning the values, just changes the pointers
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++){
            if(s->sudoku[i][j] == '.'){
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

//The solving sudoku puzzle with DFS. Given the sudoku puzzle, it will check if the puzzle is filled or not.
//If the puzzle it will return True or else false. Then, it will find the next empty spot using the isEmpty function. Then, it will place
//a number between 1 and 9. After placing the number it will see if the puzzle is still solvable using the checkSolved function. If it is still
//solvable it will recursively call the depthFirstSolve function again. If the function returns true then it will also return true. If it goes through all numbers and nothing works
//It will return false. 
bool depthFirstSolve(Sudoku * s){
    //base case check to see if the puzzle was filled
    if(checkFilled(s)){
        //Checks if solved to determine if it passed or failed and returned corresponding boolean
        if(checkSolved(s)){
        return true;
        }
        return false;
    }

    //initialize row and column values
    int r = -1;
	int c = -1;


    //Set row and column location using getEmpty
	getEmpty(s, &r, &c);

    //printSudoku(s);
    //printf("\n%d %d \n", r, c);

    //Array of possible numbers
    char arr[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    //Goes through the possible numbers and plugs them into the puzzle
    for(int i = 0; i < 9; i++){
        s-> sudoku[r][c] = arr[i];
        //checks if new sudoku puzzle is valid
        if(checkSolved(s)){
            if(depthFirstSolve(s)){
                return true;
            }
        }
    }

    //removes changes to sudoku puzzle
    s->sudoku[r][c] = '.';
    return false;
    
}

//Writes sudoku puzzle into a passed in file
void writeSudoku(Sudoku * s, char * sudokuFilename){

    FILE* inSudoku = fopen(sudokuFilename, "w");

    //error opening writing files
    if (inSudoku == NULL) {
		fprintf(stderr, "Could not open sudoku output file for writing\n");
		exit(1);
	}

    //uses for loops to print the sudoku puzzle to files
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(inSudoku, "%c", s->sudoku[i][j]);
        }
        fprintf(inSudoku, "\n");
    }
}