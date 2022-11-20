#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#define HEX_UPPER  "0123456789ABCDEF"
#define HEX_LOWER  "0123456789abcdef"
#define BINARY  "01"
#define OCTAL  "01234567"

/** struct function - struct containing
 * an identifier and function pointer
 *@id: identifier for the function
*@func: a pointer to function
*/
struct function
{
char id;
char *(*func)(va_list *);
};
int _printf(const char *format, ...);
int check_buff_overflow(char *buff, int size_r);
char *(*get_fuction(char c))(va_list *);
/*sting and char conversion*/
char *ctostr(va_list *ap);
char *tostr(va_list *ap);
/* number conversion*/
char *_uitos(va_list *ap);
char *_itos(va_list *ap);
/*conversion to hex, binary and octal*/
char *_itox(va_list *ap);
char *_itoX(va_list *ap);
char *_itob(va_list *ap);
char *ito_oc(va_list *ap);
/* custom conversions*/
char *rot13(va_list *ap);
char *rev(va_list *ap);
char *custom_str(va_list *ap);
/*helper functions*/
int _strlen(char *s, int non_prt);
char *conv_to_xob(unsigned int n, char flag);
char *num_to_str(unsigned int n);
char *_strcpy(char *dest, char *src);
char *_strdup1(char *str);
char *add_sign(char sign, char *n);
#endif
