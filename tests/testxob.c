#include "xob.h"
int main(void)
{
    char *str;
    char arrb[3] = {'0', '1'};
    char arrx[16] = {
        '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F'};
    str = conv_to_xob(4294967295, 'X');
    printf("%s\n", str);
    free(str);
    str = conv_to_xob(4294967295, 'b');
    printf("%s\n", str);
    free(str);
    return 0;
}