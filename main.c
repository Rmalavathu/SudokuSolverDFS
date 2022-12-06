#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku.h"

int main(int argc, char * * argv)
{
    if (argc != 3) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./hw9 [mazeFile] [pathFile]\n");
		return EXIT_FAILURE;
	}

    Sudoku * s = readSudoku(argv[1]);
    //printSudoku(s);

	
	//printf("%d", checkSolved(s));
	depthFirstSolve(s);
	//printSudoku(s);
	writeSudoku(s, argv[2]);

	free(s);
}