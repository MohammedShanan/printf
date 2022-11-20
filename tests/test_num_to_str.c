#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
char *num_to_str(unsigned int n);
int main(void)
{
    char *str;
    str = num_to_str(4294967295);
    printf("%s\n", str);
    free(str);
    return 0;
}
char *num_to_str(unsigned int n)
{
    int digit, i = 0, len_n = 1;
    char *s;
    double tens = 1;
    while (tens * 10 <= n)
    {
        tens *= 10;
        len_n++;
    }
    s = malloc(len_n + 1);
    if (s == NULL)
    {
        return (NULL);
    }
    while (tens >= 1)
    {
        digit = n / tens;
        s[i] = digit + '0';
        n = (n - (tens * digit));
        tens /= 10;
        i++;
    }
    s[i] = '\0';
    return (s);
}