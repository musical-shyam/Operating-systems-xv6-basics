all: task1 task2 task3 signal
	
task1: task1.c
	gcc -static task1.c -o $@

task2: task2.c
	gcc -static task2.c -o $@

task3: task3.c
	gcc -static task3.c -o $@

signal: sig.c
	gcc -static sig.c -o $@


clean:
	rm -f task1 task2 task3 sig
