#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../set_1.h"

// Single-byte XOR cipher: https://cryptopals.com/sets/1/challenges/3
//  The hex encoded string:
// 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
// ... has been XOR'd against a single character. Find the key, decrypt the message.

int main(void)
{
    const char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    const char *funhex = "ETAOIN SHRDLU";
    size_t len = strlen(cipherhex);
    unsigned int *hexbytes = str_to_hexbytes(cipherhex);
    unsigned int tmp = get_most_frequent_byte(hexbytes, len / 2);
    printf("Decrypted: %x\n", 0x78 ^ 'x');
    printf("Most Frequent Letter: %x\n", tmp);
    for (int i = 0; i < len / 2; i++)
    {
        printf("%c", (0x78 ^ 'T') ^ hexbytes[i]);
    }
    return 0;
}