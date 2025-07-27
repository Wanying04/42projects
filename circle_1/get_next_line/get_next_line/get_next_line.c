/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:07:01 by wtang             #+#    #+#             */
/*   Updated: 2025/05/21 16:18:07 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_init(char **buffer, char **line, char **storage)
{
	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (0);
	if (*storage)
		*line = ft_strdup(*storage);
	else
		*line = ft_strdup("");
	free (*storage);
	*storage = NULL;
	if (!*line)
	{
		free(*buffer);
		return (0);
	}
	return (1);
}

int	gnl_read_loop(int fd, char **line, char *buffer, int *bytes_read)
{
	char	*temp;

	while (!ft_strchr(*line, '\n') && *bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read < 0)
			return (0);
		buffer[*bytes_read] = '\0';
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
		if (!*line)
			return (0);
	}
	return (1);
}

char	*gnl_process_line(char **line, char **storage)
{
	char	*newline_pos;
	char	*result;
	size_t	len;

	newline_pos = ft_strchr(*line, '\n');
	if (newline_pos)
	{
		len = newline_pos - *line + 1;
		*storage = ft_strdup(newline_pos + 1);
		result = ft_substr(*line, 0, len);
		free(*line);
		if (!result)
		{
			free(*storage);
			*storage = NULL;
		}
		return (result);
	}
	return (*line);
}

char	*gnl_cleanup(char *buffer, char **storage, char *line)
{
	if (buffer)
		free(buffer);
	if (line)
		free(line);
	if (storage && *storage)
	{
		free(*storage);
		*storage = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*buffer;
	char		*line;
	char		*newline_pos;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (gnl_cleanup(NULL, &storage, NULL));
	if (!gnl_init(&buffer, &line, &storage))
		return (NULL);
	newline_pos = ft_strchr(line, '\n');
	bytes_read = 1;
	if (!newline_pos)
	{
		if (!gnl_read_loop(fd, &line, buffer, &bytes_read))
			return (gnl_cleanup(buffer, NULL, line));
	}
	free(buffer);
	if (bytes_read == 0 && !*line)
		return (gnl_cleanup(NULL, NULL, line));
	return (gnl_process_line(&line, &storage));
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		write(2, "Usage: ./a.out <file_path>\n", 26);
// 		return (1);
// 	}
// 	int fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		write(2, "Error: Could not open file\n", 27);
// 		return (1);
// 	}
//     char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
