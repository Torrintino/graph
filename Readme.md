# Graph algorithms and datastructures in C

Hello,
I created this repo for practice and because I need to work on graphs at the
university on a regular basis.

All files have in common, that all memory will be free'd, when a malloc or realloc call
fails.

## Tests

To test that all memory will be free'd, a special mock for malloc and realloc
has been created. They can be found in `test.c`.
To create the binaries for the tests use `make test`.
The usage of `valgrind` is recommended, to ensure that there are no memory
leakes.

## Helpers

helpers.h/helper.c contain some definitions and functions that are frequently
needed and/or do not fit into a particular exercise or module.

read_line is similar to get_line, however it only uses parts of the standard
library. get_ul is a variadic function that returns n unsigned long values
from a line it reads from stdin (using read_line). This functions aim at
providing an easy way to get integer values from user input in a safe way,
without using third party extensions like getline (which is POSIX standard,
but not yet part of every standard library). Compared to scanf, get_ul
is rather strict when comes to input format, it doesn't accept non-numeric
values and the line must contain exactly n values. It uses strtoul and hence
accepts negative values (converting them to unsigned long).
