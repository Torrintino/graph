.PHONY: clean

print_adjacent_list: print_adjacent_list.c ../helpers.c
	gcc -o $@ -Wall -Werror -pedantic -std=c99 -g print_adjacent_list.c ../helpers.c ../adjacency_list.c ../linked_list.c

clean:
	rm print_adjacent_list
