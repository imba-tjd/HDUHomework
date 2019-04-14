#include <stdio.h>
#include <string.h>

int ROW, COL;
int DP[200][200];
int Stack[2000][2];
int SCount;

int Relax(int r, int c, int value, char level[200][200])
{
    if (r < 0 || r > ROW || c < 0 || c > COL || (level[r][c] == '#'))
        return 0;
    if (DP[r][c] > value + 1)
    {
        DP[r][c] = value + 1;
        return 1;
    }
    else
        return 0;
}

void Explore(int r, int c, char level[200][200])
{
    SCount--;
    if (level[r][c] == 'F')
        return;

    // 不用Stack时这样已经通过测试用例了，但提交后栈溢出
    // if (Relax(r - 1, c, DP[r][c], level))
    //     Explore(r - 1, c, level);
    // if (Relax(r, c - 1, DP[r][c], level))
    //     Explore(r, c - 1, level);
    // if (Relax(r + 1, c, DP[r][c], level))
    //     Explore(r + 1, c, level);
    // if (Relax(r, c + 1, DP[r][c], level))
    //     Explore(r, c + 1, level);

    if (Relax(r - 1, c, DP[r][c], level))
    {
        Stack[SCount][0] = r - 1;
        Stack[SCount][1] = c;
        SCount++;
    }
    if (Relax(r, c - 1, DP[r][c], level))
    {
        Stack[SCount][0] = r;
        Stack[SCount][1] = c - 1;
        SCount++;
    }
    if (Relax(r + 1, c, DP[r][c], level))
    {
        Stack[SCount][0] = r + 1;
        Stack[SCount][1] = c;
        SCount++;
    }
    if (Relax(r, c + 1, DP[r][c], level))
    {
        Stack[SCount][0] = r;
        Stack[SCount][1] = c + 1;
        SCount++;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        SCount = 0;
        char level[200][200];
        memset(DP, 0x3f, 200 * 200 * sizeof(int));

        scanf("%d %d", &ROW, &COL);
        int ok = 0;
        int Rr, Rc;
        int Fr, Fc;

        int j;
        for (j = 0; j < ROW; j++)
        {
            int k;
            for (k = 0; k < COL; k++)
            {
                scanf(" %c", &level[j][k]);
                if (ok != 2)
                {
                    if (level[j][k] == 'R')
                    {
                        Rr = j;
                        Rc = k;
                        ok++;
                        DP[j][k] = 0;
                    }
                    if (level[j][k] == 'F')
                    {
                        Fr = j;
                        Fc = k;
                        ok++;
                    }
                }
            }
        }
        // Explore(Rr, Rc, level);

        Stack[SCount][0] = Rr;
        Stack[SCount][1] = Rc;
        SCount++;
        while (SCount != 0)
            Explore(Stack[SCount - 1][0], Stack[SCount - 1][1], level);

        if (DP[Fr][Fc] == 0x3f3f3f3f)
            puts("Poor Rabbit.");
        else
            printf("%d\n", DP[Fr][Fc]);
    }
}
