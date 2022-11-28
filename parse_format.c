#include "main.h"
/**
 * parse_format - parse the formatted string
 * @format: formatted string
 * @ap: argument paramater
 * @buffer: buffer
 * Return: total length
 */
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
/**
 * parse_specifier - parse the formatted string to get specifier
 * @s: formatted string
 * @indx: a pointer to the indx to start from
 * @ap: argument paramater
 * Return: total length
 */

char *parse_specifier(const char *s, int *indx, va_list *ap)
{
char *str;
char id;
op options = {0, 0, 0, 0, 0, 0, -1, 0, 0};
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
/**
 * update_buff - updated buffer with the formatted
 * @buff: buffer to updated
 * @str: string
 * @size_r: curren size of the buffer
 * @tlen: total length
 */
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
/**
 * convert - convert argument according to specifier
 * @id: format specifier
 * @ap: argument parameter
 * @opt: options
 * Return: convert sting
 */
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
