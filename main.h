#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
typedef struct op
{
    int hash_flag;
    int zero_flag;
    int space_flag;
    int plus_flag;
    int minus_flag;
    int filed_width;
    int precision;
    int h;
    int l;
} op;
/**
 *struct function - struct containing
 *an identifier and function pointer
 *@id: identifier for the function
 *@func: a pointer to function
 */
typedef struct conv_function
{
    char id;
    char *(*func)(va_list *);
} conv_function;
typedef struct op_function
{
    char id;
    int (*func)(const char *, int, op *);
} op_function;

int _printf(const char *format, ...);
int check_buff_overflow(char *buff, int size_r);
int parse_format(const char *format, va_list *ap, char *buffer);
void update_buff(char *buff, char *str, int *size_r, int *tlen);
char get_specifier(const char *str, int *indx_ptr, op *options);
int update_options(const char *s, int indx, op *opt);
int update_flag(const char *s, int indx, op *opt);
int update_len_modifier(const char *s, int indx, op *opt);
int update_precision(const char *s, int indx, op *opt);
int update_field_width(const char *s, int indx, op *opt);
char *convert(char id, va_list *ap);
char *(*get_conv_fuction(char c))(va_list *);
int (*get_op_fuction(char c))(const char *, int, op *);
/*sting and char conversion*/
char *ctostr(va_list *ap);
char *tostr(va_list *ap);
/* number conversion*/
char *_uitos(va_list *ap);
char *_itos(va_list *ap);
char *num_to_str(unsigned int n);
/*conversion to hex, binary and octal*/
char *_itox(va_list *ap);
char *_itoX(va_list *ap);
char *_itob(va_list *ap);
char *ito_oc(va_list *ap);
char *ptr_to_str(va_list *ap);
char *conv_to_xob(unsigned int n, char flag);
/* custom conversions*/
char *rot13(va_list *ap);
char *rev(va_list *ap);
char *custom_str(va_list *ap);
/*helper functions*/
int _strlen(char *s, int non_prt);
char *_strcpy(char *dest, char *src);
char *_strdup1(char *str);
char *add_sign(char *sign, char *n);
#endif
