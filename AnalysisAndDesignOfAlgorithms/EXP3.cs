using System;
using System.Collections.Generic;

class ShiYanSan
{
    static void Main()
    {
        var list = new List<int>() { 4, 3, 2, 1 }; // 表示4个序列分别有4、3、2、1个元素
        int count = 0;
        while (list.Count > 1)
        {
            list.Sort(); // 元素数量从小到大排序
            int a = list[0];
            int b = list[1];
            list.Add(a + b);
            count += a + b - 1;
            list.Remove(a);
            list.Remove(b);
        }
        Console.WriteLine(count);
    }
}
