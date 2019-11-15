all: compile test 

compile: playground.c tree_heap_test.c
	mkdir -p out
	gcc -o ./out/playground playground.c
	gcc -o ./out/tree_heap_test tree_heap_test.c

test: 
	./out/tree_heap_test

clean:
	rm -rf out
