#include <stdio.h>
#include <stdlib.h>
#include "cvarint.h"

#define EXIT_ERR(msg) { \
        printf("%s\n", msg); \
        exit(-1); \
    }

int main(int argc, char** argv)
{
    
    Byte* out = NULL;
    uint8_t byte_size;
    int e = encode_varint(300, &out, &byte_size);

    if (e != 0)
    {
        free(out);
        EXIT_ERR("error encode varint");
    }

    printf("byte size: %d\n", byte_size);

    for (uint32_t i = 0; i < byte_size; i++)
        printf("%d\n", out[i]);

    printf("-------------\n");
    Byte data[2] = {172, 2};
    uint64_t decoded_varint = 0;
    int d = decode_varint(data, &decoded_varint, byte_size);
    if (d != 0)
    {
        free(out);
        EXIT_ERR("error decode varint");
    }

    printf("decoded varint: %llu\n", decoded_varint);

    // make sure to free the resources
    free(out);

    return 0;
}