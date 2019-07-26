#include <stdio.h>

void Print(int a, double mid, int b)
{
    if (a < b)
    {
        int t = a;
        a = b;
        b = t;
    }

    if (mid - (int)mid != 0)
        printf("%d %.1f %d", a, mid, b);
    else
        printf("%d %.0f %d", a, mid, b);
}

int main()
{
    int a, b, midt;
    double mid;

    int n;
    scanf("%d", &n);

    scanf("%d", &a);
    if (n == 1)
        printf("%d %d %d", a, a, a);
    if (n == 2)
    {
        scanf("%d", &b);
        mid = a + (b - a) / 2.0;
        Print(a, mid, b);
    }

    int i = 1;
    for (; i < (n - 1) / 2; i++)
        scanf("%*d");

    scanf("%d", &midt); // (n - 1) / 2
    i++;
    if (n % 2 == 0)
    {
        int t;
        scanf("%d", &t); // (n - 1) / 2 + 1
        mid = midt + (t - midt) / 2.0;
        i++;
    }
    else
        mid = midt;

    for (; i < n - 1; i++)
        scanf("%*d");

    scanf("%d", &b);

    Print(a, mid, b);
}
