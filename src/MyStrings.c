#include <assert.h>
#include <stdio.h>
#include "../lib/MyStrings.h"
#include "../lib/Memory.h"


char* my_getline(char* buf, FILE* file){
    assert (file != NULL);
    assert (buf != NULL);
    assert (file != NULL);
    char ch;
    int i = 0;

    while ((ch = fgetc(file)) != '\n' && ch != EOF)
    {
        buf[i] = ch;
        i++;
    }

    if (ch == '\n')
        buf[i] = '\n';
        buf[i+1] = '\0';
    if (ch == EOF)
        buf[i] = '\0';

    return buf;
}

char* my_strdup (char* str) 
{
    assert (str != NULL);

    int len = my_strlen(str);
    char* new_str = CALLOC (len + 1, char);

    assert (new_str != NULL);

    my_strcat (new_str, str);

    return new_str;
}

char* my_fgets (char* buf, int num, FILE* file)
{
    assert (num >= 0);
    assert (file != NULL);
    assert (buf != NULL);
    char ch;
    int i = 0;

    while (i < num) 
    {
        ch = fgetc (file);
        if (ch != EOF && ch != '\n')
            buf [i] = ch;
        i++; 
    }

    buf [i] = '\0';

    return buf;
}

char* my_strncat (char* dest, char* str, int num) 
{
    assert (dest != NULL);
    assert (str != NULL);
    assert (num >= 0);

    int i = 0;
    int len = my_strlen (dest);

    while (i < num)
    {
        if (str[i] != '\0') 
            dest [len + i] = str [i];
        
        else 
            dest [len + i] = '\0';
        i++;
    } 
    return dest;
}

char* my_strcat (char* dest, char* str)
{
    assert (dest != NULL);
    assert (str != NULL);

    int len = my_strlen (dest);
    int i = 0;

    while (str [i] != '\0') 
    {
        dest [len + i] = str [i];
        i++;
    }
    dest[i + len] = '\0';
    return dest;
}

char* my_strncpy (char* buf, char* str, int num)
{
    assert (str != NULL);
    assert (num >= 0);

    int i = 0;
    while (i < num) 
    {
        if (str[i] != '\0') 
            buf[i] = str[i];
        else 
            buf[i] = '\0';
        i++;
    }

    return buf;
}
char* my_strcpy (char* buf, char* str) 
{
    assert (str != NULL);
    int i = 0;

    while (str[i] != '\0') {
        buf[i] = str[i];
        i ++;    
    } 
    buf[i] = '\0';

    return buf;
}

int my_strlen (char* str) 
{
    assert (str != NULL);
    int i = 0;

    while (str[i] != '\0') {
         i++;
    }
    return i;
} 

char* my_strchr (char* str, int code)
{
    assert (str != NULL);

    int i = 0;
    while (str[i] != '\0') 
    {
        int symb = str[i];

        if (symb == code) {
            assert (*(str + i) == code);
            return str + i;
        }  
        i++;
    }

    return NULL;
}

void my_puts (char* str) 
{
    assert (str != NULL);
    int i = 0;

    while (str[i] != '\0') {
        putchar (str[i]);
        i++; 
    }
    printf ("\n");
}