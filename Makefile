CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFLAGS = -DCHECK_PATH
GCC = gcc $(CFLAGS) $(TESTFLAGS)
EXEC = main
OBJS =  main.o sudoku.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

$(EXEC): $(OBJS) sudoku.h
	$(GCC) $(OBJS) -o $(EXEC) 

test: $(EXEC)
	./$(EXEC) testcases/sudoku1 output1
	./$(EXEC) testcases/sudoku2 output2
	./$(EXEC) testcases/sudoku3 output3
	./$(EXEC) testcases/sudoku4 output4
	./$(EXEC) testcases/sudoku5 output5

memory: $(EXEC)
	$(VALGRIND) --log-file=log1 ./$(EXEC) testcases/sudoku1 output1
	$(VALGRIND) --log-file=log2 ./$(EXEC) testcases/sudoku2 output2
	$(VALGRIND) --log-file=log3 ./$(EXEC) testcases/sudoku3 output3
	$(VALGRIND) --log-file=log4 ./$(EXEC) testcases/sudoku4 output4
	$(VALGRIND) --log-file=log5 ./$(EXEC) testcases/sudoku5 output5



%.o : %.c
	$(GCC) -c $< 

clean:
	rm -f main.o
	rm -f $(EXEC)
	rm -f id? name? log?
	rm -f output*