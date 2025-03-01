/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:05:21 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/02/25 18:57:27 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*search_in_dirs(char **dirs, char *cmd)
{
	int		i;
	char	*dir;
	char	*bin;

	i = -1;
	while (dirs && dirs[++i])
	{
		dir = ft_strjoin(dirs[i], "/");
		bin = ft_strjoin(dir, cmd);
		free(dir);
		if (access(bin, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (bin);
		}
		free(bin);
	}
	ft_free_split(dirs);
	return (NULL);
}

char	*get_cmd_path(char *cmd)
{
	char	*path;
	char	**dirs;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	return (search_in_dirs(dirs, cmd));
}

void	execute_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		(ft_free_split(args), handle_errors(cmd));
	path = get_cmd_path(args[0]);
	if (!path)
		handle_errors(args[0]);
	if (execve(path, args, env) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(args[0]);
		free(path);
		ft_free_split(args);
		exit(126);
	}
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		error_exit("pipe", EXIT_FAILURE);
}
