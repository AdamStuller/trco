#include "headers/format.h"
#define MAX_ROW_LEN 1024
#define NUMBER_OF_INPUT_LINES 3

/**
 * Remove commas from input string
 */
unsigned char * remove_illegal_chars(char * input, int len) {
    unsigned char * safe_buffer = (char *) malloc(sizeof(char) * len);
    
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
 */
char ** parse_input_CRLF(char * input, int len, int num_lines) {
    char ** lines = (char **) malloc(sizeof(char *) * num_lines);
    int num_of_lines = 0; // for validation of number of lines

    if (lines == NULL) {
        return NULL;
    }
    // alloc lines
    for (int i = 0; i < num_lines; i++) {
        lines[i] = (char *) malloc(sizeof(char) * MAX_ROW_LEN);
        if (lines[i] == NULL) {
            return NULL;
        }
    }

    char internal_buffer[MAX_ROW_LEN];
    memset(internal_buffer, '\0', MAX_ROW_LEN);

    for (int i = 0, j = 0; i < len; j++, i++) {
        // CRLF, we are at end of line
        if (input[i - 1] == '\r' && input[i] == '\n' && num_of_lines < NUMBER_OF_INPUT_LINES) { 
            lines[num_of_lines] = (char *) malloc(sizeof(char) * j - 1);
            // j - 1 omits CRLF from internal_buffer
            strncpy(lines[num_of_lines], internal_buffer, j-1);
            j = -1;
            num_of_lines++;
        } else {
            internal_buffer[j] = input[i];
        }
    }
    return lines;
}

/**
 * Appends lines with delimiter ','
 * without trailing ','
 */
char * append_lines(char ** lines, int num) {
    char * output = (char*) malloc(sizeof(char) * NUMBER_OF_INPUT_LINES * MAX_ROW_LEN + 3);
    if (output == NULL)
        return NULL;

    bzero(output, NUMBER_OF_INPUT_LINES * MAX_ROW_LEN + 3);

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
    if (safe_buffer == NULL)
        return NULL;
    char ** lines = parse_input_CRLF(safe_buffer, strlen(safe_buffer), num_lines);
    if (lines == NULL)
        return NULL;
    char * output = append_lines(lines, num_lines);    
    if (output == NULL)
        return NULL;
    
    free(safe_buffer);
    for (int i = 0; i < num_lines; i++)
        free(lines[i]);
    free(lines);

    return output;
}


char ** parse_keys(char *input, int * keys_num) {
    int num_commas = 0;
    char * head = input;
    while(*head != '\0') {
        if (*head == ',')
            num_commas++;
        head++;
    }
 
    *keys_num = num_commas;

    char ** keys = (char**) malloc(sizeof(char*) * num_commas);
    char internal_buffer[256];
    
    bzero(internal_buffer, 256);
    
    for (int i = 0, j = 0; i < num_commas; i++) {
        while (*input != '\0') {
            if (*input == ',') {
                strncpy(keys[i], internal_buffer, j - 1);
                j = 0;
            } else {
                internal_buffer[j++] = *input;
            }
            input += 1;
        }
        
        // internal_buffer[j] = 
        // j++;
    }
    return keys;
}

/**
 * Returns correct input line(CRLF) according keys:value pairs
 * order according to keys order
 */
char * encode_keypairs(char * keys, char * input, int len, int num_lines) {
    // encode_keypairs("wifi,host,something", "wifi:something\r\nhost:yolo\r\nsomething:sss\r\n"); -> correct order of something\r\n ...
    char * safe_buffer = remove_illegal_chars(input, strlen(input));
    char ** lines = parse_input_CRLF(safe_buffer, len, num_lines);

    // if ()


    // char *strstr(const char *haystack, const char *needle);
    int found = 0;
    for (int i = 0; i < num_lines; i++) {
        
        // if (strstr() == NULL) {

        // } else {
        //     found = 1;
        // }
    }
    return NULL;
}

// int main() {
//     char *input = "Jello\r\nWorld\r\nMotfuckrs\r\n\0";
//     char *keys = "wifi,hocico";
//     // printf("%s\n", format(input, strlen(input), 3));
//     int num_of_keys = 0;
//     char ** ks =  parse_keys(keys,&num_of_keys);
//     return 0;
// }