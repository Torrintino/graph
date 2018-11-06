CFLAGS = -g -Wall -Werror -pedantic -std=c99
LDFLAGS = -Wl,--wrap,malloc,--wrap,realloc

TEST_CASES = test_adjacency_list test_adjacency_matrix test_linked_list

.PHONY: clean

all: test_adjacency_list test_adjacency_matrix test_linked_list

test_adjacency_list: test_adjacency_list.c ../adjacency_list.c ../linked_list.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_adjacency_matrix: test_adjacency_matrix.c ../adjacency_matrix.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_linked_list: test_linked_list.c ../linked_list.c framework/test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm test_adjacency_matrix test_linked_list test_adjacency_list

test: $(TEST_CASES)
	valgrind ./test_adjacency_list
	valgrind ./test_adjacency_matrix
	valgrind ./test_linked_list
