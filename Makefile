default: *.c *.h
	mkdir -p bin
	gcc -Wall -o bin/test_sbnf test_sbnf.c sbnf.c
	./bin/test_sbnf
