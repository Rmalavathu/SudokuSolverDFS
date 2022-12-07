#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"

int main(int argc, char * * argv)
{
	//Looks for input to have 4 inputs for running file, sudoku input file, and output file
    if (argc != 3) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./main [sudokuFile] [pathFile]\n");
		return EXIT_FAILURE;
	}

	//Reads input file and gives out sudoku struct type
    Sudoku * s = readSudoku(argv[1]);
    //printSudoku(s);

	
	//printf("%d", checkSolved(s));

	//Solves the sudoku puzzle
	depthFirstSolve(s);
	//printSudoku(s);

	//Writes the solved sudoku puzzle to a file
	writeSudoku(s, argv[2]);

	free(s);
}