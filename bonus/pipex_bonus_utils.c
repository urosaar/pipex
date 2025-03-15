/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:05:21 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/13 21:29:53 by oukhanfa         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv(char **env, char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	if (name == NULL || env == NULL)
		return (NULL);
	while (name[len] != '\0')
		len++;
	if (len > 0 && name[len - 1] == '=')
		len--;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
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
	path = ft_getenv(env, "PATH=");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, cmd));
}

void	execute_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (args[0][0] == '.' && args[0][1] == '/')
		(ft_free_split(args), exit(0));
	if (!args || !args[0])
	{
		if (args)
			ft_free_split(args);
		handle_errors("", NULL);
	}
	path = get_cmd_path(args[0], env);
	if (!path)
		handle_errors(args[0], args);
	if (execve(path, args, env) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(args[0]);
		free(path);
		ft_free_split(args);
		exit(126);
	}
}
