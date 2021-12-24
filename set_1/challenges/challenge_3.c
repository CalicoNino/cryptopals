#include <stdio.h>
#include "../set_1.h"

// Single-byte XOR cipher: https://cryptopals.com/sets/1/challenges/3
//  The hex encoded string:
// 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
// ... has been XOR'd against a single character. Find the key, decrypt the message.

int main(void)
{
    const char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char *result = attack_single_byte_xor(cipherhex);
    printf("%s\n", result);
    return 0;
}