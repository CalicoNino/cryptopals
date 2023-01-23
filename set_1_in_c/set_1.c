#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_1.h"

#define ENOUGH 10000

const char *index_to_base64[65] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                                   "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                                   "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d",
                                   "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
                                   "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
                                   "y", "z", "0", "1", "2", "3", "4", "5", "6", "7",
                                   "8", "9", "+", "/"};

const int B64index[256] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
                           56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6,
                           7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,
                           0, 0, 0, 63, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                           41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

char letter_frequencies[58] = {'E', 'e', 'T', 't', 'A', 'a', 'O', 'o', 'I', 'i', 'N', 'n', ' ', 'S',
                               's', 'R', 'r', 'H', 'h', 'D', 'd', 'L', 'l', 'U', 'u', 'C', 'c', 'M',
                               'm', 'F', 'f', 'Y', 'y', 'W', 'w', 'G', 'g', 'P', 'p', 'B', 'b', 'V',
                               'v', 'K', 'k', 'X', 'x', 'Q', 'q', 'J', 'j', 'Z', 'z',
                               '\'', '\"', '\n', '?', '!'};

unsigned int *str_to_hexbytes(const char *hex_str)
{
    size_t len = strlen(hex_str);
    unsigned int *hex = malloc(sizeof(unsigned int) * len / 2);
    for (int i = 0, j = 0; i < len; i += 2, j++)
    {
        char tmp[3];
        strncpy(tmp, hex_str + i, 2);
        tmp[2] = 0;
        hex[j] = strtol(tmp, NULL, 16);
    }
    return hex;
}

unsigned int *str_to_base64bytes(const char *base64_str)
{
    size_t len = strlen(base64_str);
    unsigned int *base64 = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i++)
    {
        if (base64_str[i] != '\n')
        {
            base64[i] = B64index[(int)base64_str[i]];
        }
    }
    return base64;
}

unsigned int *base64bytes_to_hexbytes(unsigned int *base64bytes, size_t len)
{
    int pad = len > 0 && (len % 4 || base64bytes[len - 1] == 0);
    const size_t new_len = ((len + 3) / 4 - pad) * 4;
    unsigned int *hexbytes = malloc(sizeof(unsigned int) * new_len / 4 * 3 + pad);
    for (int i = 0, j = 0; i < new_len; i += 4)
    {
        int n = base64bytes[i] << 18 | base64bytes[i + 1] << 12 | base64bytes[i + 2] << 6 | base64bytes[i + 3];
        hexbytes[j++] = n >> 16;
        hexbytes[j++] = n >> 8 & 0xFF;
        hexbytes[j++] = n & 0xFF;
    }

    if (pad)
    {
        int n = base64bytes[new_len] << 18 | base64bytes[new_len + 1] << 12;
        hexbytes[new_len - 1] = n >> 16;
    }

    return hexbytes;
}

unsigned int *hexbytes_to_base64bytes(unsigned int *hexbytes, size_t len)
{
    unsigned int *base64bytes = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i += 3)
    {
        base64bytes[i] = (hexbytes[i] >> 2) & 0x3f;
        base64bytes[i + 1] = ((hexbytes[i] & 0x3) << 4) | ((hexbytes[i + 1] & 0xF0) >> 4);
        base64bytes[i + 2] = ((hexbytes[i + 1] & 0xf) << 2) | ((hexbytes[i + 2] & 0xC0) >> 6);
        base64bytes[i + 3] = hexbytes[i + 2] & 0x3f;
        printf("%d-%d-%d-%d\n", base64bytes[i], base64bytes[i + 1], base64bytes[i + 2], base64bytes[i + 3]);
    }
    free(hexbytes);
    return base64bytes;
}

char *base64_to_str(unsigned int *base64bytes, size_t len)
{
    char *str = malloc(sizeof(char) * len);
    for (int i = 0; i <= len; i++)
    {
        strcat(str, index_to_base64[(int)base64bytes[i]]);
    }
    free(base64bytes);
    return str;
}

char *hex_to_base64(const char *input)
{
    size_t len = strlen(input) / 2;
    unsigned int *hex = str_to_hexbytes(input);
    unsigned int *base64 = hexbytes_to_base64bytes(hex, len);
    return base64_to_str(base64, len);
}

char *base64_to_hex(const char *input)
{
    size_t len = strlen(input);
    unsigned int *one = str_to_base64bytes(input);
    unsigned int *two = base64bytes_to_hexbytes(one, len);

    return bytes_to_str(two, len * 3 / 2);
}

char *bytes_to_str(unsigned int *bytes, size_t len)
{
    char *str = malloc(sizeof(char) * len);
    for (int i = 0; i < len / 2; i++)
    {
        char tmp[3];
        sprintf(tmp, "%x", bytes[i]);
        if (strlen(tmp) == 1)
        {
            tmp[1] = tmp[0];
            tmp[0] = '0';
        }
        tmp[2] = 0;
        strcat(str, tmp);
    }
    free(bytes);
    return str;
}

