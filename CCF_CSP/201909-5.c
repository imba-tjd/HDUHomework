#include <stdio.h>
#include <string.h>

int graph[2000][2000];
int len[2000];
char visited[2000];

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    int A,B;
    scanf("%d %d",&A,&B);

    memset(graph,0x3F,n*n*sizeof(int));

    for(int i=0; i<n-1; i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a-1][b-1]=c;
    }
    memset(len,0x3F,n*sizeof(int));
    len[A-1]=0;

    for(int cnt=0; cnt<n; cnt++)
    {
        int mini;
        int minlen=20000;
        for(int i=0; i<n; i++)
            if(!visited[i] && len[i]<minlen)
            {
                mini=i;
                minlen=len[i];
            }
        visited[mini]=1;
        for(int i=0;i<n;i++)
        {
            if(!visited[i]&&len[mini]+graph[mini][i]<len[i])
                len[i] = len[mini]+graph[mini][i];
        }
    }
    printf("%x",len[B-1]);
}

