/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_solution2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:01:37 by albarrei          #+#    #+#             */
/*   Updated: 2025/11/06 18:29:59 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024

void *memmem(const void *haystack, size_t haystacklen,
                    const void *needle, size_t needlelen);

void	filter_block(char *buf, size_t n, char *pattern, size_t patlen)
{
	char	*found;
	size_t	i;

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
	char		buf[BUFSIZE];
	ssize_t		n;
	size_t		patlen;
	size_t		keep;

	if (argc != 2)
		return (1);
	patlen = strlen(argv[1]);
	keep = 0;
	n = read(0, buf, BUFSIZE);
	while (n > 0)
	{
		filter_block(buf, n, argv[1], patlen);
		if (patlen > 1 && n >= (ssize_t)(patlen - 1))
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
		n += keep;
	}
	if (keep > 0)
		write(1, buf, keep);
	return (0);
}
