#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fixed XOR: https://cryptopals.com/sets/1/challenges/2
// Write a function that takes two equal-length buffers and produces their XOR combination. 
long int input_1 = 0x1c0111001f010100061a024b53535009181c;
const char *input_2 = "686974207468652062756c6c277320657965";
const char *output = "746865206b696420646f6e277420706c6179";

// u_int8_t *str_to_hex(const char *hex_str) {
//     size_t len = strlen(hex_str);
//     u_int8_t *hex = malloc(sizeof(u_int8_t)* len);
//     for(int i = 0; i < len; i++) {
//         char tmp[1];
//         strncpy(tmp, hex_str+i, 1);
//         hex[j] = strtol(tmp, NULL, 16);
//     }
//     return hex;
// }

int main() {
    // char num = 0x12^0x25;
    printf("%x\n", input_1);
    return 0;
}