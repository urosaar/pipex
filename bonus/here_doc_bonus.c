/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:47:13 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/10 23:40:46 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_bonus.h"

static void	heredoc_child(int pipefd[2], char *limiter)
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("pipex: warning: EOF reached\n", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	handle_here_doc(char *limiter, int *in_fd)
{
	int		pipefd[2];
	pid_t	pid;
	char	*limiter_with_nl;

	limiter_with_nl = ft_strjoin(limiter, "\n");
	 if (!limiter_with_nl)
        error_exit("here_doc", EXIT_FAILURE);
    if (pipe(pipefd) < 0) 
	{
        free(limiter_with_nl);
        error_exit("here_doc", EXIT_FAILURE);
    }
	pid = fork();
	if (pid == 0)
		heredoc_child(pipefd, limiter_with_nl);
	else
	{
		free(limiter_with_nl);
		close(pipefd[1]);
		*in_fd = pipefd[0];
		waitpid(pid, NULL, 0);
	}
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		error_exit("pipe", EXIT_FAILURE);
}
void	exit_close(int fd, int fd2)
{
	if (fd != -1)
		close(fd);
	if (fd2 != -1)
		close(fd2);
	error_exit("file error", EXIT_FAILURE);
}
