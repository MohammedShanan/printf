#include "main_test.h"
/*gcc -Wall -Werror -Wextra -pedantic -std=gnu89  main_test.o -L. -lprtf -o test*/
int main(void)
{
    unsigned int ui = (unsigned int)INT_MAX + 1024;
    int len;
    _printf("test s %s and char %c", "string", 'c');
    _printf("Character:[%c]\n", 'H');
    _printf("test int %i\ndecimal %d\nunsigned int %u", 150, -150, ui);
    _printf("test 98 binary  %b\nhex %x\nHEX %X\noctal %o", 98, 98, 98, 98);
    _printf("test revere  %r\nrot13 %R", "thgir", "pnc");
    _printf("%S", "test new line \n test tab \t\n");
    len = _printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    _printf("Unknown:[%r]\n");
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    return 0;
}

/**
 * _printf - print formatted string
 * @format: string to print
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    char *buffer, *s;
    int i, size_r, j, total_len;
    char *(*fuc)(va_list *);
    va_list ap;
    i = size_r = j = total_len = 0;
    va_start(ap, format);
    buffer = malloc(sizeof(char) * 1024);
    if (buffer == NULL)
    {
        return (0);
    }
    while (format[i])
    {
        if (format[i] != '%')
        {
            size_r = check_buff_overflow(buffer, size_r);
            buffer[size_r++] = format[i++];
            total_len++;
        }
        else
        {
            i++;
            if (format[i] == '%')
            {
                size_r = check_buff_overflow(buffer, size_r);
                buffer[size_r] = '%';
                total_len++;
            }
            else
            {
                fuc = get_fuction(format[i]);
                j = 0;
                s = fuc(&ap);
                while (s[j])
                {
                    size_r = check_buff_overflow(buffer, size_r);
                    buffer[size_r++] = s[j++];
                    total_len++;
                }
                free(s);
            }
            i++;
        }
    }
    va_end(ap);
    buffer[size_r] = '\0';
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
char *(*get_fuction(char c))(va_list *)
{
    int i = 0;
    struct function funcs[] = {
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
/**
 * rot13 - encode string using rot13
 * @ap: pointer to argument parameter
 * Return: encoded string
 */

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

/**
 * rev - reverse a string
 * @ap: pointer to argument parameter
 * Return: string in reverse
 */

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
/**
 * custom_str - convert a string to a custom string
 * @ap: pointer to argument parameter
 * Return: a custom string with
 * none printable charater replaced by \x
 * followed by the ASCII code value in
 * hexadecimal (upper case - always 2 characters)
 */
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
/**
 * _strlen - returns the length of a string
 * @s: string
 * @non_prt: paramater to determine whether
 * to count non printable charters as part of the string or not
 * Return: length
 */

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

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of original source
 */

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

/**
 * _strdup1 - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */

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
/**
 * _itos - convert  int to string
 * @ap: argument parameter
 * Return: an int as string
 */

char *_itos(va_list *ap)
{
    int n = va_arg(*ap, int);
    char *s;
    if (n < 0)
    {
        n = n * -1;
        s = add_sign('-', num_to_str(n));
        return (s);
    }
    s = num_to_str(n);
    return (s);
}
/**
 * _uitos - convert unsigned int to string
 * @ap: argument parameter
 * Return: an unsigned int as string
 */
char *_uitos(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (num_to_str(n));
}
/**
 * add_sign - add a sign to numbers
 * @sign: sign to add
 * @n: number
 * Return: number with sign in front
 */
char *add_sign(char sign, char *n)
{
    char *str = malloc(_strlen(n, 1) + 2);
    int i, j = 0;
    str[j++] = sign;
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
/**
 * ctostr - char to string
 * @ap: argument parameter
 * Return: char as string
 */
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
/**
 * tostr - string
 * @ap: argument parameter
 * Return: string
 */
char *tostr(va_list *ap)
{
    return (_strdup1(va_arg(*ap, char *)));
}
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
 * _itob - convert unsigned int to binary
 * @ap: argument parameter
 * Return: an unsigned int as binary
 */
char *_itob(va_list *ap)
{
    unsigned int n = va_arg(*ap, unsigned int);
    return (conv_to_xob(n, 'b'));
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
    for (i = len_tmp - 1; n != 0; i--)
    {
        rem = n % div;
        n = n / div;
        tmp[i] = arr[rem];
    }
    tmp[len_tmp] = '\0';
    s = _strdup1(tmp + i + 1);
    free(tmp);
    return (s);
}
