#include "main.h"
/**
 * pad_zeros - pad number with zeros
 * @num_z: number of zeros to be padded
 * @str: string to modify
 * Return: string padded with zeros
 */
char *pad_zeros(int num_z, char *str)
{
int i, j = 0, len_str, negative = 0;
char *s;
len_str = _strlen(str, 1);
if (str[0] == '-')
{
j++, len_str--;
negative = 1;
}
if (len_str >= num_z)
{
return (str);
}
s = malloc(num_z + 1);
if (s == NULL)
{
free(str);
return (NULL);
}
for (i = 0; i < num_z - len_str; i++)
{
s[i] = '0';
}
while (i <= num_z)
{
s[i++] = str[j++];
}
if (negative)
{
s = add_sign("-", s);
}
free(str);
return (s);
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
char *num_to_str(unsigned long n)
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
n = (n - (tens *digit));
tens /= 10;
i++;
}
s[i] = '\0';
return (s);
}
/**
 * reset_options - reset options to zero
 * @opt: struct op
 */
void reset_options(op *opt)
{
opt->filed_width = 0;
opt->hash_flag = 0;
opt->minus_flag = 0;
opt->plus_flag = 0;
opt->zero_flag = 0;
opt->space_flag = 0;
opt->h = 0;
opt->l = 0;
opt->precision = 0;
}
