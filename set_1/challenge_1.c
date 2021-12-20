#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert hex to base64: https://cryptopals.com/sets/1/challenges/1
// The string: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
// Should produce: SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
const char *input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char *output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

// Global Bytes to Base64
char *byte_to_base64[65] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/"};

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
    size_t len = strlen(input) / 2;
    unsigned int *hex = str_to_hexbytes(input);
    unsigned int *base64 = hexbytes_to_base64bytes(hex, len);
    return base64_to_str(base64, len);
}

int main()
{

    char *result = hex_to_base64(input);
    printf("%s\n", result);

    return 0;
}