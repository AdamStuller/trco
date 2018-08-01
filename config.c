#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONF_BUFF_LEN 512
#define CONF_MAX_NUM_LINES 10

struct CONFIG {
    int PORT;
    char HOST_IP[16];
    char LOG_FILE[128];
    char DAT_FILE[128];
};

void print_CONFIG(struct CONFIG s) {
    printf("HOST_IP=%s\nPORT=%d\nLOG_FILE=%s\nDAT_FILE=%s\n", s.HOST_IP, s.PORT, s.LOG_FILE, s.DAT_FILE);
}

int load_config(const char * config_file) {
    return 0;
}

void print_err(int errnum) {
    switch(errnum) {
    case -1:
        printf("PORT IS NUMBER between 0 - 65535\n");
        break;
    case -2:
        printf("HOST_IP IS IP_V4 example: 127.0.0.1\n");
        break;
    case -3:
        printf("LOG_FILE IS file path to log file, name must be less than 128 chars\n");
        break;
    case -4:
        printf("DAT_FILE IS file path to data file, name must be less than 128 chars\n");
        break;
    }
}

int load_from_lines(char ** lines, int len, struct CONFIG *ss) {
    for (int i = 0; i < len; i++) {

        if (strstr(lines[i], "PORT=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            
            int conv = atoi(s + 1);
            if (conv == 0) {
                return -1;
            }
            ss->PORT = atoi(s);
        } else if (strstr(lines[i], "HOST_IP=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            
            int l = strlen(s);

            if (l > 15) {
                return -2;
            }
            *(s + l) = '\0';
            strncpy(ss->HOST_IP, s, l + 1);
            
        } else if (strstr(lines[i], "LOG_FILE=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            int l = strlen(s);
            if (l > 127) {
                return -3;
            }
            strncpy(ss->LOG_FILE, s, l + 1);


        } else if (strstr(lines[i], "DAT_FILE=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            int l = strlen(s);
            if (l > 127) {
                return -4;
            }
            strncpy(ss->DAT_FILE, s, l + 1);
        }
    }
    return 0;
}



int main() {

    FILE* f = fopen("config.cfg", "r");

    if (f == NULL)
        exit(EXIT_FAILURE);
   
    fseek(f, 0, SEEK_END); // seek to end of file
    int size = ftell(f); // get current file pointer
    if (size > CONF_BUFF_LEN - 1) {
        printf("Config file is too big. Max 511 chars.");
        exit(EXIT_FAILURE);
        fclose(f);
    }
    fseek(f, 0, SEEK_SET); // seek back to beginning of file
    // proceed with allocating memory and reading the file

    char * lines[CONF_MAX_NUM_LINES];
    bzero(lines, 10);
    
    if (lines == NULL)
        exit(EXIT_FAILURE);
    
    
    // Setup buffer for whole config
    char line_buf[CONF_BUFF_LEN];
    memset(line_buf, '\0', CONF_BUFF_LEN);
    
    // First line starts at line_buf[0]
    lines[0] = line_buf;

    int c, i = 0, j = 1;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
            line_buf[i] = '\0';
            lines[j++] = &line_buf[i+1];
            i++;
        } else {
            line_buf[i] = c;
            i++;
        }

    }
    struct CONFIG s;
    int r = load_from_lines(lines, j, &s);

    if (r == -1) {

    }

    print_CONFIG(s);
    
    fclose(f);
}