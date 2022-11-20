#include "main.h"
#include <unistd.h>
#include<stdio.h>
/**
 * _printf - print formatted string
 * @format: string to print
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    char *buffer;
    int size_r, total_len = 0;
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

