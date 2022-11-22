#include "main.h"
/**
 * short_tos - convert short int to string
 * @ap: argument parameter
 * Return: an short int as string
 */
char *short_tos(va_list *ap)
{
short n = va_arg(*ap, int);
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
 * unsigned_short_tos - convert unsigned short int to string
 * @ap: argument parameter
 * Return: an unsigned short int as string
 */
char *unsigned_short_tos(va_list *ap)
{
unsigned short n = va_arg(*ap, int);
char *s;
s = num_to_str(n);
return (s);
}
/**
 * long_tos - convert long int to string
 * @ap: argument parameter
 * Return: an long int as string
 */
char *long_tos(va_list *ap)
{
long n = va_arg(*ap, long);
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
 * unsigned_long_tos - convert unsigned long int to string
 * @ap: argument parameter
 * Return: an unsigned long int as string
 */
char *unsigned_long_tos(va_list *ap)
{
unsigned long n = va_arg(*ap, unsigned long);
char *s;
s = num_to_str(n);
return (s);
}
/**
 * apply_len_modifier - apply len modifier option
 * @id: format specifier
 * @opt: struct op
 * @ap: argument parameter
 * Return: string
 */
char *apply_len_modifier(char id, op *opt, va_list *ap)
{
char *s;
int i;
char *(*f)(va_list *);
conv_function funcs[] = {
{'i', short_tos},
{'d', short_tos},
{'u', unsigned_short_tos},
{'I', long_tos},
{'D', long_tos},
{'U', unsigned_long_tos},
};
id = opt->h ? id : id - 32;
while (1)
{
if (funcs[i].id == id)
{
f = funcs[i].func;
break;
}
i++;
}
s = f(ap);
return (s);
}
