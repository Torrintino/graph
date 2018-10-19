#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

/* read_line allocates memory as needed, 
   so the pointer has to be free'd by the caller ***/
#define RL_BUFFER_SIZE 80
char* read_line() {
  int buffer_size = RL_BUFFER_SIZE;
  int position = 0, c;
  
  char* buffer = malloc(sizeof(char) * buffer_size);
  if(!buffer) return NULL;

  while(1) {
    c = getchar();

    if(c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if(position >= buffer_size) {
      buffer_size += RL_BUFFER_SIZE;
      buffer = realloc(buffer, buffer_size * sizeof(char));
      if(!buffer) return NULL;
    }
  }
}

/*** get "n" unsigned long values from input, which are delimted by " \t"
     RETURNS TRUE for success and FALSE for failure
***/
int get_ul(int n, ...) {
  va_list args;
  va_start(args, n);

  char* line = read_line();
  if(line == NULL) {
    fprintf(stderr, "get_ul: Allocation error\n");
    return FALSE;
  }
  
  for(int i=0; i<n; i++) {
    unsigned long* input = va_arg(args, unsigned long*);
    char* token = (i==0) ? strtok(line, " \t") : strtok(NULL, " \t");
    if(token == NULL) {
      fprintf(stderr, "get_ul: Invalid format\n");
      return FALSE;
    }
    
    if(i == n-1) {
      if(strtok(NULL, " \t") != NULL) {
	fprintf(stderr, "get_ul: Invalid format\n");
	return FALSE;
      }
    }

    errno = 0;
    char* endptr;
    *input = strtoul(token, &endptr, 10);
    if(errno != 0 ||
       endptr == line ||
       *endptr != '\0') {
      fprintf(stderr, "get_ul: Invalid value\n");
      return FALSE;
    }
  }

  free(line);
  va_end(args);
  return TRUE;
}
