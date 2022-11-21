#include "main.h"
#include <unistd.h>
#include<stdio.h>
int main(void)
{
    unsigned int ui = UINT_MAX;
    int len;
    size_t addr = 0;
    printf("%p\n", addr);
    _printf("%p\n", addr);
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

