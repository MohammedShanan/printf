#include "main.h"
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
        }
        else
        {
            i++;
            if (format[i] == '%')
            {
                size_r = check_buff_overflow(buffer, size_r);
                buffer[size_r] = '%';
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
                }
                free(s);
                i++;
            }
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