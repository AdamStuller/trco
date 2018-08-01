#include "config.h"

void print_CONFIG(struct CONFIG s) {
    printf("HOST_IP=%s\nPORT=%d\nLOG_FILE=%s\nDAT_FILE=%s\n", s.HOST_IP, s.PORT, s.LOG_FILE, s.DAT_FILE);
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
            
            int conv = atoi(s);
            if (conv <= 0 || conv > 2<<16 - 1) {
                return -1;
            }
            ss->PORT = (unsigned short)conv;
        } else if (strstr(lines[i], "HOST_IP=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            
            int l = strlen(s);

            if (l > 2<<4 - 1) {
                return -2;
            }
            *(s + l) = '\0';
            strncpy(ss->HOST_IP, s, l + 1);
            
        } else if (strstr(lines[i], "LOG_FILE=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            int l = strlen(s);
            if (l > 2<<8 - 1) {
                return -3;
            }
            strncpy(ss->LOG_FILE, s, l + 1);


        } else if (strstr(lines[i], "DAT_FILE=") != NULL) {
            char * s = strchr(lines[i], '=');
            s += 1; // shift to right, omit '='
            int l = strlen(s);
            if (l > 2<<8 - 1) {
                return -4;
            }
            strncpy(ss->DAT_FILE, s, l + 1);
        }
    }
    return 0;
}


/**
 * Loads config file and fills the struct CONFIG
 * Returns zero on success 
 */
int load_config(const char * config_file, struct CONFIG *s) {

    FILE* f = fopen(config_file, "r");

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
    bzero(lines, CONF_MAX_NUM_LINES);
    
    // Setup buffer for whole config
    char line_buf[CONF_BUFF_LEN];
    memset(line_buf, '\0', CONF_BUFF_LEN);
    
    // First line starts at line_buf[0]
    lines[0] = line_buf;
    // Load other lines to *lines[]
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
    
    int r = load_from_lines(lines, j, s);

    if (r != 0) {
        print_err(r);
        return -1;
        fclose(f);
    }
    
    fclose(f);
    return 0;
}

// int main() {
//     struct CONFIG s;
//     int e = load_config("config.cfg", &s);
//     if (e != 0) {
//         exit(EXIT_FAILURE);
//     }
//     print_CONFIG(s);
//     exit(EXIT_SUCCESS);
// }