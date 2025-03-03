/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:12:14 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/03 16:07:38 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void handle_child_process(char *limiter, int pipefd[])
{
	char    *line;
	char    *limiter_nl;

	close(pipefd[0]);
	limiter_nl = ft_strjoin(limiter, "\n");

	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (ft_strcmp(line, limiter_nl) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter_nl);
	close(pipefd[1]);
	exit(0);
}

static void	handle_here_doc(char *limiter, int *in_fd)
{
	int		pipefd[2];
	pid_t	pid;

	create_pipe(pipefd);
	pid = fork();
	if (pid == 0)
		handle_child_process(limiter, pipefd);
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		*in_fd = pipefd[0];
	}
}

static void	exec_cmd(int input, int output, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(input, STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		close(input);
		close(output);
		execute_cmd(cmd, envp);
	}
	close(output);
}

static void	process_commands(int cmds, char **cmd, int io[], char **envp)
{
	int	i;
	int	prev_pipe;
	int	next_pipe[2];

	i = -1;
	prev_pipe = io[0];
	while (++i < cmds)
	{
		if (i < cmds - 1)
			create_pipe(next_pipe);
		if (i == cmds - 1)
			exec_cmd(prev_pipe, io[1], cmd[i], envp);
		else
		{
			exec_cmd(prev_pipe, next_pipe[1], cmd[i], envp);
			close(next_pipe[1]);
			prev_pipe = next_pipe[0];
		}
	}
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	int		io[2];
	int		cmd_count;
	char	**cmds;

	validate_arguments(argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		handle_here_doc(argv[2], &io[0]);
		cmd_count = argc - 4;
		cmds = &argv[3];
		io[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		io[0] = open(argv[1], O_RDONLY);
		cmd_count = argc - 3;
		cmds = &argv[2];
		io[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (io[0] == -1 || io[1] == -1)
		error_exit(argv[argc - 1], 1);
	process_commands(cmd_count, cmds, io, envp);
	return (0);
}
