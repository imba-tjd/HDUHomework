#include <stdio.h>
// #include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);

    int sum=0;
    int droptree[1000]= {0};
    int droptimes=0;

    for(int i=0; i<n; i++)
    {
        int m;
        scanf("%d",&m);

        int init;
        scanf("%d",&init);

        int reducesum=0;
        for(int j=1; j<m; j++)
        {
            int work;
            scanf("%d",&work);
            if(work<=0)
                reducesum+=work;
            else
            {
                if(init+reducesum>work && droptree[i]==0)
                {
                    droptree[i]=1;
                    droptimes++;
                }
                init=work;
                reducesum=0;
            }
        }

        sum+=init+reducesum;
    }

    int e=0;
    for(int i=1; i<n-1; i++)
        e+=droptree[i-1]&&droptree[i]&&droptree[i+1];
    e+=droptree[n-1]&&droptree[0]&&droptree[1];
    e+=droptree[n-2]&&droptree[n-1]&&droptree[0];

    printf("%d %d %d\n",sum,droptimes,e);
}
