// https://blog.csdn.net/oguro/article/details/53841949
#include <errno.h>
#include <fcntl.h> // O_CREATE
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int fd[2]; // fd[0]读，fd[1]写

void WritePipe(int id, pid_t toWait)
{
    sleep(1);
    close(fd[0]); // 关闭读取管道

    if (toWait != 0)
        waitpid(toWait, NULL, 0);

    // lockf(fd[1], 1, 0); //对写管道加锁

    printf("in child %d (pid=%d)\n", id + 1, getpid());
    char buffer[BUFSIZ];

    sprintf(buffer, "this message is from child %d (pid=%d)", id + 1, getpid());

    ssize_t count;
    if ((count = write(fd[1], buffer, sizeof(buffer))) == -1)
        perror("writing failed.");
    else
        printf("totally write %zd\n", count);

    sleep(1);
    // lockf(fd[1], 0, 0);
    printf("child %d finishes.\n", getpid());

    // exit(0);
}

int main()
{
    pid_t pid[3] = {-1, -1, -1}; //3个子进程
    char buffer[BUFSIZ];
    sem_t *child1sem = NULL, *child2sem = NULL, *child3sem = NULL;
    // sem_init(child1sem, 0, 1); // 无法使用，原因不明
    child1sem = sem_open("/child1", O_CREAT | O_RDWR, 0666, 1);
    child2sem = sem_open("/child2", O_CREAT | O_RDWR, 0666, 0);
    child3sem = sem_open("/child3", O_CREAT | O_RDWR, 0666, 0);

    if (pipe(fd) < 0) //创建管道失败
        perror("creating pipe failed.");

    if ((pid[0] = fork()) < 0)
        perror("fork failed.");

    if (pid[0] == 0)
    {
        sem_wait(child1sem);
        WritePipe(0, 0);
        sem_post(child2sem);
        exit(0);
    }

    if ((pid[1] = fork()) < 0)
        perror("fork failed.");

    if (pid[1] == 0)
    {
        sem_wait(child2sem);
        WritePipe(1, 0);
        sem_post(child3sem);
        exit(0);
    }

    if ((pid[2] = fork()) < 0)
        perror("fork failed.");

    if (pid[2] == 0)
    {
        sem_wait(child3sem);
        WritePipe(2, 0);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    close(fd[1]); // 关闭写入管道

    printf("parent %d start reading.\n", getpid());

    ssize_t count;
    for (int i = 0; i < 3; i++)
    {
        if ((count = read(fd[0], buffer, sizeof(buffer))) == -1)
            perror("reading failed.");
        else
            printf("read %zd\n", count);

        printf("%s\n", buffer);
    }

    sem_close(child1sem);
    sem_close(child2sem);
    sem_close(child3sem);
    sem_unlink("/child1");
    sem_unlink("/child2");
    sem_unlink("/child3");
    sem_destroy(child1sem);
    sem_destroy(child2sem);
    sem_destroy(child3sem);

    return 0;
}
