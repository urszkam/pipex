#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

char    **ft_split(char const *s, char c);
char	*ft_strndup(char const *str, int n);
char    **create_arr(char *str, char *str2);
char    **create_cmd_vector(char *cmd, int j);
char    *create_path(char *cmd);

void    free_array(char **arr);
void    exec_cmd(char *cmd, int j);
void    close_fds(int *fd, int cmd_len);
void    open_fds(int *fd, int j, int cmd_len, int output_fd);

#endif