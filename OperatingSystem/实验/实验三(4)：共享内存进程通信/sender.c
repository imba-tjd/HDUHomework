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
    int fd = shm_open("/shared", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 128); // 如果不执行ftruncate函数的话,会报Bus error的错误
    char *str = (char *)mmap(0, BUFSIZ, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_t *mutex = sem_open("/mutex1", O_CREAT | O_RDWR, 0666, 1);
    sem_t *sendSig = sem_open("/sendSig", O_CREAT | O_RDWR, 0666, 0);
    sem_t *endSig = sem_open("/endSig", O_CREAT | O_RDWR, 0666, 0);

    char buffer[128] = {0};
    while (1)
    {
        printf("%c>", 64);
        if (fgets(buffer, BUFSIZ, stdin) == NULL)
            abort();

        if (buffer[0] == '\n')
            continue;

        // buffer[strlen(buffer) - 1] = '\0'; // 去掉\n

        sem_wait(mutex);
        // strcpy(str, buffer); // 不能用memcpy
        strcat(str, buffer);
        sem_post(mutex);
        sem_post(sendSig);

        if (strcmp("end\n", buffer) == 0)
        {
            sem_wait(endSig);
            sem_wait(mutex);
            fputs(str, stdout);
            sem_post(mutex);
            break;
        }
    }
    sem_close(mutex);
    sem_unlink("/mutex1");
    sem_destroy(mutex);
    close(fd);
    shm_unlink("/shared");
}
