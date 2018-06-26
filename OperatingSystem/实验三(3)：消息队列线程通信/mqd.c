#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *sender(void *args);
void *receiver(void *args);
pthread_t sender_t, receiver_t;

int main(void)
{
    printf("progress start\n");
    if (pthread_create(&sender_t, NULL, sender, NULL) != 0)
        abort();
    if (pthread_create(&receiver_t, NULL, receiver, NULL) != 0)
        abort();
    // printf("thread start.\n");

    pthread_join(sender_t, NULL);
    pthread_join(receiver_t, NULL);

    return 0;
}

void *sender(void *args)
{
    char input[BUFSIZ] = {0};
    char exitmessage[BUFSIZ] = {0};

    mqd_t mymq = mq_open("/mymq", O_WRONLY | O_CREAT, 0666, NULL);
    mqd_t exitmq = mq_open("/mymq2", O_RDONLY | O_CREAT, 0666, NULL);

    // printf("%d\n", mymq);
    // printf("%d\n", exitmq);

    if (mymq < 0 || exitmq < 0)
        abort();

    printf("sender created.\n");
    while (1)
    {
        printf("%c>", 64);
        if (fgets(input, BUFSIZ, stdin) == NULL)
            abort();

        if (input[0] == '\n')
            continue;

        if (input[BUFSIZ - 2] != 0 && input[BUFSIZ - 2] != '\n')
        {
            perror("too long input.\n");

            char c = getchar();
            while (c != EOF && c != '\n')
                c = getchar();

            continue;
        }

        // input[strlen(input) - 1] = '\0'; // 去掉\n

        if (strcmp("exit\n", input) == 0)
        {
            mq_send(mymq, "end\n", sizeof("end\n"), 0);
            pthread_join(receiver_t, NULL);
            mq_receive(exitmq, exitmessage, sizeof(exitmessage), NULL);
            fputs(exitmessage, stdout);

            mq_close(mymq);
            mq_close(exitmq);
            mq_unlink("mymq");
            mq_unlink("exitmq");
            pthread_exit(NULL);
        }

        if (mq_send(mymq, input, sizeof(input), 0) == 0)
        {
            // printf("send.\n");
            usleep(1);
        }
        else
            printf("send failed.\n");
    }
}

void *receiver(void *args)
{
    // sleep(10);
    char output[BUFSIZ] = {0};
    mqd_t mymq = mq_open("/mymq", O_RDONLY);
    mqd_t exitmq = mq_open("/mymq2", O_WRONLY);

    // printf("%d\n", mymq);
    // printf("%d\n", exitmq);

    if (mymq < 0 || exitmq < 0)
        abort();

    // printf("receiver created.\n");
    while (1)
    {
        mq_receive(mymq, output, sizeof(output), NULL);
        //printf("received");

        if (strcmp("end\n", output) == 0)
        {
            mq_send(exitmq, "over\n", sizeof("over\n"), 0);

            mq_close(mymq);
            mq_close(exitmq);
            pthread_exit(NULL);
        }
        else if (strcmp("sleep\n", output) == 0)
            sleep(5);
        else
            fputs(output, stdout);
    }
}
