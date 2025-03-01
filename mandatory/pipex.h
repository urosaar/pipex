/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:06 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/02/27 14:59:33 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

void	execute_cmd(char *cmd, char **envp);
char	*get_cmd_path(char *cmd);
void	error_exit(char *msg, int code);
void	ft_free_split(char **arr);
void	handle_errors(char *cmd);

#endif
