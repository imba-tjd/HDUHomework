/*
这个代码是错误的，按照我的理论根本不需要Record数组，只要TimeTable[100000][2]
测试用例：
1
2 1
00:00:10 10
00:00:10 30
00:00:10 00:00:30
应输出：40，实际输出：60，即30+30
*/
#include <stdio.h>
#include <string.h>

static int Time2Int()
{
    int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int main()
{
    int _n;
    scanf("%d", &_n);
    int i;
    for (i = 0; i < _n; i++)
    {
        int n, q;
        scanf("%d %d", &n, &q);
        int TimeTable[100000] = {0};
        int Records[24 * 3600] = {0};
        int tablecount = 0;

        int j;
        for (j = 0; j < n; j++)
        {
            int num, time;
            time = Time2Int();
            TimeTable[tablecount] = time;
            tablecount++;

            scanf("%d", &num);
            Records[time] = num;
        }
        int k;
        for (k = 0; k < q; k++)
        {
            int total = 0, from, to;
            from = Time2Int();
            to = Time2Int();

            int tablecount2 = 0;
            for (; tablecount2 < tablecount; tablecount2++)
                if (TimeTable[tablecount2] >= from)
                    break;

            while (tablecount2 < tablecount && TimeTable[tablecount2] <= to)
            {
                total += Records[TimeTable[tablecount2]];
                tablecount2++;
            }
            printf("%d\n", total);
        }
    }
}
