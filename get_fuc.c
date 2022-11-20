#include "main.h"

/**
 *get_fuction- get the function based on a giver identifier
*@c: identifier
*Return: a function pointer corresponding to the identifier or NULL
*/
char *(*get_fuction(char c))(va_list *)
{
int i = 0;
struct function funcs[] =
{
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
