#include <assert.h>
#include <stdio.h>

typedef struct
{
    int R;
    int G;
    int B;
} Pixle;

static Pixle pic[1080][1920]; // 看作横向的图，所以第二个分量反而更大

// 单个16进制字符转换成十进制数字
static inline int char2int(char c)
{
    return c >= '0' && c <= '9' ? c - '0' :
           c >= 'a' && c <= 'f' ? c - 'a' + 10 :
           c >= 'A' && c <= 'F' ? c - 'A' + 10 :
           -1;
}

// 两个16进制字符转换成十进制数字
static inline int OneColor2int(char a, char b)
{
    return char2int(a) * 16 + char2int(b);
}

static void FillPixle(Pixle *p, char *line)
{
    if (line[2] == '\0')
    {
        int c = OneColor2int(line[1], line[1]);
        p->R = c;
        p->G = c;
        p->B = c;
    }
    else if (line[4] == '\0')
    {
        p->R = OneColor2int(line[1], line[1]);
        p->G = OneColor2int(line[2], line[2]);
        p->B = OneColor2int(line[3], line[3]);
    }
    else if (line[7] == '\0')
    {
        p->R = OneColor2int(line[1], line[2]);
        p->G = OneColor2int(line[3], line[4]);
        p->B = OneColor2int(line[5], line[6]);
    }
    else
        assert(0);
}

static void PAdd(Pixle *a, Pixle b)
{
    a->R += b.R;
    a->G += b.G;
    a->B += b.B;
}

static void PAve(Pixle *a, int num)
{
    a->R /= num;
    a->G /= num;
    a->B /= num;
}

static inline int PEql(Pixle a, Pixle b)
{
    return a.R == b.R && a.G == b.G && a.B == b.B;
}

// 假如颜色的值是255，要看成三个**字符**输出16进制
static void OneColorPrint_BAD(int c)
{
    int t = c / 100;
    if (t != 0)
        printf("\\x%x", t + '0');
    t = c % 100 / 10;
    if (t != 0) // 此处出了BUG，如果百位不为0，十位为0，仍然要输出十位的0，而此代码不会
        printf("\\x%x", t + '0');
    t = c % 10;
    printf("\\x%x", t + '0');
    // 三个全部为0已经在外面处理了，但假如其中有一个分量为0，仍然要输出0，即最后一个不能有if
}

// 修复上面的BUG
static void OneColorPrint(int c)
{
    char buf[4];
    sprintf(buf, "%d", c);
    for (char *p = buf; *p != '\0'; p++)
        printf("\\x%x", *p); // 注意不用+'0'
}

int main()
{
    int m, n, p, q;
    scanf("%d %d %d %d", &m, &n, &p, &q);
    getchar();  // 去掉换行符
    for (int i = 0; i < n; i++)     // n是行指针界限（“高”）
        for (int j = 0; j < m; j++) // m是纵坐标界限（“宽”）
        {
            char line[8];
            gets(line);
            FillPixle(&pic[i][j], line);
        }

    for (int r = 0; r < n; r += q)
    {
        Pixle pipre = {0};             // 每次换行，值初始化为黑色
        for (int c = 0; c < m; c += p) // (r,c)即一个块的起始坐标
        {
            Pixle pi = {0};
            for (int i = r; i < r + q; i++)
                for (int j = c; j < c + p; j++)
                    PAdd(&pi, pic[i][j]);
            PAve(&pi, p * q);

            if (!PEql(pi, pipre)) // 和前一个颜色一样就不用改
                if (PEql(pi, (Pixle){0}))
                    printf("\\x1B\\x5B\\x30\\x6D"); // 题目说了如果当前颜色是纯黑，直接用重置
                else
                {
                    // 手动更改颜色
                    //printf("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B\\x%X\\x3B\\x%X\\x3B\\x%X\x6D");
                    printf("\\x1B\\x5B\\x34\\x38\\x3B\\x32\\x3B");
                    OneColorPrint(pi.R);
                    printf("\\x3B");
                    OneColorPrint(pi.G);
                    printf("\\x3B");
                    OneColorPrint(pi.B);
                    printf("\\x6D");
                }

            printf("\\x20"); // space

            pipre = pi;
        }
        if (!PEql(pipre, (Pixle){0})) // 如果是黑色就不用输出重置的信息了
            printf("\\x1B\\x5B\\x30\\x6D");
        printf("\\x0A"); // 换行
    }
}
