// fread 和 fopen 必须使用以二进制打开的流，否则会出错
#include <stdio.h>
#define Length(x) (sizeof(x) / sizeof(*x))

int main(void)
{
    char arr1[] = { 1, 1, 26, 1};
    FILE *f1 = fopen("temp.txt", "w");
    int count = fwrite(arr1, sizeof(char), Length(arr1), f1);
    printf("%d\n", count); // 4
    fclose(f1);

    FILE *f2 = fopen("temp.txt", "r"); // use rb will fix this
    char arr2[Length(arr1)];
    count = fread(arr2, sizeof(char), Length(arr1), f2);
    printf("%d\n", count); // 4 on Linux and 2 on MinGW
    fclose(f2);
}
