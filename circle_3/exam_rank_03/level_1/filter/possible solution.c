/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible solution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:49:35 by albarrei          #+#    #+#             */
/*   Updated: 2025/11/06 19:10:35 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

void	*memmem(const void *haystack, size_t haystacklen,
			const void *needle, size_t needlelen);

void	ft_filter_block(char *buf, ssize_t n, char *pattern, ssize_t patlen)
{
	char	*found;
	ssize_t	i;

	found = memmem(buf, n, pattern, patlen);
	while (found)
	{
		i = 0;
		while (i < patlen)
		{
			found[i] = '*';
			i++;
		}
		n = n - ((found + patlen) - buf);
		buf = found + patlen;
		found = memmem(buf, n, pattern, patlen);
	}
}

int	main(int argc, char **argv)
{
	char	buf[BUFSIZE];
	char	*pattern;
	ssize_t	n;
	ssize_t	keep;
	ssize_t	patlen;

	if (argc != 2)
		return (1);
	keep = 0;
	pattern = argv[1];
	patlen = strlen(argv[1]);
	n = read(0, buf + keep, BUFSIZE - keep);
	while (n > 0)
	{
		n += keep;
		ft_filter_block(buf, n, pattern, patlen);
		if (patlen > 1 && n >= patlen - 1)
		{
			write(1, buf, n - (patlen - 1));
			memmove(buf, buf + n - (patlen - 1), patlen - 1);
			keep = patlen - 1;
		}
		else
		{
			write(1, buf, n);
			keep = 0;
		}
		n = read(0, buf + keep, BUFSIZE - keep);
	}
	// printf("Saliendo del bucle, n = %li\n", n);
	if (keep > 0)
		write(1, buf, keep);
	return (0);
}

/* #include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void ft_filter

int main(int argc, char **argv)
{

    char *temp[BUFFER_SIZE];
    char *buffer;
    char *res = NULL;
    int total_read;
    ssize_t bytes;

    if(argc != 2)
        return 1;

    while((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        buffer = realloc(res, (total_read + bytes + 1));
        if(!buffer)
        {
            perror("realloc");
            free(buffer);
            return 1;
        }
        res = buffer;
        memmove((res + total_read), temp, bytes);
        total_read = total_read + bytes;
        res[total_read] = '\0';
    }

    if(bytes < 0)
    {
        free(res);
        perror("bytes");
        return 1;
    }
    if(!res)
    {
        free(res);
        return 1;
    }
    ft_filter(res, argv[1]); // function where u find and replace 
    free(res);
    return 0;
}``` */
