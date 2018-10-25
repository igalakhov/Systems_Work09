all:
	gcc -o main.out main.c
	rm -f file.txt

run:
	./main.out
clean:
	rm -rf file.txt
	rm -rf *.out
