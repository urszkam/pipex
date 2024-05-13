#include "pipex.h"

void close_fds(int *fd, int cmd_len) 
{
    int i;

    i = 0;
    while (i < 2 * cmd_len) {
        if (close(fd[i]) < 0)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void create_pipes(int *fd, int cmd_len)
{
    int i;

    i = 0;
    while (i < cmd_len) {
        if (pipe(fd + i * 2) < 0) {
            perror("piping");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

char **create_cmd_vector(char *cmd, int j)
{
    char **cmdv;

    if (j == 0)
        cmdv = create_arr("<", cmd);
    else
        cmdv = ft_split(cmd, ' ');
    return (cmdv);
}

void open_fds(int *fd, int j, int cmd_len, int output_fd)
{
    if (j + 4 < 2 * cmd_len) 
    {
        if (dup2(fd[j + 1], 1) < 0) 
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (j > 0) 
    {
        if (dup2(fd[j - 2], 0) < 0)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    if (j + 4 == 2 * cmd_len )
    {
        if (dup2(output_fd, 1) < 0) 
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
}

void    exec_cmd(char *cmd, int j) 
{
    char **cmdv;
    char *path;

    cmdv = create_cmd_vector(cmd, j); 
    if (j == 0)
        path = "/usr/bin/cat";
    else 
        path = create_path(cmdv[0]);
    fprintf(stderr, "%s, %s, %d\n", path, cmdv[0], j);
    if (execve(path, cmdv, NULL) < 0) 
    {
        free_array(cmdv);
        free(path);
        perror(cmdv[0]);
        exit(EXIT_FAILURE);
    }
    free_array(cmdv);
    free(path);
}

void pipex(char **cmd, int cmd_len) {
    int i;
    pid_t pid;
    int fd[2 * cmd_len];

    int output_fd = open(cmd[cmd_len - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
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