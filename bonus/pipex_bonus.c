/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:12:14 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/08 05:35:04 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_child(int input_fd, int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_cmd(cmd, envp);
	}
}

static void	handle_middle_commands(int *input_fd, char **cmds,
			int count, char **envp)
{
	int		pipefd[2];
	int		i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe", EXIT_FAILURE);
		execute_child(*input_fd, pipefd, cmds[i], envp);
		close(pipefd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = pipefd[0];
		i++;
	}
}

static void	handle_last_command(int input_fd, int output_fd,
	char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		execute_cmd(cmd, envp);
	}
}

static void	process_pipeline(int fds[2], char **cmds, int count, char **envp)
{
	int	input_fd;
	int	output_fd;

	input_fd = fds[0];
	output_fd = fds[1];
	handle_middle_commands(&input_fd, cmds, count, envp);
	handle_last_command(input_fd, output_fd, cmds[count - 1], envp);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	int		input_fd;
	int		output_fd;
	char	**cmds;
	int		cmd_count;
	int		fds[2];

	validate_arguments(argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		handle_here_doc(argv[2], &input_fd);
		cmd_count = argc - 4;
		cmds = &argv[3];
		output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		input_fd = open(argv[1], O_RDONLY);
		cmd_count = argc - 3;
		cmds = &argv[2];
		output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (input_fd == -1 || output_fd == -1)
		error_exit("file error", EXIT_FAILURE);
	return (fds[0] = input_fd, fds[1] = output_fd,
		process_pipeline(fds, cmds, cmd_count, envp), 0);
}
