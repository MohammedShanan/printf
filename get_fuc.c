#include "main.h"

/**
 *get_op_fuction- get the function based on a giver identifier
 *@c: identifier
 *Return: a function pointer corresponding to the identifier or NULL
 */
int (*get_op_fuction(char c))(const char *,int ,op *)
{
    int i = 0;
    struct op_function funcs[] = {
        {'0', update_flag},
        {' ', update_flag},
        {'+', update_flag},
        {'-', update_flag},
        {'#', update_flag},
        {'.', update_precision},
        {'h', update_len_modifier},
        {'l', update_len_modifier},
        {'w', update_field_width},
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
 *@c: identifier
 *Return: a function pointer corresponding to the identifier or NULL
 */
char *(*get_conv_fuction(char c))(va_list *)
{
    int i = 0;
    struct conv_function funcs[] = {
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
