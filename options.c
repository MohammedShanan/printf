# include "main.h"
/**
 * update_len_modifier - update the length modifier option
 * @c: 
 */
int update_len_modifier(const char *s, int indx ,op *opt)
{
    if (s[indx]== 'h')
    {
        opt->h = 1;
    }
    else
    {
        opt->l = 1;
    }
    return (1);
}

int update_flag(const char *s, int indx, op *opt)
{
    if (s[indx] == '0')
    {
        opt->zero_flag = 1;
    }
    else if (s[indx] == ' ')
    {
        opt->space_flag  = 1;
    }
    else if (s[indx] == '+')
    {
        opt->plus_flag = 1;
    }
    else if (s[indx] == '-')
    {
        opt->minus_flag = 1;
    }
    else if (s[indx] == '#')
    {
        opt->hash_flag = 1;
    }
    else
    {
        return (0);
    }
    return (1);
}

int update_field_width(const char *s, int indx, op *opt)
{
    int i;
    if (opt == NULL)
    {
        i = s[indx];
    }
    i = 0;
    return (i);
}

int update_precision(const char *s, int indx, op *opt)
{
    int i;
    if (opt == NULL)
    {
        i = s[indx];
    }
    i = 0;
    return (i);
}