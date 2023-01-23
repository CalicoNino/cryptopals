#include <stdio.h>
#include <stdlib.h>
#include "../set_1.h"

// Detect single-character XOR
// One of the 60-character strings in this file (../txt/challenge_4.txt) has been encrypted by single-character XOR. Find it.

int main(void)
{
    FILE *fptr;
    char line[256];

    fptr = fopen("./txt/challenge_4.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while (fgets(line, sizeof(line), fptr))
    {
        printf("%s", line);
        const char *cipherhex = line;
        char *result = attack_single_byte_xor(cipherhex);
        if (result != NULL)
        {
            printf("%s", result);
        }
    }

    fclose(fptr);
    return 0;
}