/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:22 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/02/27 14:59:40 by oukhanfa         ###   ########.fr       */
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
char	*get_cmd_path(char *cmd);
void	error_exit(char *msg, int code);
void	ft_free_split(char **arr);
void	create_pipe(int pipefd[2]);
void	validate_arguments(int argc, char **argv);
void	handle_errors(char *cmd);

#endif
