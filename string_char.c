#include "main.h"

/**
 * ctostr - char to string
 * @ap: argument parameter
 * @opt: options
 * Return: char as string
 */
char *ctostr(va_list *ap, op *opt UNUSED)
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
 * @opt: options
 * Return: string
 */
char *tostr(va_list *ap, op *opt)
{
char *s;
s = _strdup1(va_arg(*ap, char *));
if (opt->precision < _strlen(s, 1))
{
s[opt->precision] = '\0';
}
s = apply_filed_width(s, opt->filed_width, opt->minus_flag);
return (s);
}
/**
 * _itos - convert  int to string
 * @ap: argument parameter
 * @opt: options
 * Return: an int as string
 */

char *_itos(va_list *ap, op *opt)
{
int n = va_arg(*ap, int);
char *s;
if (n < 0)
{
n = n * -1;
s = add_sign("-", num_to_str(n));
}
else
{
s = num_to_str(n);
}
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'i', opt);
s = apply_zero(s, 'i', opt);
s = apply_filed_width(s, opt->filed_width, opt->minus_flag);
return (s);
}

/**
 * _uitos - convert unsigned int to string
 * @ap: argument parameter
 * @opt: options
 * Return: an unsigned int as string
 */
char *_uitos(va_list *ap, op *opt)
{
unsigned int n = va_arg(*ap, unsigned int);
char *s;
s = num_to_str(n);
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'u', opt);
s = apply_zero(s, 'u', opt);
s = apply_filed_width(s, opt->filed_width, opt->minus_flag);
return (s);
}
