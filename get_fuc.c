#include "main.h"
/**
 *get_op_fuction- get the function based on a giver identifier
 *@c: option identifier
 *Return: a function pointer corresponding to option identifier or NULL
 */
int (*get_op_fuction(char c))(const char *, int *, op *)
{
int i = 0;
op_function funcs[] = {
{'0', update_flag},
{' ', update_flag},
{'+', update_flag},
{'-', update_flag},
{'#', update_flag},
{'.', update_precision},
{'h', update_len_modifier},
{'l', update_len_modifier},
{'\0', NULL},
};
while (funcs[i].id != '\0')
{
if (funcs[i].id == c)
{
return (funcs[i].func);
}
i++;
}
return (NULL);
}
/**
 *get_conv_fuction - get the function based on a giver identifier
*@c: format specifier
*Return: a function pointer corresponding to format specifier or NULL
*/
char *(*get_conv_fuction(char c))(va_list *, op *)
{
int i = 0;

conv_function funcs[] = {
{'c', ctostr},
{'s', tostr},
{'i', _itos},
{'d', _itos},
{'b', _itob},
{'u', _uitos},
{'x', _itox},
{'X', _itoX},
{'o', ito_oc},
{'r', rev},
{'R', rot13},
{'S', custom_str},
{'p', ptr_to_str},
{'\0', NULL},
};
while (funcs[i].id != '\0')
{
if (funcs[i].id == c)
{
return (funcs[i].func);
}
i++;
}
return (NULL);
}
