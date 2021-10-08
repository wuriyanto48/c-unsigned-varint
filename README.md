## C Unsigned Varint

Variable Integer (VarInt) Encoding implementation in `C`

Based on `Protocol Buffer Varint Encoding` implementation, but:
- Without `Signed Encoding`
- Limit only `9 bytes length`

### Header only
So just copy `cvarint.h` to your project, and you ready to go

### Usage

Encoding
```c
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
    printf("%d\n", out[i]); // 172, 2
```

Decoding

```c
Byte stream[2] = {172, 2};
uint64_t decoded_varint = 0;
int d = decode_varint(stream, &decoded_varint, byte_size);
if (d != 0)
{
    free(out);
    EXIT_ERR("error decode varint");
}

printf("decoded varint: %llu\n", decoded_varint); // 300
```

### Try run the implementation
```shell
$ make build
$ ./app
```