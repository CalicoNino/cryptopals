#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../set_1.h"

// Fixed XOR: https://cryptopals.com/sets/1/challenges/2
// Write a function that takes two equal-length buffers and produces their XOR combination.

int main(void)
{
    const char *input_1 = "1c0111001f010100061a024b53535009181c";
    const char *input_2 = "686974207468652062756c6c277320657965";
    const char *output = "746865206b696420646f6e277420706c6179";

    char *result = xor_hex(input_1, input_2);
    printf("Output: %s\n", result);
    return 0;
}