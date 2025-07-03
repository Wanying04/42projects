#include <stdlib.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(char *str)
{
	int	count = 0;

	while (*str)
	{
		while (is_space(*str)) 
			str++;
		if (*str) 
			count++;
		while (*str && !is_space(*str)) 
			str++;
	}
	return count;
}

static char	*extract_word(char *str, int *pos)
{
	int		start = *pos;
	int		i = 0;
	char	*word;

	while (str[*pos] && !is_space(str[*pos]))
		(*pos)++;
	word = malloc(*pos - start + 1);
	if (!word)
		return NULL;
	while (i < *pos - start)
	{
		word[i] = str[start + i];
		i++;
	}
	word[*pos - start] = '\0';
	return word;
}

char	**ft_split(char *str)
{
	int		word_count;
	char	**result;
	int		pos = 0;
	int		word_idx = 0;

	if (!str)
		return NULL;
	word_count = count_words(str);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return NULL;
	
	while (word_idx < word_count)
	{
		while (is_space(str[pos]))
			pos++;
		result[word_idx] = extract_word(str, &pos);
		if (!result[word_idx])
		{
			while (word_idx--) 
				free(result[word_idx]);
			free(result);
			return NULL;
		}
		word_idx++;
	}
	result[word_idx] = NULL;
	return result;
}