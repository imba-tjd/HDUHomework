#include <assert.h> // assert
#include <math.h>   // pow
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

static void PaiXuInternal(int array[], const int from, const int to)
{
    const int length = to - from;
    if (from >= to)
        assert(false);
    else if (length == 1)
        return;

    const int step = (int)pow(length, 0.5); // 每个子问题的长度为根号n
    int from2 = from;                       // 子问题开头
    int to2 = from + step;                  // 子问题结尾
    while (to2 < to)
    {
        PaiXuInternal(array, from2, to2);
        from2 = to2; // 下一个子问题
        to2 += step;
    }
    PaiXuInternal(array, from2, to); // 最后一个子问题长度可能不足根号n

    int *newArray = malloc((length) * sizeof(int));
    int *p = newArray;
    // char flags[length];
    bool *flags = calloc(length, sizeof(bool)); // 标识是否已经取出

    while (p < newArray + length) // 合并
    {
        int mini = -1; // 最小项的下标

        from2 = from;
        to2 = from + step;
        while (to2 < to)
        {
            for (int i = from2; i < to2; i++)                                       // 遍历子问题
                if (flags[i - from] == 0 && (mini == -1 || array[i] < array[mini])) // 未被取出时，最小项不存在或小于最小项
                    mini = i;
            from2 = to2;
            to2 += step;
        }
        for (int i = from2; i < to; i++)
            if (flags[i - from] == 0 && (mini == -1 || array[i] < array[mini]))
                mini = i;

        flags[mini - from] = 1; // 注意偏移
        *p++ = array[mini];
    }

    memcpy(array + from, newArray, length * sizeof(int)); // 注意偏移
    free(newArray);
    free(flags);
}

void PaiXu(int length, int array[length])
{
    return PaiXuInternal(array, 0, length);
}

static int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
int main(void)
{
    int length = sizeof(arr) / sizeof(*arr);

    for (int i = 0; i < length; i++)
        printf("%d ", arr[i]);
    putchar('\n');

    PaiXu(length, arr);
    for (int i = 0; i < length; i++)
        printf("%d ", arr[i]);
    putchar('\n');

    return 0;
}

void PaiXu(int length, int array[length])
{
    return PaiXuInternal(array, 0, length);
}

static int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
int main(void)
{
    int length = sizeof(arr) / sizeof(*arr);

    for (int i = 0; i < length; i++)
        printf("%2d ", arr[i]);
    putchar('\n');

    PaiXu(length, arr);
    for (int i = 0; i < length; i++)
        printf("%2d ", arr[i]);
    putchar('\n');

    return 0;
}
