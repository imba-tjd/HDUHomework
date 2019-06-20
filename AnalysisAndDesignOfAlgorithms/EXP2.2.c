#include <stdio.h>
#include <stdlib.h>

static int *Array;
// static int Array[15];
static int Rows;

static inline int GetNum(int row, int position)
{
    int index = row * (row - 1) / 2 + position - 1; // 前row-1行相加，首项1末项row-1项数row-1
    int result = Array[index];
    return result;
}

static inline int Max(int a, int b)
{
    return a > b ? a : b;
}

int MaxArray(int row, int position)
{
    int current = GetNum(row, position);
    if (row == Rows)
        return current;
    else
        return current + Max(MaxArray(row + 1, position), MaxArray(row + 1, position + 1));
}

int main(void)
{
    scanf("%d", &Rows);
    int count = (1 + Rows) * Rows / 2 - 1;
    Array = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++)
        scanf("%d", &Array[i]);
    printf("%d", MaxArray(1, 1));

    return 0;
}
