#include "main_test.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
/*gcc -Wall -Werror -Wextra -pedantic -std=gnu89  main_test.o -L. -lprtf -o test*/
int main(void)
{
    unsigned int ui = UINT_MAX;
    int len;
    printf("%llu\n", (void *)0x7ffe637541f0);
    _printf("%u\n", (void *)0x7ffe637541f0);
    printf("%p\n", (void *)0x7ffe637541f0);
    _printf("%p\n", (void *)0x7ffe637541f0);
    printf("%#-+0l.45i\n");
    _printf("%#-+ 0lh.45s\n");
    printf("%#-+ 0lh.405p\n");
    _printf("%#-+ 0lh.405p\n");
    _printf("b 98 %b b 0%b\nhex 98 %x hex 0 %x\n octal 98 %o octal 0 %o\n", ui, 0, ui, 0, ui, 0);
    _printf("test int %i\ndecimal %d\nunsigned int %u\n", 150, -150, 0);
    _printf("%j]\n");
    _printf("%%%j]\n");
    printf("%%i\n");
    _printf("test s %s and char %c\n", "string", 'c');
    _printf("Character:[%c]\n", 'H');
    _printf("test revere  %r\nrot13 %R\n", "thgir", "pnc");
    _printf("%S", "test new line \n test tab \t\n");
    len = _printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    return 0;
}

int _printf(const char *format, ...)
{

    char *buffer;
    int size_r = 0, total_len = 0, i;
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

/**
 * check_buff_overflow - check if the size of buffer has reached 1024
 * the right the buffer to stdout and reset the buffer
 * @buff: buffer to check
 * @size_r: buffer size
 * Return: 0 of size_r reached 1024, size_r if not
 */
int check_buff_overflow(char *buff, int size_r)
{
    if (size_r == 1024)
    {
        write(1, buff, size_r);
        return (0);
    }
    return (size_r);
}
/**
 *get_fuction- get the function based on a giver identifier
 *@c: identifier
 *Return: a function pointer corresponding to the identifier or NULL
 */
char *(*get_conv_fuction(char c))(va_list *)
{
    int i = 0;
    struct conv_function funcs[] = {
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
    int i, j = 0, len_Str;
    len_Str = _strlen(n, 1) + _strlen(sign, 1);
    char *str = malloc(len_Str + 1);
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
    char id;
    struct op options = {0, 0, 0, 0, 0, 0, 0, 0, 0};
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
                id = get_specifier(format, &i, &options);
                s = convert(id, ap);
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

char get_specifier(const char *str, int *indx_ptr, op *options)
{
    int i;
    char id;
    while (1)
    {
        if (!update_options(str[*indx_ptr], options))
        {
            id = str[*indx_ptr];
            break;
        }
        *indx_ptr = *indx_ptr + 1;
    }
    return (id);
}

char *convert(char id, va_list *ap)
{
    char *(*f)(va_list *);
    char *s;
    f = get_conv_fuction(id);
    if (f == NULL)
    {
        return (NULL);
    }
    s = f(ap);
    return (s);
}

int update_options(char f, op *opt)
{
    int (*fun)(char, op *);
    fun = get_op_fuction(f);
    if (fun == NULL)
    {
        return (0);
    }
    return (fun(f, opt));
}
int update_flag(char f, op *opt)
{
    if (f == '0')
    {
        opt->zero_flag = 1;
    }
    else if (f == ' ')
    {
        opt->space_flag = 1;
    }
    else if (f == '+')
    {
        opt->plus_flag = 1;
    }
    else if (f == '-')
    {
        opt->minus_flag = 1;
    }
    else if (f == '#')
    {
        opt->hash_flag = 1;
    }
    else
    {
        return (0);
    }
    return (1);
}
int (*get_op_fuction(char c))(char, op *)
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
        {'w', update_field_width},
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
int update_len_modifier(char c, op *opt)
{
    if (c == 'h')
    {
        opt->h = 1;
    }
    else
    {
        opt->l = 1;
    }
}
int update_field_width(char c, op *opt)
{
    return (0);
}

int update_precision(char c, op *opt)
{
    return (0);
}
char *ptr_to_str(va_list *ap)
{
    size_t n = va_arg(*ap, size_t);
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