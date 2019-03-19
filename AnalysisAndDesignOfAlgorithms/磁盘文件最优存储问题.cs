using System;
using System.Collections.Generic;
using System.Linq;

class CiPan
{
    static void Main()
    {
        int count = int.Parse(Console.ReadLine());
        int[] array = Console.ReadLine().Split(' ').Select(x => int.Parse(x)).OrderByDescending(x => x).ToArray(); // 将输入的数据降序排序
        int pall = 0; // 所有输入的概率之和

        LinkedList<int> ll = new LinkedList<int>(); // 自带的双向链表
        bool flag = false;
        foreach (int num in array)
        {
            if (flag == false)
                ll.AddFirst(num);
            else
                ll.AddLast(num);

            pall += num;
            flag = !flag;
        }

        int[] sorted = ll.ToArray();
        double result = 0;
        for (int i = 0; i < count - 1; i++)
            for (int j = i; j < count; j++)
                result += (double)sorted[i] / pall * sorted[j] / pall * (j - i);

        Console.WriteLine(result);
    }
}
