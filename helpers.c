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

/*** Helper function for get_ul and get_ul_array
     Get the next token from given line and parse it to unsigned long
     With the first call a pointer to the line must be given, with all subsequent
     calls for the same line, NULL must be passed.

     Returns FALSE if any input errors occured
 ***/
int get_ul_token(char* line, unsigned long* input) {
  char* token = strtok(line, " \t");
  if(token == NULL) {
    fprintf(stderr, "get_ul_token: Invalid format\n");
    return FALSE;
  }

  errno = 0;
  char* endptr;
  *input = strtoul(token, &endptr, 10);
  if(errno != 0 ||
     endptr == line ||
     *endptr != '\0') {
    fprintf(stderr, "get_ul_token: Invalid value\n");
    return FALSE;
  }
  return TRUE;
}

/*** get "n" unsigned long values from input, which are delimted by " \t"
     n pointers need to be passed as arguments, 
     which will be set to the values from input.

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
    if(!get_ul_token((i == 0) ? line : NULL, input)) {
      free(line);
      return FALSE;
    }
  }

  if(strtok(NULL, " \t") != NULL) {
    fprintf(stderr, "get_ul: Invalid format\n");
    free(line);
    return FALSE;
  }

  free(line);
  va_end(args);
  return TRUE;
}

/*** Gets n values from a line from stdin.
     The space for array needs to be allocated by the user.

     RETURNS TRUE for success and FALSE for failure
 ***/
int get_ul_array(int n, unsigned long* array) {
  char* line = read_line();
  if(line == NULL) {
    fprintf(stderr, "get_ul_array: Allocation error\n");
    return FALSE;
  }
  
  for(int i=0; i<n; i++) {
    if(!get_ul_token((i == 0) ? line : NULL, &array[i])) {
      free(line);
      return FALSE;
    }
  }

  if(strtok(NULL, " \t") != NULL) {
    fprintf(stderr, "get_ul_array: Invalid format\n");
    free(line);
    return FALSE;
  }

  free(line);
  return TRUE;
}
