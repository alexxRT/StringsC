#ifndef MY_STRINGS
#define MY_STRINGS

#include <stdio.h>


void  my_puts (char* str);

char* my_strchr (char* str, int code);

int   my_strlen (char* str);

char* my_strcpy (char* buf, char* str);

char* my_strncpy (char* buf, char* str, int num);

char* my_strcat (char* dest, char* str);

char* my_strncat (char* dest, char* str, int num);

char* my_fgets (char* buf, int num, FILE* file);

char* my_strdup (char* str);

char* my_getline(char* buf, FILE* file);


#endif