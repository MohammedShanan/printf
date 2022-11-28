#include "main.h"
#include <stdio.h>
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
    _printf("String:[%.4s]\n", "I am a string !");
    printf("String:[%.4s]\n", "I am a string !");
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
if (format == NULL)
{
return (-1);
}
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
