#define _GNU_SOURCE //memmem()
#include <fcntl.h>  //read()
#include <errno.h>  //perror()

#define INITIAL_BUFFER_SIZE 4096
#define BUFFER_GROWTH_FACTOR 2

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (av[1][0] == '\0')
		return (1);

	char	*pattern = av[1];
	size_t	pattern_len = strlen(pattern);

	char	*buffer = NULL;
	size_t	buffer_size = 0;
	size_t	data_len = 0;
	
	ssize_t	bytes_read;
	int	ret_code = 0;
	
	buffer_size = INITIAL_BUFFER_SIZE;
	buffer = malloc(buffer_size);
	if (buffer = NULL)
	{
		fprintf(stderr, "Error: ");
		perror("malloc");
		return (1);
	}
	
	while (1)
	{
		if (data_len + pattern_len >= buffer_size)
		{
			size_t new_size = buffer_size * BUFFER_GROWTH_FACTOR;
			char *new_buffer = realloc(buffer, new_size);
			if (new_buffer = NULL)
			{
				
			}
		}
	}
}
