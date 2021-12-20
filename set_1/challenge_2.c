#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fixed XOR: https://cryptopals.com/sets/1/challenges/2
// Write a function that takes two equal-length buffers and produces their XOR combination.
const char *input_1 = "1c0111001f010100061a024b53535009181c";
const char *input_2 = "686974207468652062756c6c277320657965";
const char *output = "746865206b696420646f6e277420706c6179";

unsigned int *str_to_hexbytes(const char *hex_str)
{
    size_t len = strlen(hex_str);
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

int main(void)
{

    char *result = xor_hex(input_1, input_2);
    printf("Output: %s\n", result);
    return 0;
}