/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:23:48 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/13 04:16:06 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	error_exit(char *msg, int code)
{
	perror(msg);
	exit(code);
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
