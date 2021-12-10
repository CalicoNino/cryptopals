#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert hex to base64: https://cryptopals.com/sets/1/challenges/1
// The string: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
// Should produce: SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
const char *input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const char *output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

u_int8_t *str_to_hexbytes(const char *hex_str) {
    size_t len = strlen(hex_str);
    u_int8_t *hex = malloc(sizeof(u_int8_t)* len/2);
    for(int i, j = 0; i < len; i += 2, j++) {
        char tmp[2];
        strncpy(tmp, hex_str+i, 2);
        hex[j] = strtol(tmp, NULL, 16);
    }
    return hex;
}

u_int8_t *hexbytes_to_base64bytes(u_int8_t *hexbytes) {
    size_t len = strlen(hexbytes);
    u_int8_t *base64bytes = malloc(sizeof(u_int8_t) * len);
    for(int i = 0; i < len; i += 3) {
        base64bytes[i] = (hexbytes[i] >> 2) & 0x3f;
        base64bytes[i+1] = ((hexbytes[i] & 0x3) << 4) | ((hexbytes[i+1] & 0xF0) >> 4);
        base64bytes[i+2] = ((hexbytes[i+1] & 0xf) << 2) | ((hexbytes[i+2] & 0xC0) >> 6);
        base64bytes[i+3] = hexbytes[i+2] & 0x3f;
    }
    return base64bytes;
}

char *byte_to_base64[65] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/"};

char *base64_2_str(u_int8_t *base64bytes) {
    size_t len = strlen(base64bytes);
    char *str = "\0";
    str = malloc(sizeof(len));
    for(int i = 0; i < len; i++) {
        strcat(str, byte_to_base64[(int)base64bytes[i]]);
    }
    return str;
}

int main() {
    u_int8_t *hex = str_to_hexbytes(input);
    u_int8_t *base64 = hexbytes_to_base64bytes(hex);

    // for(int i = 0; i < strlen(base64); i++) {
    //     printf("%d ", (int)base64[i]);
    // }

    char *result = base64_2_str(base64);
    printf("\n%s\n", result);
    
    return 0;
}