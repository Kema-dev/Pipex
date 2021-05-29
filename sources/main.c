/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdan <jjourdan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:38:50 by jjourdan          #+#    #+#             */
/*   Updated: 2021/05/29 14:10:45 by jjourdan         ###   ########lyon.fr   */
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
	{
		errno = EPIPE;
		exit(kemaexit("Errore during pipe creation"));
	}
	pid = fork();
	if (pid < 0)
	{
		errno = ESPIPE;
		exit(kemaexit("Fork failed"));
	}
	if (pid == 0)
		ft_pipex_child(pid, pip, argv, envp);
	else
		ft_pipex_parent(pid, pip, argv, envp);
	exit(kemaexit(""));
}

void	ft_pipex_exec(pid_t pid, int *pip, char **argv, char **envp)
{
	char	**cmd1;
	char	*path;
	ssize_t	i;

	(void)pid;
	(void)pip;
	cmd1 = ft_split(argv[2], ' ');
	i = -1;
	while (ft_strncmp(envp[++i], "PWD=", 4))
		;
	path = ft_strjoin(ft_strdup(&envp[i][4]), "/");
	if (execve(ft_strjoin("/bin/", cmd1[0]), &cmd1[1], envp))
	{
		if (execve(ft_strjoin("/sbin/", cmd1[0]), &cmd1[1], envp))
		{
			if (execve(ft_strjoin(path, cmd1[0]), &cmd1[1], envp))
			{
				errno = EINVAL;
				exit(kemaexit("cmd1"));
			}
		}
	}
}
