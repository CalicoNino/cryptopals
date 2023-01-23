#include <stdio.h>
#include "../set_1.h"
#include <stdlib.h>
#include <string.h>

#define ENOUGH 10000
#define MIN_KEYSIZE 2
#define MAX_KEYSIZE 36

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
//     4. The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
//     5. Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
//     6. Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
//     7. Solve each block as if it was single-character XOR. You already have code to do this.
//     8. For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.
// This code is going to turn out to be surprisingly useful later on. Breaking repeating-key XOR ("Vigenere") statistically is obviously an academic exercise, a "Crypto 101" thing. But more people "know how" to break it than can actually break it, and a similar technique breaks something much more important.
// No, that's not a mistake.
// We get more tech support questions for this challenge than any of the other ones. We promise, there aren't any blatant errors in this text. In particular: the "wokka wokka!!!" edit distance really is 37.

int main(void)
{
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
        char *decoded = base64_to_hex(line);
        strcat(buffer, decoded);
    }
    fclose(fptr);

    int probable = guess_keysize(buffer, MAX_KEYSIZE, MIN_KEYSIZE);
    printf("%d\n", probable);

    int cols = probable;
    int rows = strlen(buffer) / (probable * 2);
    unsigned int *matrix[rows];

    // int i = 0;
    // int t = 0;
    // char temp[probable * 2];
    // for (int j = 0; j < strlen(buffer); j++)
    // {
    //     temp[i] = buffer[j];
    //     i++;

    //     if (i == probable * 2)
    //     {
    //         matrix[i] = str_to_hexbytes(temp);
    //         i = 0;
    //         t++;
    //     }
    //     printf("%s\n", temp);
    // }

    // for (size_t i = 0; i < rows; i++)
    // {
    //     for (size_t k = 0; k < cols; k++)
    //     {
    //         printf("%ls", matrix[i]);
    //     }
    //     printf("\n");
    // }

    return 0;
}