#ifndef XOB_H
#define XOB_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
int _strlen(char *s, int non_prt)
{
    int len;
    len = 0;
    while (*s)
    {
        len++;
        s++;
    }
    return (len);
}
char *_strcpy(char *dest, char *src)
{
    int i;

    for (i = 0; src[i]; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */

char *_strdup(char *str)
{
    char *new_str;
    int size;
    if (str == NULL)
    {
        return (NULL);
    }
    size = _strlen(str, 1) + 1;
    new_str = (char *)malloc(size);
    if (new_str == NULL)
    {
        return (NULL);
    }
    return (_strcpy(new_str, str));
}
char *conv_to_xob(unsigned int n, char flag)
{
    int i, rem, len_tmp, div;
    char *arr;
    char *tmp = "", *s;
    len_tmp = div = 16;
    if (flag == 'b')
    {
        div = 2, len_tmp = 32;
        arr = OCTAL;
    }
    else if (flag == 'o')
    {
        div = 8, len_tmp = 11;
        arr = BINARY;
    }
    else if (flag == 'x')
    {
        arr = HEX_LOWER;
    }
    else
    {
        arr = HEX_UPPER;
    }
    tmp = (char *)malloc(len_tmp + 1);
    if (tmp == NULL)
    {
        return (NULL);
    }
    for (i = len_tmp - 1; n != 0; i--)
    {
        rem = n % div;
        n = n / div;
        tmp[i] = arr[rem];
    }
    tmp[len_tmp] = '\0';
    s = _strdup(tmp + i + 1);
    free(tmp);
    return (s);
}
#endif