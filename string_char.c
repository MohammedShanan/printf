#include "main.h"

/**
 * ctostr - char to string
 * @ap: argument parameter
 * Return: char as string
 */
char *ctostr(va_list *ap)
{
char c = va_arg(*ap, int);
char *s = malloc(2);
if (s == NULL)
{
return (NULL);
}
s[0] = c;
s[1] = '\0';
return (s);
}
/**
 * tostr - string
 * @ap: argument parameter
 * Return: string
 */
char *tostr(va_list *ap)
{
return (_strdup1(va_arg(*ap, char *)));
}
