#include <stdio.h>
#include <string.h>

int n, s, l;
char disks[1000][40 * 1024 * 2]; // l<=n<=10^3; 40KiB==40*1024B ,1B对应2个16进制的字符
unsigned char dexist[1000];
int len;
void Handle();

#define CHARTOINT(c) ((c) >= 'A' ? (c) - 'A' + 10 : (c) - '0')
#define INTTOCHAR(c) ((c) >= 10 ? (c) + 'A' - 10 : (c) + '0')

int main()
{
    scanf("%d %d %d", &n, &s, &l);
    for (int i = 0; i < l; i++)
    {
        int index;
        scanf("%d", &index);
        getchar(); // 吃掉空格
        dexist[index] = 1;
        gets(disks[index]);
        if (len == 0)
            len = strlen(disks[index]); // 在里面判断算了，否则还要判断磁盘是否存在
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        Handle();
}

void Handle()
{
    int b;
    scanf("%d", &b);

    int srow = b / ((n - 1) * s);          // 计算所在的条带行索引，除数是一整行的块数
    int srest = b % ((n - 1) * s) / s + 1; // 剩余的条带

    int pcol = (n - 1 - srow) % n; // 当前行的P在哪列上，一个-1是去掉P，还一个是n是数量不是索引
    if (pcol < 0)
        pcol += n; // C取余后符号取决于被除数，要处理一下；或者也可以放到上一步里直接+n

    int bcol = (pcol + srest) % n; // 由P的列推出块所在条带的列，也是块的列

    int blocki = srow * s + b % s; // 竖着数是第几块
    int datai = blocki * 8;        // 1块是4B，对应8个16进制字符

    if (datai > len) // 指定的块超出阵列总长度
    {
        printf("-\n");
        return;
    }

    char *data = &disks[bcol][datai];

    if (!dexist[bcol])
    {
        if (n != l + 1) // 被读取的缺失且无法推算
        {
            printf("-\n");
            return;
        }
        else
        {
            for (int i = 0; i < n; i++) // 遍历除了当前以外的列
                if (i != bcol)
                    for (int j = 0; j < 8; j++)                    // 一块对应8个字符
                        data[j] ^= CHARTOINT(disks[i][datai + j]); // 异或是对数字运算，不能直接对char运算
            for (int j = 0; j < 8; j++)
                data[j] = INTTOCHAR(data[j]); // 但可最后才转回char
        }
    }

    // printf("%8s", data); // 效果不是最多输出8个，而是不满8个时右对齐前面补空格
    for (int i = 0; i < 8; i++) // 只能一个个输出
        putchar(data[i]);
    putchar('\n');
}
