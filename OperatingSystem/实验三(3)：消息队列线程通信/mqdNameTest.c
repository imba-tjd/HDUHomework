#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("%d\n", mq_open("/mymq", O_WRONLY | O_CREAT, 0666, NULL)); // 成功
    printf("%d\n", mq_open("/mymq", O_RDONLY)); // 成功

    printf("%d\n", mq_open("mymq", O_WRONLY | O_CREAT, 0666, NULL)); // 失败
    printf("%d\n", mq_open("mymq", O_RDONLY)); // 失败

    printf("%d\n", mq_open("/exitmq", O_WRONLY | O_CREAT, 0666, NULL)); // 成功
    printf("%d\n", mq_open("/exitmq", O_RDONLY)); // 失败

    printf("%d\n", mq_open("/test", O_WRONLY | O_CREAT, 0666, NULL)); // 成功
    printf("%d\n", mq_open("/test", O_RDONLY)); // 失败

    printf("%d\n", mq_open("/asdf", O_WRONLY | O_CREAT, 0666, NULL)); // 成功
    printf("%d\n", mq_open("/asdf", O_RDONLY)); // 成功
}
