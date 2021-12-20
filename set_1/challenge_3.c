#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Single-byte XOR cipher: https://cryptopals.com/sets/1/challenges/3
//  The hex encoded string:
// 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
// ... has been XOR'd against a single character. Find the key, decrypt the message.
const char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
const char *funhex = "ETAOIN SHRDLU";

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

// char *hex_to_ascii(unsigned int *hexbytes, size_t len) {
//     char *str = malloc(sizeof(char)*len);
//     for(int i = 0; i < len/2; i++) {
//         char tmp[3];
//         sprintf(tmp, "%x", bytes[i]);
//         tmp[2] = 0;
//         strcat(str, tmp);
//     }
//     free(bytes);
//     return str;
// }

int main(void)
{
    size_t len = strlen(funhex);
    unsigned int *hexbytes = str_to_hexbytes(funhex);
    for (int i = 0; i < len / 2; i++)
    {
        printf("Decrypted: %c\n", 0x78 ^ hexbytes[i]);
    }
    return 0;
}