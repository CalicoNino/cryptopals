#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
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
        size_t len = strlen(line);
        unsigned int *hexbytes = str_to_hexbytes(line);
        unsigned int tmp = get_most_frequent_byte(hexbytes, len / 2);
        printf("\nMost Frequent Letter: %c\n", tmp);
        printf("Decrypted Key: %c\n", tmp ^ ' ');
        for (int i = 0; i < len / 2; i++)
        {
            printf("%c", (tmp ^ ' ') ^ hexbytes[i]);
        }
    }

    fclose(fptr);
    return 0;
}