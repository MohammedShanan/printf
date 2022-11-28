#include "main.h"
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
/**
 * _itox - convert unsigned int to hexadecimal in lower case
 * @ap: argument parameter
 * @opt: options
 * Return: an unsigned int as hexadecimal in lower case
 */
char *_itox(va_list *ap, op *opt)
{
unsigned int n = va_arg(*ap, unsigned int);
char *s;
s = conv_to_xob(n, 'x');
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'x', opt);
s = apply_zero(s, 'x', opt);
return (s);
}

/**
 * _itoX - convert unsigned int to hexadecimal in upper case
 * @ap: argument parameter
 * @opt: options
 * Return: an unsigned int as hexadecimal in upper case
 */
char *_itoX(va_list *ap, op *opt)
{
unsigned int n = va_arg(*ap, unsigned int);
char *s;
s = conv_to_xob(n, 'X');
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'X', opt);
s = apply_zero(s, 'X', opt);
return (s);
}

/**
 * ito_oc - convert unsigned int to octal
 * @ap: argument parameter
 * @opt: options
 * Return: an unsigned int as an octal
 */
char *ito_oc(va_list *ap, op *opt)
{
unsigned int n = va_arg(*ap, unsigned int);
char *s;
s = conv_to_xob(n, 'o');
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'o', opt);
s = apply_zero(s, 'o', opt);
return (s);
}

/**
 * conv_to_xob - convert a number to binary or hex or octal
 * @n:number to convert
 * @flag: value to covert to hex or octal as a string,
 * by default it convert to hex uppercase (flag == NULL)
 * Return: a num as hex ,binary or  octal
 */
char *conv_to_xob(size_t n, char flag)
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
i = len_tmp - 1;
do
{
rem = n % div;
n = n / div;
tmp[i--] = arr[rem];
} while (n != 0);
tmp[len_tmp] = '\0';
s = _strdup1(tmp + i + 1);
free(tmp);
return (s);
}
/**
 * ptr_to_str - convert void pointer argument as hexadecimal
 * @ap: argument parameter
 * @opt: options
 * Return: void pointer argument as hexadecimal
 */
char *ptr_to_str(va_list *ap, op *opt UNUSED)
{
size_t n = va_arg(*ap, size_t);
char *s;
s = conv_to_xob(n, 'x');
s = add_sign("0x", s);
return (s);
}
