#include <stdio.h>
#include "getmd5.h"

int main()
{
    char md5[33];
    FILE *f = fopen("plain.txt", "rb");
    if(f == NULL)
        return -1;

    getmd5(f, md5);
    md5[32] = '\0';
    puts(md5);
    fclose(f);
}
