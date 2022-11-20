#include"../main.h"
int main(void)
{
    unsigned int i = (unsigned int)INT_MAX + 1024;
    _printf("test s %s and char %c", "string", 'c');
    _printf("test int %i\ndecimal %d\nunsigned int %u", 150, -150, i);
    _printf("test 98 binary  %b\nhex %x\nHEX %X\noctal %o", 98, 98, 98, 98);
    _printf("test revere  %r\nrot13 %R", "thgir", "pnc");
    _printf("%S", "test new line \n test tab \t");
    return 0;
}

/*gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c*/