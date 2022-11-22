#include "main.h"
#include <stdio.h>
/**
 * _printf - print formatted string
 * @format: string to print
 * Return: number of characters printed
 */
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
