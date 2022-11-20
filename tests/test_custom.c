#include "custom.h"
int main(void)
{
    char *str;
    str = rev("thgir");
    printf("%s\n", str);
    free(str);
    str = rot13("pnc123456789");
    printf("%s\n", str);
    free(str);
    str = custom_str("\n\n");
    printf("%s\n", str);
    free(str);
    return 0;
}