unsigned int *xor_hexbytes(unsigned int *hexbytes_1, unsigned int *hexbytes_2, size_t len)
{
    unsigned int *hex = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i++)
    {
        hex[i] = hexbytes_1[i] ^ hexbytes_2[i];
    }
    free(hexbytes_1);
    free(hexbytes_2);
    return hex;
}

char *xor_hex(const char *input_1, const char *input_2)
{
    size_t len = strlen(input_1);
    if (len == strlen(input_2))
    {
        unsigned int *hexbytes_1 = str_to_hexbytes(input_1);
        unsigned int *hexbytes_2 = str_to_hexbytes(input_2);
        unsigned int *hexbytes = xor_hexbytes(hexbytes_1, hexbytes_2, len / 2);
        return bytes_to_str(hexbytes, len);
    }
    return 0;
}

unsigned int get_most_frequent_byte(unsigned int *bytes, size_t len)
{
    size_t i, j, count;
    size_t most = 0;
    unsigned int tmp, elem;

    for (i = 0; i < len; i++)
    {
        tmp = bytes[i];
        count = 1;
        for (j = i + 1; j < len; j++)
        {
            if (bytes[j] == tmp)
            {
                count++;
            }
        }
        if (most < count)
        {
            most = count;
            elem = bytes[i];
        }
    }
    return elem;
}

int is_english_symbol(unsigned int c)
{
    if ((0x61 <= c && c <= 0x79)    // a -> y
        || (0x41 <= c && c <= 0x59) // A -> Y
        || (0x30 <= c && c <= 0x39) // 0 -> 9
        || (0x20 <= c && c <= 0x22) // space ! "
        || c == 0x27                // '
        || c == 0x0A                // \n
        || c == 0x2C                // ,
        || c == 0x2E                // .
        || c == 0x3F                // ?
        || c == 0x5A                // Z
        || c == 0x7A                // z

    )
    {
        return 1;
    }
    return 0;
}

char *attack_single_byte_xor(const char *input)
{
    size_t len = strlen(input);
    unsigned int *hexbytes = str_to_hexbytes(input);
    unsigned int most_frequent_letter = get_most_frequent_byte(hexbytes, len / 2);
    for (int j = 0; j < 58; j++)
    {
        char *str = malloc(sizeof(char) * len);
        for (int i = 0; i < len / 2; i++)
        {
            unsigned int c = (most_frequent_letter ^ letter_frequencies[j]) ^ hexbytes[i];
            if (!is_english_symbol(c))
            {
                break;
            }
            char tmp[3];
            sprintf(tmp, "%c", c);
            tmp[2] = 0;
            strcat(str, tmp);
        }
        if (strlen(str) == len / 2)
        {
            free(hexbytes);
            return str;
        }
    }
    return 0;
}

char *xor_text(const char *plaintext, const char *key)
{
    size_t len = strlen(plaintext);
    unsigned int *bytes = malloc(sizeof(unsigned int) * len);
    for (int i = 0, j = 0; i < len; i++, j++)
    {
        if (j == strlen(key))
        {
            j = 0;
        }
        bytes[i] = plaintext[i] ^ key[j];
    }
    return bytes_to_str(bytes, len * 2);
}

unsigned int *text_to_bytes(const char *text)
{
    size_t len = strlen(text);
    unsigned int *bytes = malloc(sizeof(unsigned int) * len);
    for (int i = 0; i < len; i++)
    {
        bytes[i] = text[i];
    }
    return bytes;
}

int hamming_distance(unsigned int *input_1, unsigned int *input_2, size_t len)
{
    int distance = 0;
    for (int i = 0; i < len; i++)
    {
        for (int tmp = input_1[i] ^ input_2[i]; tmp > 0; distance++, tmp &= (tmp - 1))
            ;
    }

    return distance;
}

int guess_keysize(char *buffer, int max_keysize, int min_keysize)
{
    double score_averages[40]; // index 0 -> MIN_KEYSIZE && index 39 -> MAX_KEYSIZE
    double lowest_score = ENOUGH;
    int index_lowest_score;

    for (int i = min_keysize; i <= max_keysize; i++)
    {
        double score = 0;
        int slice_size = i * 2;
        for (int j = 0; j < strlen(buffer) / slice_size; j += slice_size)
        {
            char test_1[slice_size + 1];
            char test_2[slice_size + 1];
            strncpy(test_1, buffer + j, slice_size);
            strncpy(test_2, buffer + slice_size + j, slice_size);
            test_1[slice_size] = '\0';
            test_2[slice_size] = '\0';

            unsigned int *bytes_1 = text_to_bytes(test_1);
            unsigned int *bytes_2 = text_to_bytes(test_2);

            score += hamming_distance(bytes_1, bytes_2, i + 1);
        }
        score = score / (i + 0.0);
        score = score / (slice_size + 0.0);
        score_averages[i - 2] = score;
        if (lowest_score > score)
        {
            lowest_score = score;
            index_lowest_score = i;
        }
    }
    return index_lowest_score;
}