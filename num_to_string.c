#include "main.h"
/**
 * _itos - convert  int to string
 * @ap: argument parameter
 * Return: an int as string
 */

char *_itos(va_list *ap)
{
    int n = va_arg(*ap, int);
    char *s;
    if (n < 0)
    {
        n = n * -1;
        s = add_sign("-", num_to_str(n));
        return (s);
    }
    s = num_to_str(n);
    return (s);
}
/**
 * _uitos - convert unsigned int to string
 * @ap: argument parameter
 * Return: an unsigned int as string
 */
char *_uitos(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (num_to_str(n));
}
/**
 * add_sign - add a sign to numbers
 * @sign: sign to add
 * @n: number
 * Return: number with sign in front
 */
char *add_sign(char *sign, char *n)
{
    int i, j = 0, len_Str;
    char *str; 
    len_Str = _strlen(n, 1) + _strlen(sign, 1);
    str = malloc(len_Str + 1);
    for (i = 0; sign[i]; i++)
    {
        str[j++] = sign[i];
    }
    for (i = 0; n[i]; i++)
    {
        str[j++] = n[i];
    }
    str[j] = '\0';
    free(n);
    return (str);
}
/**
 * num_to_str - convert a number to a string
 * @n: number to be converted
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
