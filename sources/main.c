/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdan <jjourdan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:38:50 by jjourdan          #+#    #+#             */
/*   Updated: 2021/05/29 11:50:35 by jjourdan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	*bin1;
	char	*path;
	ssize_t	i;

	errno = SUCCESS;
	if (argc < 5)
	{
		errno = EINVAL;
		exit(kemaexit("Please provide file1 cmd1 cmd2 file2"));
	}
	cmd1 = ft_split(argv[2], ' ');
	i = -1;
	while (ft_strncmp(envp[++i], "PWD=", 4))
		;
	path = ft_strjoin(ft_strdup(&envp[i][4]), "/");
	if (execve(ft_strjoin("/bin/", bin1 = ft_strdup(cmd1[0])), &cmd1[1], envp))
	{
		if (execve(ft_strjoin("/sbin/", bin1 = ft_strdup(cmd1[0])), &cmd1[1], envp))
		{
			if (execve(ft_strjoin(path, bin1 = ft_strdup(cmd1[0])), &cmd1[1], envp))
			{
				errno = EINVAL;
				exit(kemaexit("Please provide file1 cmd1 cmd2 file2"));
			}
		}
	}
	exit(kemaexit(""));
}
