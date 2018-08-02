#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CONF_BUFF_LEN 512
#define CONF_MAX_NUM_LINES 10

struct CONFIG {
    unsigned short PORT;
    char HOST_IP[16];
    char LOG_FILE[128];
    char DAT_FILE[128];
};

void print_CONFIG(struct CONFIG s);
void print_err(int errnum);
int load_from_lines(char ** lines, int len, struct CONFIG *ss);
int load_config(const char * config_file, struct CONFIG *s);