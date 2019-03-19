#include <stdio.h>

void MaxAndMin(const unsigned length, int array[length], int *max, int *min)
{
    if (length == 1)
    {
        *max = *min = array[0];
        return;
    }

    const unsigned half = length / 2;
    int max1, max2, min1, min2;
    MaxAndMin(half, array, &max1, &min1);
    MaxAndMin(length - half, array + half, &max2, &min2);
    *max = max1 > max2 ? max1 : max2;
    *min = min1 < min2 ? min1 : min2;
}

int main(void)
{
    int arr[] = {85, 75, 75, 59, 7, 30, 36, 16, 27, 80, 53, 78, 69, 85, 75};
    int max, min;
    MaxAndMin(sizeof(arr) / sizeof(*arr), arr, &max, &min);
    printf("%d %d\n", max, min);
    return 0;
}
