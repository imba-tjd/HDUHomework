#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char command[BUFSIZ];
    while (1)
    {
        printf("%c>", '@');
        if (fgets(command, BUFSIZ, stdin) == NULL)
            abort();

        if (command[0] == '\n')
            continue;

        if (command[BUFSIZ - 2] != 0 && command[BUFSIZ - 2] != '\n')
        {
            perror("too long command.\n");

            while (getchar() != EOF)
                continue;

            continue;
        }

        if (strcmp("exit\n", command) == 0)
            return 0;

        command[strlen(command) - 1] = '\0';

        // system(command);
        // putchar('\n');

        pid_t pid = fork();

        if (pid < 0)
            abort();
        else if (pid == 0) // 子进程
        {
            if (execl(command, "", NULL) != 0)
            {
                printf("command not found.\n");
                exit(1);
            }

            exit(0);
        }
        else
        {
            wait(NULL); // 父进程
        }
    }
}
