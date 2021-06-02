/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdan <jjourdan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:38:50 by jjourdan          #+#    #+#             */
/*   Updated: 2021/06/02 13:18:21 by jjourdan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pip[2];

	errno = SUCCESS;
	if (argc != 5)
	{
		errno = EINVAL;
		exit(kemaexit("Please provide file1 cmd1 cmd2 file2"));
	}
	if (pipe(pip) != 0)
		exit(kemaexit("Error during pipe creation"));
	pid = fork();
	if (pid < 0)
	{
		errno = ESPIPE;
		exit(kemaexit("Fork failed"));
	}
	if (pid == 0)
		ft_pipex_child(pip, argv, envp);
	else
		ft_pipex_parent(pip, argv, envp);
}

void	ft_pipex_child(int *pip, char **argv, char **envp)
{
	int	fd;

	close(pip[0]);
	dup2(pip[1], 1);
	close(pip[1]);
	fd = open(argv[1], O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		errno = EISDIR;
		exit(kemaexit("file1"));
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		errno = ENOENT;
		exit(kemaexit("file1"));
	}
	dup2(fd, 0);
	ft_pipex_exec_cmd(argv[2], envp);
	errno = EAGAIN;
	exit(kemaexit("cmd1"));
}

void	ft_pipex_parent(int *pip, char **argv, char **envp)
{
	int	fd;
	int	*status;

	status = NULL;
	wait(status);
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
	fd = open (argv[4], O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		errno = EISDIR;
		exit(kemaexit("file2"));
	}
	fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT);
	if (fd < 0)
	{
		errno = ENOENT;
		exit(kemaexit("file2"));
	}
	dup2(fd, 1);
	ft_pipex_exec_cmd(argv[3], envp);
	errno = EAGAIN;
	exit(kemaexit("cmd2"));
}

void	ft_pipex_exec_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	char	*buf;
	ssize_t	i;

	cmd = ft_split(argv, ' ');
	i = -1;
	while (ft_strncmp(envp[++i], "PWD=", 4))
		;
	path = ft_strjoin(ft_strdup(&envp[i][4]), "/");
	buf = ft_strdup(cmd[0]);
	ft_pipex_try_path(cmd, path, buf, envp);
	ft_pipex_try_path(cmd, "/bin/", buf, envp);
	ft_pipex_try_path(cmd, "/usr/bin/", buf, envp);
	ft_pipex_try_path(cmd, "/usr/local/bin/", buf, envp);
	ft_pipex_try_path(cmd, "/sbin/", buf, envp);
	ft_pipex_try_path(cmd, "/usr/sbin/", buf, envp);
	errno = ENOENT;
	exit(kemaexit(buf));
}

void	ft_pipex_try_path(char **cmd, char *path, char *buf, char **envp)
{
	kemafree(cmd[0]);
	cmd[0] = ft_strjoin(path, buf);
	execve(cmd[0], &cmd[0], envp);
}
