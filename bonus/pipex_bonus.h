/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:22 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/10 21:51:55 by oukhanfa         ###   ########.fr       */
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

void	execute_cmd(char *cmd, char **envp);
char	*get_cmd_path(char *cmd , char **env);
void	error_exit(char *msg, int code);
void	ft_free_split(char **arr);
void	create_pipe(int pipefd[2]);
void	validate_arguments(int argc, char **argv);
char	*get_next_line(int fd);
void	handle_errors(char *cmd);
void	handle_here_doc(char *limiter, int *in_fd);
void	exit_close(int fd, int fd2);

#endif
