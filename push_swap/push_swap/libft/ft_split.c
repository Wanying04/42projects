/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:54:02 by wtang             #+#    #+#             */
/*   Updated: 2024/12/20 15:33:35 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_get_next_word(char const *s, char c)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_add(char const **s, char c, char **result, int *i)
{
	while (**s == c)
		(*s)++;
	result[*i] = ft_get_next_word(*s, c);
	if (!result[*i])
	{
		while (*i > 0)
			free(result[--*i]);
		free(result);
		return ;
	}
	while (**s && **s != c)
		(*s)++;
	(*i)++;
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		i;
	char	**result;

	word_count = 0;
	i = 0;
	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
		ft_add(&s, c, result, &i);
	result[i] = NULL;
	return (result);
}
