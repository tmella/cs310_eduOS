
#ifndef CSWK_STDLIB_STRING_H
#define CSWK_STDLIB_STRING_H

char isspace(char ch);

int strlen(const char *str);

int strtrim(const char *str, char *trimmed);

int strcmp(const char *str1, const char *str2);

int next_word(const char *str1, char *str2);
char **strwordsplit(const char *str, char **tgt);

#endif //CSWK_STDLIB_STRING_H
