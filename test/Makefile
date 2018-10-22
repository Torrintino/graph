CFLAGS = -g -Wall -Werror -pedantic -std=c99
LDFLAGS = -Wl,--wrap,malloc,--wrap,realloc

.PHONY: clean

all: test_adjacency_list test_adjacency_matrix test_linked_list

test_adjacency_list: test_adjacency_list.c ../adjacency_list.c ../linked_list.c test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_adjacency_matrix: test_adjacency_matrix.c ../adjacency_matrix.c test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

test_linked_list: test_linked_list.c ../linked_list.c test.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm test_adjacency_matrix test_linked_list test_adjacency_list
