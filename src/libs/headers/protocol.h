#include <stdint.h>
#include <stdlib.h>

#define MESSAGE_BODY_LEN 412
#define MESSAGE_HEADER_LEN 7

struct Message_Header {
    uint16_t size;
    uint16_t count;
    uint16_t order;
    uint16_t type;
};

struct Message {
    struct Message_Header header;
    char body[MESSAGE_BODY_LEN];
};

int msg_to_bytes(struct Message m, unsigned char** buf);
int bytes_to_msg(struct Message *m, unsigned char *buf, int body_len);