
.PHONY: test
test: main
	./a.out 1157

main: main.c
	gcc main.c -o a.out
