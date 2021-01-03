
//void *memset(void *str, int c, size_t n) copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.
void *memset(void *str, int c, int n);

void memory_copy(char* source, char* dest, int no_bytes);


/* decimal : base = 10
 * hex : base = 16
 * binary : base = 2
 * octal : base = 8
 */

char *itoa(int num, char *str, int base);
