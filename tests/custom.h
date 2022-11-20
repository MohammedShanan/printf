#ifndef CUSTM_H
#define CUSTM_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define HEX_UPPER "0123456789ABCDEF"
#define HEX_LOWER "0123456789abcdef"
#define BINARY "01"
#define OCTAL "01234567"
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

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */

char *_strdup(char *str)
{
char *new_str;
int size;
if (str == NULL)
{
return (NULL);
}
size = _strlen(str, 1) + 1;
new_str = (char *)malloc(size);
if (new_str == NULL)
{
return (NULL);
}
return (_strcpy(new_str, str));
}

char *rot13(char *s)
{
int i = 0, n;
char *str = (char *)malloc(_strlen(s, 1) + 1);
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

char *rev(char *s)
{
int i = 0, j;
char *rev = (char *)malloc(_strlen(s, 1) + 1);
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

char *conv_to_xob(unsigned int n, char flag)
{
int i, rem, len_tmp, div;
char *tmp, *s, *arr;
len_tmp = div = 16;
if (flag == 'b')
{
div = 2, len_tmp = 32;
arr = OCTAL;
}
else if (flag == 'o')
{
div = 8, len_tmp = 11;
arr = BINARY;
}
else if (flag == 'x')
{
arr = HEX_LOWER;
}
else
{
arr = HEX_UPPER;
}
tmp = (char *)malloc(len_tmp + 1);
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
s = _strdup(tmp + i + 1);
free(tmp);
return (s);
}
char *custom_str(char *s)
{
char *hex, *cstm_s;
int i, j = 0, len_s, len_nall, len_cstms;
len_s = _strlen(s, 1);                      /*length s with none printable chars*/
len_nall = _strlen(s, 0);                   /*length s without none printable chars*/
len_cstms = (len_s - len_nall) * 3 + len_s; /*length custom string*/
cstm_s = (char *)malloc(len_cstms + 1);
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
#endif