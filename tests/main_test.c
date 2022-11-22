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
    len = printf("%sahmed\n");
    len2 = _printf("%sahmed\n", "");
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
char *(*get_conv_fuction(char c))(va_list *)
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

char *rot13(va_list *ap)
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

char *rev(va_list *ap)
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

char *custom_str(va_list *ap)
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

char *tostr(va_list *ap)
{
    return (_strdup1(va_arg(*ap, char *)));
}

char *_itox(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (conv_to_xob(n, 'x'));
}

char *_itoX(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (conv_to_xob(n, 'X'));
}

char *ito_oc(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (conv_to_xob(n, 'o'));
}

char *_itob(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);

    return (conv_to_xob(n, 'b'));
}

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
            if (format[i] == '%')
            {
                size_r = check_buff_overflow(buffer, size_r);
                buffer[size_r++] = '%';
                len++;
            }
            else
            {
                s = parse_specifier(format, &i, ap);
                if (s == NULL)
                {
                    size_r = check_buff_overflow(buffer, size_r);
                    buffer[size_r++] = '%';
                    len++;
                    continue;
                }
                update_buff(buffer, s, &size_r, &len);
            }
            i++;
        }
    }
    buffer[size_r] = '\0';
    return (len);
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

char *ptr_to_str(va_list *ap)
{
    unsigned long n = va_arg(*ap, unsigned long);
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
    do
    {
        rem = n % div;
        n = n / div;
        tmp[i--] = arr[rem];
    } while (n != 0);
    tmp[len_tmp] = '\0';
    s = _strdup1(tmp + i + 1);
    free(tmp);
    s = add_sign("0x", s);
    return (s);
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

char *apply_precision(char *str, int pre)
{
    char *s;
    s = pad_zeros(pre, str);
    return (s);
}

char *apply_len_modifier(char id, op *opt, va_list *ap)
{
    char *s;
    int i;
    char *(*f)(va_list *);
    conv_function funcs[] =
        {
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

char *unsigned_short_tos(va_list *ap)
{
    unsigned short n = va_arg(*ap, int);
    char *s;
    s = num_to_str(n);
    return (s);
}

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

char *unsigned_long_tos(va_list *ap)
{
    unsigned long n = va_arg(*ap, unsigned long);
    char *s;
    s = num_to_str(n);
    return (s);
}

/*new --------------------------------*/
char *_itos(va_list *ap)
{
    int n = va_arg(*ap, int);
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

char *_uitos(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (num_to_str(n));
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

char *convert(char id, va_list *ap, op *opt)
{
    char *(*f)(va_list *);
    char *s;
    if (is_c_in_str(id, "idu") && (opt->l || opt->h))
    {
        s = apply_len_modifier(id, opt, ap);
    }
    else
    {
        f = get_conv_fuction(id);
        if (f == NULL)
        {
            return (NULL);
        }
        s = f(ap);
    }
    s = apply_options(id, s, opt);
    return (s);
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
