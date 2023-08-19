CC= gcc -Werror
AR= ar
DEL = del
OBJ := ./build/$(wildcard *.o)
all: compile_OBJ combine mtest run



compile_OBJ:
	$(CC) src/errorHandler.c -c -o build/errorHandler.o
	$(CC) src/matrix_utils.c -c -o build/matrix_utils.o
	$(CC) src/matrix_math.c -c -o build/matrix_math.o
	$(CC) src/iterators.c -c -o build/iterators.o
	
	
combine:
	$(AR) rvs build/matrix.a build/*.o

mtest:
	$(CC) test/test.c build/matrix.a -o build/test.exe
	$(CC) test/iteratorTests.c build/matrix.a -o build/iteratorTests.exe

run:
	build/test.exe
	build/iteratorTests.exe


clean: 
	del build
