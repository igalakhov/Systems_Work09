all:
	gcc -o main.out main.c

run:
	./main.out
clean:
	rm -rf file.txt
	rm -rf *.out