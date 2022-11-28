#include "main.h"
/**
 * update_options - update flags options
 * @s: formatted string
 * @indx: pointer to the indx of the options
 * @opt: options
 * Return: 1 if any option or flag is updated 0 if not
 */
int update_options(const char *s, int *indx, op *opt)
{
int (*fun)(const char *, int *, op *);
if ((s[*indx] >= '1' && s[*indx] <= '9'))
{
fun = update_field_width;
}
else
{
fun = get_op_fuction(s[*indx]);
}
if (fun == NULL)
{
return (0);
}
return (fun(s, indx, opt));
}
/**
 * update_len_modifier - update length modifier options
 * @s: formatted string
 * @indx: pointer to the indx of the options
 * @opt: options
 * Return: 1 if any option or flag is updated 0 if not
 */
int update_len_modifier(const char *s, int *indx, op *opt)
{
if (s[*indx] == 'h')
{
opt->h = 1;
}
else
{
opt->l = 1;
}
*indx = *indx + 1;
return (1);
}

/**
 * update_flag - update "0", " ", "+", "-", "#"
 * @s: formatted string
 * @indx: pointer to the indx of the options
 * @opt: options
 * Return: 1 if any option or flag is updated 0 if not
 */

int update_flag(const char *s, int *indx, op *opt)
{
if (opt->filed_width || opt->h || opt->l || opt->precision != -1)
{
return (0);
}
if (s[*indx] == '0')
{
opt->zero_flag = 1;
}
else if (s[*indx] == ' ')
{
opt->space_flag = 1;
}
else if (s[*indx] == '+')
{
opt->plus_flag = 1;
}
else if (s[*indx] == '-')
{
opt->minus_flag = 1;
}
else if (s[*indx] == '#')
{
opt->hash_flag = 1;
}
else
{
return (0);
}
*indx = *indx + 1;
return (1);
}
/**
 * update_field_width - update field width
 * @s: formatted string
 * @indx: pointer to the indx of the options
 * @opt: options
 * Return: 1 if any option or flag is updated 0 if not
 */

int update_field_width(const char *s, int *indx, op *opt)
{
if (opt->h || opt->l || opt->precision  != -1)
{
return (0);
}
opt->filed_width = get_num(s, indx);
return (1);
}
/**
 * update_precision - update precision
 * @s: formatted string
 * @indx: pointer to the indx of the options
 * @opt: options
 * Return: 1 if any option or flag is updated 0 if not
 */
int update_precision(const char *s, int *indx, op *opt)
{
if (opt->h || opt->l)
{
return (0);
}
if (s[(*indx) + 1] == '-')
{
return (0);
}
opt->precision = get_num(s, indx);
return (1);
}
