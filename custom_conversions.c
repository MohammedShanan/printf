#include "main.h"
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
 * rev_string - reverse a string
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
len_s = _strlen(s, 1); /*length s with none printable chars*/
len_nall = _strlen(s, 0); /*length s without none printable chars*/
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
