all: compile test 

compile: tree_heap_test.c
	mkdir -p out
	gcc -o ./out/tree_heap_test tree_heap_test.c

test: 
	./out/tree_heap_test

clean:
	rm -rf out
