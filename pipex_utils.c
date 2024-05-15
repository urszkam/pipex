#include "pipex.h"

void    close_fds(int *fd, int cmd_len) 
{
    int i;

    i = 0;
    while (i < 2 * cmd_len)
    {
        if (close(fd[i]) < 0)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

char    **create_cmd_vector(char *cmd, int j)
{
    char    **cmdv;

    if (j == 0)
        cmdv = create_arr("<", cmd);
    else
        cmdv = ft_split(cmd, ' ');
    return (cmdv);
}

void    open_fds(int *fd, int j, int cmd_len, int output_fd)
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
    if (j + 4 == 2 * cmd_len)
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
    char    **cmdv;
    char    *path;

    cmdv = create_cmd_vector(cmd, j); 
    if (j == 0)
        path = "/usr/bin/cat";
    else 
        path = create_path(cmdv[0]);
    fprintf(stderr, "%s, %s, %d\n", path, cmdv[0], j);
    if (execve(path, cmdv, NULL) < 0)
    {
        free(path);
        free_array(cmdv);
        perror("command execution");
        exit(EXIT_FAILURE);
    }
    free_array(cmdv);
    free(path);
}
