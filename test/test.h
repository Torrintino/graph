#ifndef TEST_H
#define TEST_H

/*** This module provides some macro for test case convenience.
     It also mocks malloc and realloc, so memory outages can be tested.
     To use the malloc mocks, the --wrap function of the linker needs
     to be used for malloc and realloc.

     Note that the module will continue to execute tests, when a test
     case fails

 ***/

int tests_run;
int tests_passed;
int MALLOC_CALLS;

#define FAIL() printf("Error in \"%s\" line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) {FAIL(); return 0;} } while(0)
#define _verify(test) do { tests_passed+=test(); tests_run++; turn_malloc_on(); } while(0)

/*** This must be called, before any test is run. ***/

void test_init();

/*** Call this function to always pass the actual malloc. ***/
void turn_malloc_on();

/*** All malloc calls will fail after n calls. Pass 0 to let all calls fail. 
     This function needs to be called for each test case. After a test case finished,
     malloc will automatically be enabled again.
 ***/
void turn_malloc_off(unsigned int n);

/*** Calling this optional. It will print a summary and return 
     TRUE if all tests passed, otherwise FALSE.
 ***/
int test_finish();

#endif
