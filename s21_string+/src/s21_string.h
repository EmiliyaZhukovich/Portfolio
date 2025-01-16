#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#define S21_NULL (void *)0
typedef long unsigned s21_size_t;

// 1. Searches for the first occurrence of the character c (an unsigned char)
// in the first n bytes of the string pointed to, by the argument str.
void *s21_memchr(const void *str, int c, s21_size_t n);

// 2. Compares the first n bytes of str1 and str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// 3. Copies n characters from src to dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

// 4. Another function to copy n characters from str2 to str1.
void *s21_memmove(void *dest, const void *src, s21_size_t n);

// 5. Copies the character c (an unsigned char) to the first n
// characters of the string pointed to, by the argument str.
void *s21_memset(void *str, int c, s21_size_t n);

// 6. Appends the string pointed to, by src to the end
// of the string pointed to by dest.
char *s21_strcat(char *dest, const char *src);

// 7. Appends the string pointed to, by src to the end of
// the string pointed to, by dest up to n characters long.
char *s21_strncat(char *dest, const char *src, s21_size_t n);

// 8. Searches for the first occurrence of the character c
// (an unsigned char) in the string pointed to, by the argument str.
char *s21_strchr(const char *str, int c);

// 9. Compares the string pointed to, by str1 to the
// string pointed to by str2.
int s21_strcmp(const char *str1, const char *str2);

// 10. Compares at most the first n bytes of str1 and str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// 11. Copies the string pointed to, by src to dest.
char *s21_strcpy(char *dest, const char *src);

// 12. Copies up to n characters from the string pointed to, by src to dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

// 13. Calculates the length of the initial segment of str1
// which consists entirely of characters not in str2.
s21_size_t s21_strcspn(const char *str1, const char *str2);

// 14. Searches an internal array for the error number errnum and returns
// a pointer to an error message string. You need to declare macros containing
// arrays of error messages for mac and linux operating systems.
// Error descriptions are available in the original library.
// Checking the current OS is carried out using directives.
char *s21_strerror(int errnum);

// 15. Computes the length of the string str up to but
// not including the terminating null character.
s21_size_t s21_strlen(const char *str);

// 16. Finds the first character in the string str1 that
// matches any character specified in str2.
char *s21_strpbrk(const char *str1, const char *str2);

// 17. Searches for the last occurrence of the character c
// (an unsigned char) in the string pointed to by the argument str.
char *s21_strrchr(const char *str, int c);

// 18. Calculates the length of the initial segment of
// str1 which consists entirely of characters in str2.
s21_size_t s21_strspn(const char *str1, const char *str2);

// 19. Finds the first occurrence of the entire string needle
// (not including the terminating null character) which appears
// in the string haystack.
char *s21_strstr(const char *haystack, const char *needle);

// 20. Breaks string str into a series of tokens separated by delim.
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);

#ifdef __APPLE__
extern char *_errors[107];
#define MAX_ERROR 107
#endif  // __APPLE__

#ifdef __unix__
extern char *_errors[134];
#define MAX_ERROR 133
#endif  // unix
extern char unknown_error[150];
#endif  // SRC_S21_STRING_H_
