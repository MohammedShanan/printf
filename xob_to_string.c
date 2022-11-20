#include "main.h"
/**
 * _itox - convert unsigned int to hexadecimal in lower case
 * @ap: argument parameter
 * Return: an unsigned int as hexadecimal in lower case
 */
char *_itox(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'x'));
}

/**
 * _itoX - convert unsigned int to hexadecimal in upper case
 * @ap: argument parameter
 * Return: an unsigned int as hexadecimal in upper case
 */
char *_itoX(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'X'));
}
/**
 * ito_oc - convert unsigned int to octal
 * @ap: argument parameter
 * Return: an unsigned int as an octal
 */
char *ito_oc(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'o'));
}
/**
 * _itob - convert unsigned int to binary
 * @ap: argument parameter
 * Return: an unsigned int as binary
 */
char *_itob(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'b'));
}
