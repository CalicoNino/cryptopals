#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../set_1.h"

// Single-byte XOR cipher: https://cryptopals.com/sets/1/challenges/3
//  The hex encoded string:
// 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
// ... has been XOR'd against a single character. Find the key, decrypt the message.

char letter_frequencies[58] = {'E', 'e', 'T', 't', 'A', 'a', 'O', 'o', 'I', 'i', 'N', 'n', ' ', 'S',
                               's', 'R', 'r', 'H', 'h', 'D', 'd', 'L', 'l', 'U', 'u', 'C', 'c', 'M',
                               'm', 'F', 'f', 'Y', 'y', 'W', 'w', 'G', 'g', 'P', 'p', 'B', 'b', 'V',
                               'v', 'K', 'k', 'X', 'x', 'Q', 'q', 'J', 'j', 'Z', 'z',
                               '\'', '\"', '\n', '?', '!'};

int main(void)
{
    const char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    size_t len = strlen(cipherhex);
    unsigned int *hexbytes = str_to_hexbytes(cipherhex);
    unsigned int tmp = get_most_frequent_byte(hexbytes, len / 2);
    printf("Most Frequent Letter: %c\n", tmp);
    printf("Decrypted Key: %c\n", 0x78 ^ letter_frequencies[12]);
    for (int j = 0; j < 58; j++)
    {
        for (int i = 0; i < len / 2; i++)
        {
            unsigned int c = (tmp ^ letter_frequencies[j]) ^ hexbytes[i];
            if (!is_english_symbol(c))
            {
                break;
            }
            printf("%c", c);
        }
        printf("\n");
    }
    return 0;
}