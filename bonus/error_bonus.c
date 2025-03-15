/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:23:48 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/13 04:32:30 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_errors(char *cmd, char **args)
{
	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex: command not found\n", 2);
		exit(126);
	}
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(cmd, 2);
		write(2, "\n", 1);
		exit(126);
	}
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	if (args)
		ft_free_split(args);
	exit(127);
}

void	validate_arguments(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		exit(1);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
	{
		ft_putstr_fd("here_doc requires at least 6 arguments\n", 2);
		exit(1);
	}
	else if (argc < 5)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		exit(1);
	}
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	error_exit(char *msg, int code)
{
	perror(msg);
	exit(code);
}

void	redirect_and_execute(int input_fd, int output_fd,
	char *cmd, char **envp)
{
	dup2(input_fd, STDIN_FILENO);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	execute_cmd(cmd, envp);
}
