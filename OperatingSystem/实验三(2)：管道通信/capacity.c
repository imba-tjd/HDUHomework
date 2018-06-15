// https://blog.csdn.net/renchunlin66/article/details/51814382
// https://bbs.csdn.net/topics/390990946#post-398932335
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pipefds[2]; //[0] for read, [1] for write
    pipe(pipefds);
    
    char buf[4096];
    for (int i = 0; i < sizeof(buf); ++i)
    {
        buf[i] = 0x7f;
    }
    
    ssize_t ret = -1;
    
    int loop = 100;
    if (argc > 1)
    {
        loop = atoi(argv[1]);
    }
    
    for (int i = 0; i < loop; ++i)
    {
        printf("loop: %d\n", i);
        ret = write(pipefds[1], buf, sizeof(buf));
        if (ret < 0)
        {
            perror(NULL);
        }
        else
        {
            printf("%d\n", ret);
        }
    } // 当i=16的时候会阻塞，可知管道大小为64k
    
    close(pipefds[0]);
    close(pipefds[1]);
    
    return 0;
}
