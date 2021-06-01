/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdan <jjourdan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:28:31 by jjourdan          #+#    #+#             */
/*   Updated: 2021/06/01 15:47:28 by jjourdan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libkema/includes/libkema.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

//	*	errors handlers

# define SUCCESS		0
# define STR_SUCCESS	"Operation success!"
# define FAILURE		-1
# define STR_FAILURE	"Operation failure!"
# define ENOARG			-2
# define STR_ENOARG		"Not enough arguments!"

//	*	structs declarations

//	*	functions prototypes

//	*	main.c
int		main(int argc, char **argv, char **envp);
void	ft_pipex_exec_cmd(char *argv, char **envp);
void	ft_pipex_child(int *pip, char **argv, char **envp);
void	ft_pipex_parent(int *pip, char **argv, char **envp);
void	ft_pipex_try_path(char **cmd, char *path, char *buf, char **envp);

#endif
