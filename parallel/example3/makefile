hello:hello.o
	gcc -o hello hello.o
test: test.o
	gcc -g -lm -o test test.o
test.o: test.c
	gcc -c test.c
hello_p:hello_p.o
	mpicc -o hello_p hello_p.o
hello_p.o:hello_p.c
	mpicc -c hello_p.c
#%:%.c
#	gcc -c $*.c
%:%.c
	mpicc -o $@ $*.c
.PHONY:clean
clean:
	-rm *.o
