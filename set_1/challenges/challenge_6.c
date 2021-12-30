#include <stdio.h>
#include "../set_1.h"
#include <stdlib.h>
#include <string.h>

#define ENOUGH 10000

// Break repeating-key XOR
// It is officially on, now.
// This challenge isn't conceptually hard, but it involves actual error-prone coding. The other challenges in this set are there to bring you up to speed. This one is there to qualify you. If you can do this one, you're probably just fine up to Set 6.
// There's a file here (txt/challenge_6). It's been base64'd after being encrypted with repeating-key XOR.
// Decrypt it.
// Here's how:
//     1. Let KEYSIZE be the guessed length of the key; try values from 2 to (say) 40.
//     2. Write a function to compute the edit distance/Hamming distance between two strings. The Hamming distance is just the number of differing bits. The distance between:
//     this is a test
//     and
//     wokka wokka!!!
//     is 37. Make sure your code agrees before you proceed.
//     3. For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, and find the edit distance between them. Normalize this result by dividing by KEYSIZE.
//     The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
//     Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
//     Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
//     Solve each block as if it was single-character XOR. You already have code to do this.
//     For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.
// This code is going to turn out to be surprisingly useful later on. Breaking repeating-key XOR ("Vigenere") statistically is obviously an academic exercise, a "Crypto 101" thing. But more people "know how" to break it than can actually break it, and a similar technique breaks something much more important.
// No, that's not a mistake.
// We get more tech support questions for this challenge than any of the other ones. We promise, there aren't any blatant errors in this text. In particular: the "wokka wokka!!!" edit distance really is 37.

int main(void)
{

    int hamming[] = {};

    FILE *fptr;
    char buffer[ENOUGH];
    long length;
    char line[256];

    fptr = fopen("./txt/challenge_6.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while (fgets(line, sizeof(line), fptr))
    {
        size_t len = strlen(line);
        char *decoded = base64_to_hex(line);
        strcat(buffer, decoded);
    }

    float lowest_score = 10;
    int lowest_keysize = 0;
    for (int i = 2; i <= 40; i++)
    {
        float average = 0;
        int buffer_len = strlen(buffer) / i;
        for (int j = 0; j < 20; j += i)
        {
            char test_1[i + 1];
            char test_2[i + 1];
            strncpy(test_1, buffer + j * i, i);
            strncpy(test_2, (buffer + i) + (j * i), i);
            test_1[i] = '\0';
            test_2[i] = '\0';

            // printf("For %s and %s. \n", test_1, test_2);
            unsigned int *bytes_1 = text_to_bytes(test_1);
            unsigned int *bytes_2 = text_to_bytes(test_2);

            float test = hamming_distance(bytes_1, bytes_2, i + 1) / (i + 1.0);
            average += test;
        }
        if (average / (buffer_len / i) <= lowest_score)
        {
            lowest_score = average / (buffer_len / i);
            lowest_keysize = i;
        }
        printf("For Keysize: %d, the hamming average is %f. \n", i, average / (buffer_len / i));
        // break;
    }

    printf("\n\nSmallest score is Keysize: %d, the hamming average is %f. \n", lowest_keysize, lowest_score);
    fclose(fptr);
    return 0;
}