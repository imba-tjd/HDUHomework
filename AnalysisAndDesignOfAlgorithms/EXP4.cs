using System;
using System.Linq;
using System.Collections.Generic;

class Championship
{
    class Node
    {
        internal Node Win, Lose; // 叶子节点为null，否则分别指向大的和小的节点
        internal int Value; // 大的Node的值

        internal Node(Node a, Node b)
        {
            if (a.Value >= b.Value)
                (Win, Lose, Value) = (a, b, a.Value);
            else
                (Win, Lose, Value) = (b, a, b.Value);
        }
        internal Node(int value) => Value = value;

        internal IEnumerable<Node> GetLoses() => Lose == null ? // 获得所有和最大的比过的小的节点
            Enumerable.Empty<Node>() : new[] { Lose }.Concat(Win.GetLoses()); // 叶子节点时返回空集，因为此节点是最大的节点
    }

    readonly IEnumerable<Node> collection;
    Node finalMatch;

    public Championship(IEnumerable<int> collection) => this.collection = collection.Select(x => new Node(x)); // 把int集合变成Node集合
    Championship(IEnumerable<Node> collection) => this.collection = collection;

    IEnumerable<Node> MatchOneTurn(IEnumerable<Node> nodes)
    {
        var enumerator = nodes.GetEnumerator();
        while (enumerator.MoveNext() == true) // 两两组合建立新Node
        {
            Node a = enumerator.Current;
            if (enumerator.MoveNext() == true)
                yield return new Node(a, enumerator.Current);
            else
                yield return a; // 如果最后只有一个就直接返回
        }
    }
    public void MatchToFinal()
    {
        IEnumerable<Node> match = collection;
        while (true)
        {
            match = MatchOneTurn(match);
            using (var enumerator = match.GetEnumerator())
            {
                enumerator.MoveNext();
                var result = enumerator.Current;
                if (enumerator.MoveNext() == false) // 如果集合中只有一个元素，则完成；否则循环
                {
                    finalMatch = result;
                    break;
                }
            }
        }
    }
    public int GetMax()
    {
        if (finalMatch == null)
            MatchToFinal();
        return finalMatch.Win?.Value ?? finalMatch.Value;
    }
    public int GetMaxButFirst()
    {
        if (finalMatch == null)
            MatchToFinal();
        return finalMatch.Lose == null ? finalMatch.Value : new Championship(finalMatch.GetLoses()).GetMax();
    }

    static void Main()
    {
        //var chan = new Championship(new[] { 42, 69, 68 });
        var chan = new Championship(new[] { 42, 69, 68, 83, 36, 90, 78, 91, 82, 76, 56, 92, 73, 94, 11, 62, 17, 31, 10, 33, 27, 12, 85, 23, 21 });
        Console.WriteLine(chan.GetMax());
        Console.WriteLine(chan.GetMaxButFirst());
    }
}
