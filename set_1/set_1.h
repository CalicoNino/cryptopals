#ifndef SET_1_ /* Include guard */
#define SET_1_

unsigned int *str_to_hexbytes(const char *hex_str);

unsigned int *str_to_base64bytes(const char *base64_str);

unsigned int *base64bytes_to_hexbytes(unsigned int *base64bytes, size_t len);

char *base64_to_hex(const char *input);

unsigned int *hexbytes_to_base64bytes(unsigned int *hexbytes, size_t len);

char *base64_to_str(unsigned int *base64bytes, size_t len);

char *hex_to_base64(const char *input);

char *bytes_to_str(unsigned int *bytes, size_t len);

unsigned int *xor_hexbytes(unsigned int *hexbytes_1, unsigned int *hexbytes_2, size_t len);

char *xor_hex(const char *input_1, const char *input_2);

unsigned int get_most_frequent_byte(unsigned int *bytes, size_t len);

int is_english_symbol(unsigned int c);

char *attack_single_byte_xor(const char *input);

char *xor_text(const char *plaintext, const char *key);

unsigned int *text_to_bytes(const char *text);

int hamming_distance(unsigned int *input_1, unsigned int *input_2, size_t len);

int guess_keysize(char *buffer, int max_keysize, int min_keysize);

#endif // SET_1_
