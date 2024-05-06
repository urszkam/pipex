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
char    *create_path(char *cmd);

void    free_array(char **arr);

#endif