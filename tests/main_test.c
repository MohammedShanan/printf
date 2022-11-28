#include "main_test.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
/*_printf("%p\n", (void *)0x7ffe637541f0);
_printf("%u\n", (void *)0x7ffe637541f0);
printf("%p\n", (void *)0x7ffe637541f0);
_printf("%p\n", (void *)0x7ffe637541f0);*/
/*gcc -Wall -Werror -Wextra -pedantic -std=gnu89  main_test.o -L. -lprtf -o test*/
int main(void)
{
int len;
int len2;
unsigned int ui;
void *addr;
len = _printf("Let's try to printf a simple sentence.\n");
len2 = printf("Let's try to printf a simple sentence.\n");
ui = (unsigned int)INT_MAX + 1024;
addr = (void *)0x7ffe637541f0;
_printf("%%");
_printf("Length:[%+0.7d, %i]\n", 0, len);
printf("Length:[%+07d, %i]\n", 0, len2);
_printf("Negative:[% 8.7d]\n", -762534);
printf("Negative:[% 8.7d]\n", -762534);
_printf("Unsigned:[%u]\n", ui);
printf("Unsigned:[%u]\n", ui);
_printf("Unsigned octal:[%o]\n", ui);
printf("Unsigned octal:[%o]\n", ui);
_printf("Unsigned hexadecimal:[%.14x, %X]\n", ui, ui);
printf("Unsigned hexadecimal:[%.14x, %X]\n", ui, ui);
_printf("Character:[%c]\n", 'H');
printf("Character:[%c]\n", 'H');
_printf("String:[%s]\n", "I am a string !");
printf("String:[%s]\n", "I am a string !");
_printf("Address:[%p]\n", addr);
printf("Address:[%p]\n", addr);
len = _printf("Percent:[%%]\n");
len2 = printf("Percent:[%%]\n");
_printf("Len:[%d]\n", len);
printf("Len:[%d]\n", len2);
_printf("Unknown:[%k]\n");
printf("Unknown:[%k]\n");
return (0);
}
int _printf(const char *format, ...)
{

char *buffer;
int size_r = 0, total_len = 0;
va_list ap;
buffer = malloc(sizeof(char) * 1024);
if (buffer == NULL)
{
return (0);
}
va_start(ap, format);
total_len = parse_format(format, &ap, buffer);
va_end(ap);
size_r = _strlen(buffer, 1);
write(1, buffer, size_r);
free(buffer);
return (total_len);
}

int check_buff_overflow(char *buff, int size_r)
{
if (size_r == 1024)
{
write(1, buff, size_r);
return (0);
}
return (size_r);
}
char *(*get_conv_fuction(char c))(va_list *, op *)
{
int i = 0;
struct conv_function funcs[] =
{
{'c', ctostr},
{'s', tostr},
{'i', _itos},
{'d', _itos},
{'b', _itob},
{'u', _uitos},
{'x', _itox},
{'X', _itoX},
{'o', ito_oc},
{'r', rev},
{'R', rot13},
{'S', custom_str},
{'p', ptr_to_str},
{'\0', NULL},
};
while (funcs[i].id != '\0')
{
if (funcs[i].id == c)
{
return (funcs[i].func);
}
i++;
}
return (NULL);
}

char *rot13(va_list *ap, op *opt UNUSED)
{
int i = 0, n;
char *s = va_arg(*ap, char *);
char *str = malloc(_strlen(s, 1) + 1);
if (s == NULL || str == NULL)
{
return (NULL);
}
while (s[i])
{
if (s[i] >= 'A' && s[i] <= 'Z')
{
n = s[i] % 'A';
}
else if (s[i] >= 'a' && s[i] <= 'z')
{
n = s[i] % 'a';
}
else
{
str[i] = s[i];
i++;
continue;
}
n = n + 13;
n = n % 26;
str[i] = s[i] < 'a' ? 'A' + n : 'a' + n;
i++;
}
str[i] = '\0';
return (str);
}

char *rev(va_list *ap, op *opt UNUSED)
{
int i = 0, j;
char *s = va_arg(*ap, char *);
char *rev = malloc(_strlen(s, 1) + 1);
if (s == NULL || rev == NULL)
{
free(rev);
return (NULL);
}
j = _strlen(s, 1) - 1;
while (j >= 0)
{
rev[i] = s[j];
i++;
j--;
}
rev[i] = '\0';
return (rev);
}

char *custom_str(va_list *ap, op *opt UNUSED)
{
char *s = va_arg(*ap, char *);
char *hex, *cstm_s;
int i, j = 0, len_s, len_nall, len_cstms;
len_s = _strlen(s, 1);                      /*length s with none printable chars*/
len_nall = _strlen(s, 0);                   /*length s without none printable chars*/
len_cstms = (len_s - len_nall) * 3 + len_s; /*length custom string*/
cstm_s = malloc(len_cstms + 1);
if (cstm_s == NULL)
{
return (NULL);
}
for (i = 0; s[i]; i++)
{
if (s[i] < 32 || s[i] >= 127)
{
hex = conv_to_xob(s[i], 'X');
cstm_s[j++] = '\\', cstm_s[j++] = 'x';
cstm_s[j++] = hex[1] == '\0' ? '0' : hex[0];
cstm_s[j++] = hex[1] == '\0' ? hex[0] : hex[1];
free(hex);
}
else
{
cstm_s[j++] = s[i];
}
}
cstm_s[j] = '\0';
return (cstm_s);
}
char *_itob(va_list *ap, op *opt UNUSED)
{
unsigned int n = va_arg(*ap, unsigned int);
return (conv_to_xob(n, 'b'));
}
int _strlen(char *s, int non_prt)
{
int len;
len = 0;
while (*s)
{
if (!non_prt && (*s < 32 || *s >= 127))
{
s++;
continue;
}
len++;
s++;
}
return (len);
}

