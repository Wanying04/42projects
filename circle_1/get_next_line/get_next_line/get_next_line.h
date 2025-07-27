/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:07:15 by wtang             #+#    #+#             */
/*   Updated: 2025/05/20 13:54:51 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
// #include <stdio.h>
// #include <fcntl.h>

char	*get_next_line(int fd);
int		gnl_init(char **buffer, char **line, char **storage);
int		gnl_read_loop(int fd, char **line, char *buffer, int *bytes_read);
char	*gnl_process_line(char **line, char **storage);
char	*gnl_cleanup(char *buffer, char **storage, char *line);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif