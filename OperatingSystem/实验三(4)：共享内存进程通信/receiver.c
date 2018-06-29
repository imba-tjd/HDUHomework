#include <errno.h>
#include <fcntl.h> // O_CREATE
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fd = shm_open("/shared", O_RDWR, 0666);
    ftruncate(fd, 128);
    char *str = (char *)mmap(0, BUFSIZ, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_t *mutex = sem_open("/mutex1", O_RDWR);
    sem_t *sendSig = sem_open("/sendSig", O_RDWR);
    sem_t *endSig = sem_open("/endSig", O_RDWR);

    while (1)
    {
        sem_wait(sendSig);
        sem_wait(mutex);
        if (strcmp("sleep\n", str) == 0)
        {
            sem_post(mutex);
            sleep(5);
            continue;
        }

        fputs(str, stdout); // 因为多行数据仅以\n分隔而没有\0，所以可以直接输出

        if (strcmp("end\n", str) == 0)
        {
            strcpy(str, "over\n");
            sem_post(mutex);
            sem_post(endSig);

            break;
        }

        *str = '\0'; // 清除原有内容
        sem_post(mutex);
    }

    sem_close(mutex);
    close(fd);
}