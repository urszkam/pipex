#include "pipex.h"

int ft_strcmp(char **s1, char **s2)
{
    while (*s1 && *s2)
    {
        s1++;
        s2++;
    }
    return (!s1 && !s2);
}

void    free_array(char **arr)
{
    int i;

    i = 0;
    if (arr)
    {
        while (arr[i]) {
            free(arr[i]);
            i++;
        }
        free(arr);
        arr = NULL;
    }
}

char	*ft_strndup(char const *str, int n)
{
	char	*new;
	int		i;

	new = (char *) malloc((n + 1) * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

char    **create_arr(char *str, char *str2)
{
    char    **arr;

    arr = (char **) malloc(3 * sizeof(char *));
    if (!arr)
        return (0);
    arr[0] = ft_strndup(str, strlen(str));
    arr[1] = ft_strndup(str2, strlen(str2));
    arr[2] = NULL;
    return (arr);
}

char    *create_path(char *cmd)
{
    char    *path;
    char    *dir;
    int     i;
    int     j;

    dir = "/usr/bin/";
    path = malloc(strlen(cmd) + strlen(dir) + 1);
    if (!path)
        return (0);
    i = 0;
    while (dir[i])
    {
        path[i] = dir[i];
        i++;
    }
    j = 0;
    while (cmd[j])
    {
        path[i + j] = cmd[j];
        j++;
    }
    path[i + j] = '\0';
    return (path);
}
