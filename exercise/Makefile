TRASH = print_adjacent_list assignment_problem log.txt test_output

.PHONY: clean test

all: assignment_problem print_adjacent_list

assignment_problem: assignment_problem.c ../helpers.c ../adjacency_matrix.c ../hungarian.c
	gcc -o $@ -Wall -Werror -pedantic -std=c99 -g $^

print_adjacent_list: print_adjacent_list.c ../helpers.c ../adjacency_list.c ../linked_list.c
	gcc -o $@ -Wall -Werror -pedantic -std=c99 -g $^

clean:
	rm $(TRASH) 2> /dev/null || true

test: assignment_problem
	../test/framework/valgrind_test.py ./assignment_problem -i test_cases/assignment_problem.in -o test_cases/assignment_problem.out
