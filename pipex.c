#include "pipex.h"

static void	wait_for_children(int cmd_len)
{
	int	i;

	i = 0;
	while (i < cmd_len)
	{
		wait(NULL);
		i++;
	}
}

static void	fork_and_exec(char **cmd, int cmd_len, int *fd, int output_fd)
{
	int	i;
	int	pid;

	i = 0;
	while (i < cmd_len * 2)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error while forking");
			free(fd);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			open_fds(fd, i, cmd_len, output_fd);
			close_fds(fd, cmd_len);
			exec_cmd(cmd[i / 2], i);
		}
		i += 2;
	}
}

static void	create_pipes(int *fd, int cmd_len)
{
	int	i;

	i = 0;
	while (i < cmd_len)
	{
		if (pipe(fd + i * 2) == -1)
		{
			perror("pipe");
			free(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	pipex(char **cmd, int cmd_len)
{
	int	*fd;
	int	output_fd;

	fd = (int *) malloc(sizeof(int) * 2 * (--cmd_len));
	if (!fd)
	{
		perror("Malloc Error");
		exit(EXIT_FAILURE);
	}
	output_fd = open(cmd[cmd_len], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd < 0)
	{
		perror("Error while opening the file");
		free(fd);
		exit(EXIT_FAILURE);
	}
	create_pipes(fd, cmd_len);
	fork_and_exec(cmd, cmd_len, fd, output_fd);
	close_fds(fd, cmd_len);
	close(output_fd);
	wait_for_children(cmd_len);
	free(fd);
}

int	main(int argc, char **argv)
{
	if (argc >= 5)
	{
		argv++;
		pipex(argv, argc - 1);
	}
	return (0);
}
