#include "headers/format.h"
#define MAX_ROW_LEN 1024


/**
 * Remove commas from input string
 */
char * remove_illegal_chars(char * input, int len) {
    char * safe_buffer = (char *) malloc(sizeof(char) * len);
    
    if (safe_buffer == NULL) {
        return NULL;
    }

    memset(safe_buffer, '\0', len);

    // omit illegal characted ','
    for (int i = 0, j = 0; i < len; i++) {
        if (input[i] != ',') {
            safe_buffer[j++] = input[i];
        }
    }

    return safe_buffer;
}

/**
 * Explode lines separated with CRLF(\r\n)
 * int num_lines represents expected number of lines that are coming
 */
char ** parse_input_CRLF(char * input, int len, int num_lines) {
    char ** lines = (char **) malloc(sizeof(char *) * num_lines);

    if (lines == NULL) {
        return NULL;
    }

    char internal_buffer[MAX_ROW_LEN];
    memset(internal_buffer, '\0', MAX_ROW_LEN);

    int current_num_lines = 0;
    for (int i = 0, j = 0; i < len; j++, i++) {
        // CRLF, we are at end of line, omits other lines which are out of num_of_lines boundary
        if (input[i - 1] == '\r' && input[i] == '\n') { 
            
            // OK case
            if (current_num_lines < num_lines) {

                if (j - 1 > MAX_ROW_LEN) {
                    // ERROR
                    for (int i = 0; i < current_num_lines; i++)
                        free(lines[current_num_lines]);
                    free(lines);
                    return NULL;
                }

                lines[current_num_lines] = (char *) malloc(sizeof(char) * j - 1);
                // j - 1 omits CRLF from internal_buffer
                strncpy(lines[current_num_lines], internal_buffer, j-1);
                j = -1;
            }

            // MALFOMED, incoming lines are more than expected
            if (++current_num_lines > num_lines) {
                for (int i = 0; i < current_num_lines; i++)
                    free(lines[i]);
                free(lines);
                return NULL;
            }
        } else {
            internal_buffer[j] = input[i];
        }
    }

    // there was not enough lines as expected
    if (current_num_lines < num_lines) {
        for (int i = 0; i < current_num_lines; i++)
            free(lines[i]);
        free(lines);
        return NULL;
    }

    return lines;
}

/**
 * Appends lines with delimiter ','
 * without trailing ','
 */
char * append_lines(char ** lines, int num) {
    char * output = (char*) malloc(sizeof(char) * num * MAX_ROW_LEN);
    if (output == NULL)
        return NULL;

    bzero(output, num * MAX_ROW_LEN);

    int j = 0;
    for (int i = 0; i < num; i++) {
        int line_len = strlen(lines[i]);
        strncpy(&output[j], lines[i], line_len);
        
        j += line_len;

        if (i < num - 1) {
            output[j] = ',';
            j++;
        }
    }

    return output;
} 

/**
 * Prepares input to store on disk
 * validates input
 * removes illegal character ','
 * return char bytes instead NULL if error occured.
 */
char * format (char * input, int len, int num_lines) {
    char * safe_buffer = remove_illegal_chars(input, strlen(input));
    if (safe_buffer == NULL) {
        free(safe_buffer);
        return NULL;
    }
    char ** lines = parse_input_CRLF(safe_buffer, strlen(safe_buffer), num_lines);

    free(safe_buffer);

    if (lines == NULL)
        return NULL;

    char * output = append_lines(lines, num_lines);    
    if (output == NULL) {
        free(output);
        return NULL;
    }
    
    for (int i = 0; i < num_lines; i++)
        free(lines[i]);
    free(lines);

    return output;
}
