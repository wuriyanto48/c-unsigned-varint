#ifndef HEADER_VARINT_H
#define HEADER_VARINT_H

#include <stdio.h>
#include <stdlib.h>

typedef uint8_t Byte;

static const uint8_t CONTINUATION_BIT_MASK = 0x1 << 7;
static const uint8_t EIGHT_BIT_MASK = 0xFF;
static const uint8_t SEVEN_BIT_MASK = 0x7F;

static const uint64_t MAX_ONE_BYTES = 2UL << 6;
static const uint64_t MAX_TWO_BYTES = 2UL << 13;
static const uint64_t MAX_THREE_BYTES = 2UL << 20;
static const uint64_t MAX_FOUR_BYTES = 2UL << 27;
static const uint64_t MAX_FIVE_BYTES = 2UL << 34;
static const uint64_t MAX_SIX_BYTES = 2UL << 41;
static const uint64_t MAX_SEVEN_BYTES = 2UL << 48;
static const uint64_t MAX_EIGHT_BYTES = 2UL << 55;
static const uint64_t MAX_NINE_BYTES = 2UL << 62;

static void reverse(Byte* buf, Byte* out, int byte_size)
{
    int j = 0;
    for (int i = byte_size-1; i > -1; i--)
    {
        out[i] = buf[j];
        j++;
    }
}

static void move(uint64_t num, uint8_t byte_size, int base_shift, Byte* out)
{
    Byte _out[byte_size];
    for (uint64_t i = 0; i < byte_size; i++) 
    {
        uint64_t r_shift = base_shift - i * 7;
        if (i == 0)
        {
            uint64_t b = (num >> r_shift) & EIGHT_BIT_MASK;
            _out[i] = (Byte) b;
        } else
        {
            uint64_t b = ((num >> r_shift) & EIGHT_BIT_MASK) | CONTINUATION_BIT_MASK;
            _out[i] = (Byte) b;
        }
    }

    reverse(_out, out, (int)byte_size);
}

// 128   => 10000000 00000001
int encode_varint(uint64_t num, Byte** out, uint8_t* byte_size)
{
    if (num < MAX_ONE_BYTES)
    {
        uint8_t bs = 1;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        _out[0] = num;
        
        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_TWO_BYTES)
    {
        uint8_t bs = 2;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 7, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_THREE_BYTES)
    {
        uint8_t bs = 3;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 14, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_FOUR_BYTES)
    {
        uint8_t bs = 4;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 21, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_FIVE_BYTES)
    {
        uint8_t bs = 5;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 28, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_SIX_BYTES)
    {
        uint8_t bs = 6;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 35, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_SEVEN_BYTES)
    {
        uint8_t bs = 7;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 42, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_EIGHT_BYTES)
    {
        uint8_t bs = 8;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 49, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    if (num < MAX_NINE_BYTES)
    {
        uint8_t bs = 9;
        Byte* _out = (Byte*) malloc(sizeof(Byte) * bs);
        move(num, bs, 56, _out);

        *out = _out;
        *byte_size = bs;
        return 0;
    }

    // # return error if byte size greater than 9 bytes 
    return -1;
}

int decode_varint(Byte* buf, uint64_t* out, uint8_t byte_size)
{
    // initialize value
    *out = 0;

    Byte reversed_buf[byte_size];
    reverse(buf, reversed_buf, (int)byte_size);

    uint64_t _out = 0;
    for (uint32_t i = 0; i < byte_size; i++)
    {
        uint8_t l_shift = (7 * (byte_size - 1)) - i * 7;
        uint64_t b = (reversed_buf[i] & SEVEN_BIT_MASK) << l_shift;
        _out += b;
    }

    *out = _out;

    return 0;
}

#endif