char *_strcpy(char *dest, char *src)
{
int i;

for (i = 0; src[i]; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}

char *_strdup1(char *str)
{
char *new_str;
int size;
if (str == NULL)
{
return (NULL);
}
size = _strlen(str, 1) + 1;
new_str = malloc(size);
if (new_str == NULL)
{
return (NULL);
}
return (_strcpy(new_str, str));
}

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

void update_buff(char *buff, char *str, int *size_r, int *tlen)
{
int i = 0;
while (str[i])
{
*size_r = check_buff_overflow(buff, *size_r);
buff[*size_r] = str[i++];
*size_r = *size_r + 1;
*tlen = *tlen + 1;
}
free(str);
}

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

int (*get_op_fuction(char c))(const char *, int *, op *)
{
int i = 0;
struct op_function funcs[] = {
{'0', update_flag},
{' ', update_flag},
{'+', update_flag},
{'-', update_flag},
{'#', update_flag},
{'.', update_precision},
{'h', update_len_modifier},
{'l', update_len_modifier},
{'\0', NULL},
};
while (funcs[i].id != '\0')
{
if (funcs[i].id == c)
{
return (funcs[i].func);
}
i++;
}
return (NULL);
}

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

int update_flag(const char *s, int *indx, op *opt)
{
if (opt->filed_width || opt->h || opt->l || opt->precision)
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

int update_field_width(const char *s, int *indx, op *opt)
{
if (opt->h || opt->l || opt->precision)
{
return (0);
}
opt->filed_width = get_num(s, indx);
return (1);
}

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

int get_num(const char *s, int *indx)
{
unsigned int num = 0;
if (s[*indx] == '.')
{
*indx = *indx + 1;
}
while (s[*indx] >= '0' && s[*indx] <= '9')
{
num *= 10;
num += s[*indx] - '0';
*indx = *indx + 1;
}
return (num);
}

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

int is_c_in_str(char c, char *str)
{
int i;
for (i = 0; str[i]; i++)
{
if (c == str[i])
{
return (1);
}
}
return (0);
}

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

char *parse_specifier(const char *s, int *indx, va_list *ap)
{
char *str;
char id;
op options = {0, 0, 0, 0, 0, 0, 0, 0, 0};
while (1)
{
if (!update_options(s, indx, &options))
{
id = s[*indx];
break;
}
}
str = convert(id, ap, &options);
reset_options(&options);
return (str);
}

char *apply_precision(char *str, int pre)
{
char *s;
s = pad_zeros(pre, str);
return (s);
}

char *add_sign(char *sign, char *n)
{
char *str;
int i, j = 0, len_Str;
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

char *num_to_str(unsigned int n)
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
n = (n - (tens * digit));
tens /= 10;
i++;
}
s[i] = '\0';
return (s);
}


int parse_format(const char *format, va_list *ap, char *buffer)
{
char *s;
int i, size_r, len;
i = size_r = len = 0;
while (format[i])
{
if (format[i] != '%')
{
size_r = check_buff_overflow(buffer, size_r);
buffer[size_r++] = format[i++];
len++;
}
else
{
i++;
s = parse_specifier(format, &i, ap);
update_buff(buffer, s, &size_r, &len);
i++;
}
}
buffer[size_r] = '\0';
return (len);
}

char *convert(char id, va_list *ap, op *opt)
{
char *(*f)(va_list *, op *);
char *s;
char wrong_id[3] = {'%', '\0'};
if (id == '%')
{
return (_strdup1("%"));
}
f = get_conv_fuction(id);
if (f == NULL)
{
wrong_id[1] = id;
return (_strdup1(wrong_id));
}
s = f(ap, opt);
return (s);
}

char *ptr_to_str(va_list *ap, op *opt UNUSED)
{
size_t n = va_arg(*ap, size_t);
char *s;
s = conv_to_xob(n, 'x');
s = add_sign("0x", s);
return (s);
}

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
s = apply_zero(s, 'u', opt);
return (s);
}

char *_uitos(va_list *ap, op *opt)
{
unsigned int n = va_arg(*ap, unsigned int);
char *s;
s = num_to_str(n);
s = apply_precision(s, opt->precision);
s = apply_sign(s, 'u', opt);
s = apply_zero(s, 'u', opt);
return (s);
}
/*new -----------------------------------------------------------------*/
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
s = apply_sign(s, id, options);
}
s = apply_filed_width(s, options->filed_width, options->minus_flag);
return (s);
}

char *apply_zero(char *str, char id, op *opt)
{
char *s;
if (opt->minus_flag)
{
return (str);
}
if (!is_c_in_str(str[0], "0123456789"))
{
opt->filed_width = opt->filed_width - 1;
}
else if (is_c_in_str(id, "Xx") && opt->hash_flag)
{
opt->filed_width = opt->filed_width - 2;
}
s = pad_zeros(opt->filed_width, str);
opt->filed_width = 0;
return (s);
}

char *pad_zeros(int num_z, char *str)
{
int i, j = 0, len_str;
char *s;
char sign[2] = {'\0'};
len_str = _strlen(str, 1);
if (!is_c_in_str(str[0], "0123456789"))
{
j++, len_str--;
sign[0] = str[0];
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
s = add_sign(sign, s);
free(str);
return (s);
}
