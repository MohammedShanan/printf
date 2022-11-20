#ifndef MAIN_TEST_H
#define MAIN_TEST_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
/**
 * _strlen - returns the length of a string
 * @s: string
 * @non_prt: paramater to determine whether
 * to count non printable charters as part of the string or not
 * Return: length
 */

int _strlen(char *s, int non_prt)
{
    int len;
    len = 0;
    while (*s)
    {
        if (!non_prt && (*s < 32 || *s >= 127))
        {
            s++;
            continue;
        }
        len++;
        s++;
    }
    return (len);
}
/**
 * conv_to_xob - convert a number to binary or hex or octal
 * @n:number to convert
 * @flag: value to covert to hex or octal as a string,
 * by default it convert to hex uppercase (flag == NULL)
 */
char *conv_to_xob(unsigned int n, char flag)
{
    int i, rem, len_tmp, div;
    char *tmp, *s, *arr;
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
/**
 * num_to_str - convert a number to a string
 * @n: number to be converted
 * @negative: to specify if the number is negative or not
 * Return: number as a string
 */
char *num_to_str(unsigned int n, int negative)
{
    int digit, i = 0, len_n = 1;
    char *s;
    double tens = 1;
    if (negative)
    {
        s[i++] = '-';
    }
    while (tens * 10 <= n)
    {
        tens *= 10;
        len_n++;
    }
    s = (char *)malloc(len_n + 1);
    if (s == NULL)
    {
        return (NULL);
    }
    while (tens >= 1)
    {
        digit = n / tens;
        s[i] = digit + '0';
        n = (n - (tens * digit));
        tens /= 10;
        i++;
    }
    s[i] = '\0';
    return (s);
}

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of original source
 */

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
/**
 * rot13 - encode string using rot13
 * @ap: pointer to argument parameter
 * Return: encoded string
 */

char *rot13(va_list *ap)
{
    int i = 0, n;
    char *s = va_arg(*ap, char *);
    char *str = (char *)malloc(_strlen(s, 1) + 1);
    if (s == NULL || str == NULL)
    {
        return (NULL);
    }
    while (s[i])
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            n = s[i] % 'A';
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            n = s[i] % 'a';
        }
        else
        {
            str[i] = s[i];
            i++;
            continue;
        }
        n = n + 13;
        n = n % 26;
        str[i] = s[i] < 'a' ? 'A' + n : 'a' + n;
        i++;
    }
    str[i] = '\0';
    return (str);
}

/**
 * rev_string - reverse a string
 * @ap: pointer to argument parameter
 * Return: string in reverse
 */

char *rev(va_list *ap)
{
    int i = 0, j;
    char *s = va_arg(*ap, char *);
    char *rev = (char *)malloc(_strlen(s, 1) + 1);
    if (s == NULL || rev == NULL)
    {
        free(rev);
        return (NULL);
    }
    j = _strlen(s, 1) - 1;
    while (j >= 0)
    {
        rev[i] = s[j];
        i++;
        j--;
    }
    rev[i] = '\0';
    return (rev);
}
/**
 * custom_str - convert a string to a custom string
 * @ap: pointer to argument parameter
 * Return: a custom string with
 * none printable charater replaced by \x
 * followed by the ASCII code value in
 * hexadecimal (upper case - always 2 characters)
 */
char *custom_str(va_list *ap)
{
    char *s = va_arg(*ap, char *);
    char *hex, *cstm_s;
    int i, j = 0, len_s, len_nall, len_cstms;
    len_s = _strlen(s, 1);                      /*length s with none printable chars*/
    len_nall = _strlen(s, 0);                   /*length s without none printable chars*/
    len_cstms = (len_s - len_nall) * 3 + len_s; /*length custom string*/
    cstm_s = (char *)malloc(len_cstms + 1);
    if (cstm_s == NULL)
    {
        return (NULL);
    }
    for (i = 0; s[i]; i++)
    {
        if (s[i] < 32 || s[i] >= 127)
        {
            hex = conv_to_xob(s[i], 'X');
            cstm_s[j++] = '\\', cstm_s[j++] = 'x';
            cstm_s[j++] = hex[1] == '\0' ? '0' : hex[0];
            cstm_s[j++] = hex[1] == '\0' ? hex[0] : hex[1];
            free(hex);
        }
        else
        {
            cstm_s[j++] = s[i];
        }
    }
    cstm_s[j] = '\0';
    return (cstm_s);
}
#endif