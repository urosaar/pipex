/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:22 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/13 04:37:40 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft_bonus.h"

typedef struct s_commands_info
{
	char	**cmds;
	int		count;
}	t_commands_info;

typedef struct s_output_info
{
	char	*filename;
	int		is_heredoc;
}	t_output_info;

void	execute_cmd(char *cmd, char **envp);
char	*get_cmd_path(char *cmd, char **env);
void	error_exit(char *msg, int code);
void	ft_free_split(char **arr);
void	create_pipe(int pipefd[2]);
void	validate_arguments(int argc, char **argv);
char	*get_next_line(int fd);
void	handle_errors(char *cmd, char **args);
void	handle_here_doc(char *limiter, int *in_fd);
int		setup_output_redirection(t_output_info *output_info);
void	redirect_and_execute(int input_fd, int output_fd,
			char *cmd, char **envp);

#endif
