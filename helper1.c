#include "main.h"
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
 * get_num - convert number from sting it int
 * @s: string
 * @indx: a pointer to the indx of the first digit of the number
 * Return: number as int
 */
int get_num(const char *s, int *indx)
{
unsigned int num = 0;
if (s[*indx] == '.')
{
*indx = *indx + 1;
}
while (s[*indx] >= '0' && s[*indx] <= '9')
{
num *= 10;
num += s[*indx] - '0';
*indx = *indx + 1;
}
return (num);
}
/**
 * is_c_in_str - check if a char in string or not
 * @c: char
 * @s: string
 * Return: 1 if char is found 0 if not
 */
int is_c_in_str(char c, char *str)
{
int i;
for (i = 0; str[i]; i++)
{
if (c == str[i])
{
return (1);
}
}
return (0);
}
