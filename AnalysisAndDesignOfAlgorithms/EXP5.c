// 伪代码
Relax(u,v,w){ // 松弛
    if(v.d>u.d+w(u,v)){ // w为直接距离
        v.d=u.d+w(u,v); // 最短距离
        v.p=u; // 前一个节点
    }
}

Dijkstra(G,w,s){
    InitializeSingleSource(G,s);
    S=空集;
    Q=G.V;
    whlie(Q!=空集){
        u=ExtractMin(Q);
        S=S.Add(u);
        foreach v in G.Adj[u] // 所有指出u的节点
            Relax(u,v,w);
    }
}

InitializeSingleSource(G,s){
    foreach v in G.V{
        v.d=无穷;
        v.p=null;
    }
    s.d=0;
}

ExtractMin(Q)
{
    mini = 0;
    for(i=0 to Q.Length)
        if(Q[i].d<Q[mini].d)
            mini=i;
    move(Q[i],[i+1],Q.Length-i);
    Q.Length-=1;
    return Q[i];
}

Heapify(H)
{
    if (H == null)
        return;
    min = H;
    if (H.Left != null && H.Left.Value < H.Value)
        min = H.Left;
    if (H.Right != null && H.Right.Value < H.Value)
        min = H.Right;
    if(min!=H)
    {
        swap(max.Value, H.Value);
        Heapify(max);
    }
}

ExtractMin2(Q)
{
    t = Q[0].Value;
    Q[0] = Q[Q.Length - 1];
    Heapify(Q[0]);
    Q.Length -= 1;
    return t;
}
