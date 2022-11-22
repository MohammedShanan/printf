#include "main.h"
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
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
 * conv_to_xob - convert a number to binary or hex or octal
 * @n:number to convert
 * @flag: value to covert to hex or octal as a string,
 * by default it convert to hex uppercase (flag == NULL)
 * Return: a num as hex ,binary or  octal
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
i = len_tmp - 1;
do {
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
 * Return: void pointer argument as hexadecimal
 */
char *ptr_to_str(va_list *ap)
{
unsigned int n = va_arg(*ap, unsigned int);
char *tmp, *s, *arr;
int i, rem, len_tmp, div;
len_tmp = div = 16;
arr = HEX_LOWER;
tmp = malloc(len_tmp + 1);
if (tmp == NULL)
{
return (NULL);
}
i = len_tmp - 1;
do {
rem = n % div;
n = n / div;
tmp[i--] = arr[rem];
} while (n != 0);
tmp[len_tmp] = '\0';
s = _strdup1(tmp + i + 1);
free(tmp);
return (s);
}
