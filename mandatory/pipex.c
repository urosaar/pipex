/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:06:56 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/02/25 17:49:14 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validate_arguments(int argc)
{
	if (argc != 5)
		ft_putstr_fd("pipex: Invalid number of arguments\n",2);
}

static void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
		error_exit("pipe", EXIT_FAILURE);
}

static	pid_t	launch_first_child(char *infile_name, int pipefd[2],
			char *cmd, char **envp)
{
	pid_t	pid;
	int		infile;

	pid = fork();
	if (pid < 0)
		error_exit("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		infile = open(infile_name, O_RDONLY);
		if (infile < 0)
			error_exit(infile_name, EXIT_FAILURE);
		close(pipefd[0]);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execute_cmd(cmd, envp);
	}
	return (pid);
}

static pid_t	launch_second_child(char *outfile_name, int pipefd[2],
			char *cmd, char **envp)
{
	pid_t	pid;
	int		outfile;

	pid = fork();
	if (pid < 0)
		error_exit("fork", EXIT_FAILURE);
	if (pid == 0)
	{
		outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			error_exit(outfile_name, EXIT_FAILURE);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute_cmd(cmd, envp);
	}
	return (pid);
}
void s()
{
	system("leaks pipex");
}
int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	// atexit(s);
	validate_arguments(argc);
	create_pipe(pipefd);
	pid1 = launch_first_child(argv[1], pipefd, argv[2], envp);
	pid2 = launch_second_child(argv[4], pipefd, argv[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
