#include "protocol.h"
#include <string.h>

/**
 * Allocate new message with size of header.size
 * returned as buf arg.
 */
int msg_to_bytes(struct Message m, unsigned char** buf) {
    // buf = (unsigned char *) malloc(sizeof(unsigned char*) * sizeof(struct Message));
    // if (buf == NULL)
    //     return -1;
    // buf = (unsigned char*)&m;
    *buf = (unsigned char*)&m;
    return 0;
}

/**
 * Convert Bytes to message of len
 */
int bytes_to_msg(struct Message *m, unsigned char *buf, int body_len) {
    // first 8 bytes is header
    struct Message_Header mh;
    mh.size = (uint16_t) *(buf + 1) << 8 | *(buf + 0); // 2B
    mh.count = (uint16_t) *(buf + 3) << 8 | *(buf + 2); // 2B
    mh.order = (uint16_t) *(buf + 5) << 8 | *(buf + 4); // 2B
    mh.type = (uint16_t) *(buf + 7) << 8 | *(buf + 6); // 2B
    
    m->header = mh;
    

    // max 412 iters
    for (int i = 8, j = 0; i < body_len; i++)
        m->body[j++] = buf[i]; 

    return 0;
}