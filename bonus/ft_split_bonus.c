/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhanfa <oukhanfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:07:09 by oukhanfa          #+#    #+#             */
/*   Updated: 2025/02/23 17:40:48 by oukhanfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

static int	word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*word_dup(const char *s, int len)
{
	char	*word;
	int		i;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static int	fill_words(char **arr, const char *s, char c)
{
	int			i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			arr[i] = word_dup(start, s - start);
			if (!arr[i++])
			{
				while (i-- > 1)
					free(arr[i - 1]);
				return (0);
			}
		}
	}
	arr[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	arr = (char **)malloc((wc + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_words(arr, s, c))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
