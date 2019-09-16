#include <stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int sum=0;
    int reducemaxi=-1;
    int reducemax=1;

    for(int i=0; i<n; i++)
    {
        int init;
        scanf("%d",&init);

        int reducesum=0;
        for(int j=0; j<m; j++)
        {
            int reduce;
            scanf("%d",&reduce);
            reducesum+=reduce;
        }
        if(reducemax>reducesum)
        {
            reducemax=reducesum;
            reducemaxi=i+1;
        }
        sum+=init+reducesum;
    }

    printf("%d %d %d", sum, reducemaxi, -reducemax);
}
