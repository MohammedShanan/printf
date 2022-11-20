#include "main.h"
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
        arr = BINARY;
    }
    else if (flag == 'o')
    {
        div = 8, len_tmp = 11;
        arr = OCTAL;
    }
    else if (flag == 'x')
    {
        arr = HEX_LOWER;
    }
    else
    {
        arr = HEX_UPPER;
    }
    tmp = malloc(len_tmp + 1);
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
    s = _strdup1(tmp + i + 1);
    free(tmp);
    return (s);
}
/**
 * num_to_str - convert a number to a string
 * @n: number to be converted
 * @negative: to specify if the number is negative or not
 * Return: number as a string
 */
char *num_to_str(unsigned int n)
{
    int digit, i = 0, len_n = 1;
    char *s;
    double tens = 1;
    while (tens * 10 <= n)
    {
        tens *= 10;
        len_n++;
    }
    s = malloc(len_n + 1);
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
 * _strdup1 - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */

char *_strdup1(char *str)
{
    char *new_str;
    int size;
    if (str == NULL)
    {
        return (NULL);
    }
    size = _strlen(str, 1) + 1;
    new_str = malloc(size);
    if (new_str == NULL)
    {
        return (NULL);
    }
    return (_strcpy(new_str, str));
}
/**
 * add_sign - add a sign to numbers
 * @sign: sign to add
 * @n: number
 * Return: number with sign in front
 */
char *add_sign(char sign, char *n)
{
    char *str = malloc(_strlen(n, 1) + 2);
    int i, j = 0;
    str[j++] = sign;
    for (i = 0; n[i]; i++)
    {
        str[j++] = n[i];
    }
    str[j] = '\0';
    free(n);
    return (str);
}