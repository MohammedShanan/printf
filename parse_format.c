#include "main.h"
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
                buffer[size_r] = '%';
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
    char id;
    while (1)
    {
        if (!update_options(str, *indx_ptr,options))
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

int update_options(const char *s, int indx, op *opt)
{
    int (*fun)(const char *,int, op *);
    fun = get_op_fuction(s[indx]);
    if (fun == NULL)
    {
        return (0);
    }
    return (fun(s, indx , opt));
}
