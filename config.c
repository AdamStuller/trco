#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONF_BUFF_LEN 512
#define CONF_MAX_NUM_LINES 10

struct CONFIG {
    char HOST_IP[16];
    int PORT;
};

void print_CONFIG(struct CONFIG s) {
    printf("HOST_IP=%s\nPORT=%d\n", s.HOST_IP, s.PORT);
}

int load_config(const char * config_file) {
    return 0;
}

int load_from_lines(char ** lines, int len, struct CONFIG *ss) {
    for (int i = 0; i < len; i++) {

        if (strstr(lines[i], "PORT=") != NULL) {
            char * s = strchr(lines[i], '=');
            int conv = atoi(s + 1);
            if (conv == 0) {
                return -1;
            }
            ss->PORT = atoi(s + 1);
        } else if (strstr(lines[i], "HOST_IP=") != NULL) {
            char * s = strchr(lines[i], '=');
            int l = strlen(s + 1);
            if (l > 16) {
                return -1;
            }
            strncpy(ss->HOST_IP, s + 1, 16);  
        }
    }
}



int main() {

    FILE* f = fopen("config.cfg", "r");
    if (f == NULL)
        exit(EXIT_FAILURE);
   
    // Extract tokens from the string s that are delimited by one of the bytes in delim.
    // char *strtok(char *s, const char *delim);
   
    char ** lines = (char **) malloc(CONF_MAX_NUM_LINES * sizeof(char*));
    bzero(lines, 10);
    if (lines == NULL)
        exit(EXIT_FAILURE);
    
    int c = 0, i = 0, j = 1, a = 0;
    char line_buf[CONF_BUFF_LEN];
    memset(line_buf, '\0', CONF_BUFF_LEN);
    
    lines[0] = line_buf;

    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            line_buf[i] = '\0';
            lines[j++] = &line_buf[i+1];
            i++;
        } else {
            line_buf[i] = c;
            i++;
            a++;
        }

    }
    struct CONFIG s;
    int r = load_from_lines(lines, j, &s);
    print_CONFIG(s);
    free(lines);
}