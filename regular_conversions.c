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
s = add_sign('-', num_to_str(n));
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
/**
 * t_itox - convert unsigned int to hexadecimal in lower case
 * @ap: argument parameter
 * Return: an unsigned int as hexadecimal in lower case
 */
char *_itox(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'x'));
}

/**
 * t_itoX - convert unsigned int to hexadecimal in upper case
 * @ap: argument parameter
 * Return: an unsigned int as hexadecimal in upper case
 */
char *_itoX(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'X'));
}
/**
 * t_ito_oc - convert unsigned int to octal
 * @ap: argument parameter
 * Return: an unsigned int as an octal
 */
char *ito_oc(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'o'));
}
/**
 * t_itob - convert unsigned int to binary
 * @ap: argument parameter
 * Return: an unsigned int as binary
 */
char *_itob(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'b'));
}
