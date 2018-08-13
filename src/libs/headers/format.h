#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Takes input as lines separated with CRLF
 * expected number of lines is indicated as int num_lines
 * @param len length of*/
char * format(char * input, int len, int num_lines);

char ** parse_input_CRLF(char * input, int len, int num_lines);