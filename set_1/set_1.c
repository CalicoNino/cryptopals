#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_1.h"

char *byte_to_base64[65] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/"};

unsigned int *str_to_hexbytes(const char *hex_str)
{
    int len = strlen(hex_str);
    unsigned int *hex = malloc(sizeof(unsigned int) * len / 2);
    for (int i = 0, j = 0; i < len; i += 2, j++)
    {
        char tmp[3];
        strncpy(tmp, hex_str + i, 2);
        tmp[2] = 0;
        hex[j] = strtol(tmp, NULL, 16);
    }
    return hex;
}

unsigned int *hexbytes_to_base64bytes(unsigned int *hexbytes, size_t len)
{
    unsigned int *base64bytes = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i += 3)
    {
        base64bytes[i] = (hexbytes[i] >> 2) & 0x3f;
        base64bytes[i + 1] = ((hexbytes[i] & 0x3) << 4) | ((hexbytes[i + 1] & 0xF0) >> 4);
        base64bytes[i + 2] = ((hexbytes[i + 1] & 0xf) << 2) | ((hexbytes[i + 2] & 0xC0) >> 6);
        base64bytes[i + 3] = hexbytes[i + 2] & 0x3f;
    }
    free(hexbytes);
    return base64bytes;
}

char *base64_to_str(unsigned int *base64bytes, size_t len)
{
    char *str = malloc(sizeof(char) * len);
    for (int i = 0; i <= len; i++)
    {
        strcat(str, byte_to_base64[(int)base64bytes[i]]);
    }
    free(base64bytes);
    return str;
}

char *hex_to_base64(const char *input)
{
    int len = strlen(input) / 2;
    unsigned int *hex = str_to_hexbytes(input);
    unsigned int *base64 = hexbytes_to_base64bytes(hex, len);
    return base64_to_str(base64, len);
}

char *bytes_to_str(unsigned int *bytes, size_t len)
{
    char *str = malloc(sizeof(char) * len);
    for (int i = 0; i < len / 2; i++)
    {
        char tmp[3];
        sprintf(tmp, "%x", bytes[i]);
        tmp[2] = 0;
        strcat(str, tmp);
    }
    free(bytes);
    return str;
}

unsigned int *xor_hexbytes(unsigned int *hexbytes_1, unsigned int *hexbytes_2, size_t len)
{
    unsigned int *hex = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i++)
    {
        hex[i] = hexbytes_1[i] ^ hexbytes_2[i];
    }
    free(hexbytes_1);
    free(hexbytes_2);
    return hex;
}

char *xor_hex(const char *input_1, const char *input_2)
{
    size_t len = strlen(input_1);
    if (len == strlen(input_2))
    {
        unsigned int *hexbytes_1 = str_to_hexbytes(input_1);
        unsigned int *hexbytes_2 = str_to_hexbytes(input_2);
        unsigned int *hexbytes = xor_hexbytes(hexbytes_1, hexbytes_2, len / 2);
        return bytes_to_str(hexbytes, len);
    }
    return 0;
}

unsigned int get_most_frequent_byte(unsigned int *bytes, size_t len)
{
    size_t i, j, count;
    size_t most = 0;
    unsigned int tmp, elem;

    for (i = 0; i < len; i++)
    {
        tmp = bytes[i];
        count = 1;
        for (j = i + 1; j < len; j++)
        {
            if (bytes[j] == tmp)
            {
                count++;
            }
        }
        if (most < count)
        {
            most = count;
            elem = bytes[i];
        }
    }
    return elem;
}
