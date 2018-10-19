TEST_FILES = test_adjacency_matrix.c
SOURCE = adjacency_matrix.c helpers.c test.c
CFLAGS = -g -Wall -Werror -pedantic -std=c99 -Wl,--wrap,malloc

.PHONY: test clean

test: $(TEST_FILES) $(SOURCE)
	gcc $(CFLAGS) -o test_adjacency_matrix test_adjacency_matrix.c adjacency_matrix.c helpers.c test.c

clean:
	rm test_adjacency_matrix
