/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:47:13 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/03/02 02:47:10 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_bonus.h"

void	validate_arguments(int argc, char **argv)
{
	if (argc < 2)
		error_exit("Invalid number of arguments", 1);
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
		error_exit("here_doc requires at least 6 arguments", 1);
	else if (argc < 5)
		error_exit("Invalid number of arguments", 1);
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
