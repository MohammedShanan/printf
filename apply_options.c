#include "main.h"
/**
 * apply_precision - apply precision option
 * @str: string to modify
 * @pre: precision to be applied
 * Return: string
 */
char *apply_precision(char *str, int pre)
{
char *s;
s = pad_zeros(pre, str);
return (s);
}
/**
 * apply_sign - apply + or space or # flage
 * @str: string to modify
 * @id: format specifier
 * @opt: struct op
 * Return: string
 */
char *apply_sign(char *str, char id, op *opt)
{
char *s = str;
if (id == 'x' && opt->hash_flag)
{
s = add_sign("0x", str);
}
else if (id == 'X' && opt->hash_flag)
{
s = add_sign("0X", str);
}
else if (id == 'o' && opt->hash_flag)
{
if (str[0] != '0')
{
s = add_sign("0", str);
}
}
else if (is_c_in_str(id, "diu"))
{
if (opt->plus_flag)
{
if (str[0] != '-')
{
s = add_sign("+", str);
}
}
else if (opt->space_flag)
{
if (str[0] != '-')
{
s = add_sign(" ", str);
}
}
}
return (s);
}
/**
 * apply_zero - apply flage
 * @str: string to modify
 * @id: format specifier
 * @opt: struct op
 * Return: string
 */
char *apply_zero(char *str, char id, op *opt)
{
char *s;
if (!opt->zero_flag || !opt->filed_width)
{
return (str);
}
if (str[0] == '-')
{
opt->filed_width = opt->filed_width - 1;
}
else if ((id == 'X' || id == 'x') && opt->hash_flag)
{
opt->filed_width = opt->filed_width - 2;
}
s = pad_zeros(opt->filed_width, str);
opt->filed_width = 0;
return (s);
}
/**
 * apply_filed_width - apply filed width
 * @str: string to modify
 * @width: width to be applied
 * @minus_flag: value of the "-" flage
 * Return: string
 */
char *apply_filed_width(char *str, int width, int minus_flag)
{
int i, len_str;
char *s, *spaces;
if (width == 0)
{
return (str);
}
len_str = _strlen(str, 1);
if (len_str >= width)
{
return (str);
}
spaces = malloc(width);
if (spaces == NULL)
{
free(str);
return (NULL);
}
for (i = 0; i < width - len_str; i++)
{
spaces[i] = ' ';
}
spaces[i] = '\0';
if (minus_flag)
{
s = add_sign(str, spaces);
free(str);
}
else
{
s = add_sign(spaces, str);
free(spaces);
}
return (s);
}
/**
 * apply_options - apply all the flags and options
 * @id: format specifier
 * @str: string
 * @options: a struct op
 * Return: string
 */
char *apply_options(char id, char *str, op *options)
{
char *s = str;
if (str == NULL)
{
return (NULL);
}
if (options->precision || options->minus_flag)
{
options->zero_flag = 0;
}
if (is_c_in_str(id, "iduxXo"))
{
s = apply_precision(str, options->precision);
s = apply_zero(s, id, options);
s = apply_sign(s, id, options);
}
s = apply_filed_width(s, options->filed_width, options->minus_flag);
return (s);
}
