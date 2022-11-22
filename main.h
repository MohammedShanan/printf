#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct op - struct containing  options
 *@hash_flag: member 1
 *@zero_flag: member 2
 *@space_flag: member 3
 *@plus_flag: member 4
 *@minus_flag: member 5
 *@filed_width: member 6
 *@precision: member 7
 *@h: member 8
 *@l: member 9
 */
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
 * struct conv_function - id and function pointer
 *
 *@id: format specifier
 *@func: a pointer to fuction
 */
typedef struct conv_function
{
    char id;
    char *(*func)(va_list *);
} conv_function;
/**
 * struct op_function - id and function pointer
 *
 *@id: format specifier
 *@func: a pointer to fuction
 */
typedef struct op_function
{
    char id;
    int (*func)(const char *, int *, op *);
} op_function;

int _printf(const char *format, ...);
/*parsing functions*/
int parse_format(const char *format, va_list *ap, char *buffer);
char *parse_specifier(const char *s, int *indx, va_list *ap);
void update_buff(char *buff, char *str, int *size_r, int *tlen);
int check_buff_overflow(char *buff, int size_r);
char *convert(char id, va_list *ap, op *opt);




/*options functions*/
int update_options(const char *s, int *indx, op *opt);
int update_flag(const char *s, int *indx, op *opt);
int update_len_modifier(const char *s, int *indx, op *opt);
int update_precision(const char *s, int *indx, op *opt);
int update_field_width(const char *s, int *indx, op *opt);
/*apply options functions*/
char *apply_options(char id, char *str, op *options);
char *apply_precision(char *str, int pre);
char *apply_sign(char *str, char id, op *opt);
char *apply_filed_width(char *str, int width, int minus_flag);
char *apply_zero(char *str, char id, op *opt);
char *apply_len_modifier(char id, op *opt, va_list *ap);
void reset_options(op *opt);
/*get function functions*/
char *(*get_conv_fuction(char c))(va_list *);
int (*get_op_fuction(char c))(const char *, int *, op *);
/*sting and char conversion*/
char *ctostr(va_list *ap);
char *tostr(va_list *ap);
/* number conversion*/
char *_uitos(va_list *ap);
char *_itos(va_list *ap);
char *short_tos(va_list *ap);
char *unsigned_short_tos(va_list *ap);
char *long_tos(va_list *ap);
char *unsigned_long_tos(va_list *ap);
char *num_to_str(unsigned long n);
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
int get_num(const char *s, int *indx);
int is_c_in_str(char c, char *str);
char *pad_zeros(int num_z, char *str);
#endif