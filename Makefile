TEST_FILES = test_adjacency_matrix.c
SOURCE = adjacency_matrix.c helpers.c test.c
CFLAGS = -g -Wall -Werror -pedantic -std=c99
LDFLAGS = -Wl,--wrap,malloc,--wrap,realloc

.PHONY: test clean

test: $(TEST_FILES) $(SOURCE)
	gcc $(CFLAGS) $(LDFLAGS) -o test_adjacency_matrix test_adjacency_matrix.c adjacency_matrix.c helpers.c test.c
	gcc $(CFLAGS) $(LDFLAGS) -o test_linked_list test_linked_list.c linked_list.c test.c helpers.c

clean:
	rm test_adjacency_matrix test_linked_list
