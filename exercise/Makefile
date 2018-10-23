.PHONY: clean

all: assignment_problem print_adjacent_list

assignment_problem: assignment_problem.c ../helpers.c ../adjacency_matrix.c
	gcc -o $@ -Wall -Werror -pedantic -std=c99 -g $^

print_adjacent_list: print_adjacent_list.c ../helpers.c ../adjacency_list.c ../linked_list.c
	gcc -o $@ -Wall -Werror -pedantic -std=c99 -g $^

clean:
	rm print_adjacent_list assignment_problem
