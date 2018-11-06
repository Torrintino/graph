CFLAGS = -g -Wall -Werror -pedantic -std=c99
LDFLAGS = -Wl,--wrap,malloc,--wrap,realloc

TEST_CASES = test_adjacency_list test_adjacency_matrix test_linked_list
OUTPUT_FILES = adjacency_list.txt adjacency_matrix.txt linked_list.txt

.PHONY: clean

all: test_adjacency_list test_adjacency_matrix test_linked_list

test_adjacency_list: test_adjacency_list.c ../adjacency_list.c ../linked_list.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_adjacency_matrix: test_adjacency_matrix.c ../adjacency_matrix.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_linked_list: test_linked_list.c ../linked_list.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm test_adjacency_matrix test_linked_list test_adjacency_list log.txt

test: $(TEST_CASES) $(OUTPUT_FILES)
	framework/valgrind_test.py ./test_adjacency_list -o adjacency_list.txt
	framework/valgrind_test.py ./test_adjacency_matrix -o adjacency_matrix.txt
	framework/valgrind_test.py ./test_linked_list -o linked_list.txt
