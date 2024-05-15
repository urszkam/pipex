#include "pipex.h"

void    create_pipes(int *fd, int cmd_len)
{
    int i;

    i = 0;
    while (i < cmd_len)
    {
        if (pipe(fd + i * 2) < 0)
        {
            perror("piping");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void    pipex(char **cmd, int cmd_len)
{
    int     i;
    pid_t   pid;
    int     fd[2 * cmd_len];

    int output_fd = open(cmd[cmd_len - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    i = 0;
    create_pipes(fd, cmd_len);
    while (i / 2 < cmd_len - 1)
    {
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            open_fds(fd, i, cmd_len, output_fd);
            close_fds(fd, cmd_len);
            exec_cmd(cmd[i / 2], i);
        }
        i += 2;
    }
    fprintf(stderr, "exit");
    close_fds(fd, cmd_len);
    close(output_fd);
    i = -1;
    while (++i < cmd_len)
        wait(NULL);
}

int main(int argc, char **argv)
{
    if (argc >= 5)
    {
        argv++;
        pipex(argv, argc - 1);
    }
    return (0);
}
