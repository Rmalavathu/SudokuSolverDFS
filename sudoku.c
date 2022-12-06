#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"

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

void printSudoku(Sudoku * s){

    //Two loops to iterate through the sudoku array
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c", s->sudoku[i][j]);
        }
        printf("\n");
    }
}

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