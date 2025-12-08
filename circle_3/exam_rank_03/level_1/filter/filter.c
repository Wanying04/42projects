#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void *memmem(const void *haystack, size_t haystacklen,
					const void *needle, size_t needlelen);

int	process_buffer(char *buffer, ssize_t bytes_read, char *target, ssize_t target_len, char *stars)
{
	char	*pos = buffer;
	ssize_t	remaining = bytes_read;

	while (remaining >= target_len)
	{
		char	*found = memmem(pos, remaining, target, target_len);
		if (!found)
			break ;
		
		size_t	before_len = found - pos;
		if (before_len > 0)
		{
			ssize_t written = write(1, pos, before_len);
			if (written < 0 || (size_t)written != before_len)
				return (-1);
		}
		if (write(1, stars, target_len) != target_len)
			return (-1);
		pos = found + target_len;
		remaining = bytes_read - (pos - buffer);
	}
	if (remaining > 0)
	{
		if(write(1, pos, remaining) != remaining)
			return (-1);
	}
	return (0);
}

char	*create_stars_string(size_t len)
{
	char	*stars = malloc(len + 1);
	if (!stars)
		return (NULL);
	
	size_t	i = 0;

	while (i < len)
	{
		stars[i] = '*';
		i++;
	}
	stars[len] = '\0';
	return (stars);
}

int	filter_input(char *target, ssize_t target_len)
{
	char	*stars = create_stars_string(target_len);

	if (!stars)
	{
		fprintf(stderr, "Error: ");
		perror("malloc");
		return (1);
	}

	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		result = 0;

	while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		if (process_buffer(buffer, bytes_read, target, target_len, stars) < 0)
		{
			fprintf(stderr, "Error: ");
			perror("write");
			result = 1;
			break ;
		}
	}
	if (bytes_read < 0)
	{
		fprintf(stderr, "Error: ");
		perror("read");
		result = 1;
	}
	free(stars);
	return (result);
}

int	handle_empty_target(void)
{
	char	buf[BUFFER_SIZE];
	ssize_t	n;

	while ((n = read(0, buf, BUFFER_SIZE)) > 0)
	{
		if (write(1, buf, n) != n)
		{
			fprintf(stderr, "Error: ");
			perror("write");
			return (1);
		}
	}
	if (n < 0)
	{
		fprintf(stderr, "Error: ");
		perror("read");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return (1);
	}

	char	*target = argv[1];
	ssize_t	target_len = strlen(target);

	if (target_len == 0)
		return (handle_empty_target());
	return (filter_input(target, target_len));
}
