/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:12:14 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/13 04:30:24 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_child(int input_fd, int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid ;

	pid = fork();
	if (pid < 0)
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		close(pipefd[0]);
		close(pipefd[1]);
		error_exit("fork", EXIT_FAILURE);
	}
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

static void	handle_middle_commands(int *input_fd,
	t_commands_info *cmds_info, char **envp)
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (i < cmds_info->count - 1)
	{
		if (pipe(pipefd) < 0)
		{
			if (*input_fd != STDIN_FILENO)
				close(*input_fd);
			error_exit("pipe", EXIT_FAILURE);
		}
		execute_child(*input_fd, pipefd, cmds_info->cmds[i], envp);
		close(pipefd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = pipefd[0];
		i++;
	}
}

static void	handle_last_command(int input_fd, char *cmd,
	char **envp, t_output_info *output_info)
{
	pid_t	pid;
	int		output_fd;

	pid = fork();
	if (pid < 0)
	{
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		error_exit("fork", EXIT_FAILURE);
	}
	if (pid == 0)
	{
		output_fd = setup_output_redirection(output_info);
		redirect_and_execute(input_fd, output_fd, cmd, envp);
	}
}

static void	process_pipeline(int input_fd, t_commands_info *cmds_info,
	char **envp, t_output_info *output_info)
{
	handle_middle_commands(&input_fd, cmds_info, envp);
	handle_last_command(input_fd, cmds_info->cmds[cmds_info->count - 1],
		envp, output_info);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	while (wait(NULL) > 0)
		;
}

int	main(int argc, char **argv, char **envp)
{
	int				input_fd;
	t_commands_info	cmds_info;
	t_output_info	output_info;
	int				is_heredoc;

	validate_arguments(argc, argv);
	is_heredoc = (ft_strcmp(argv[1], "here_doc") == 0);
	if (is_heredoc)
	{
		handle_here_doc(argv[2], &input_fd);
		cmds_info.cmds = &argv[3];
		cmds_info.count = argc - 4;
	}
	else
	{
		input_fd = open(argv[1], O_RDONLY);
		if (input_fd < 0)
			error_exit(argv[1], EXIT_FAILURE);
		cmds_info.cmds = &argv[2];
		cmds_info.count = argc - 3;
	}
	output_info.filename = argv[argc - 1];
	output_info.is_heredoc = is_heredoc;
	process_pipeline(input_fd, &cmds_info, envp, &output_info);
	return (0);
}
