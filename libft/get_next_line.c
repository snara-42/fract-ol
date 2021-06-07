/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:27:13 by snara             #+#    #+#             */
/*   Updated: 2021/04/12 21:31:57 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strj(char **dst, char const *s1, char const *s2, char *c)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i] && !(c[1] && s1[i] == c[0]))
		i++;
	j = 0;
	while (s2 && s2[j] && !(c[1] && (s1[i] == c[0] || s2[j] == c[0])))
		j++;
	if (malloc_(&d, sizeof(char) * (i + j + 1)))
	{
		d[i + j] = '\0';
		while (s2 && 0 < j--)
			d[i + j] = s2[j];
		while (s1 && 0 < i--)
			d[i] = s1[i];
	}
	if (*dst)
		free(*dst);
	*dst = d;
	return (d);
}

static char	*ft_strcmove(char *s, const char c, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && s[i] != c && (i < n || n == 0))
		i++;
	if (n == 0)
		return ((char *)((s[i] == c) * (uintptr_t)(&s[i])));
	i += (s[i] && s[i] == c);
	j = 0;
	while (s[i + j] && i + j < n)
	{
		s[j] = s[i + j];
		j++;
	}
	while (j <= n && s[j])
		s[j++] = '\0';
	return (s);
}

int	get_next_line(int fd, char **line)
{
	ssize_t		r;
	static char	buf[FD_SIZE][(size_t)BUFFER_SIZE + 1];

	if (!line || read(fd, buf[fd], 0) < 0)
		return (-1);
	r = 1;
	*line = NULL;
	while (1)
	{
		ft_strj(line, *line, buf[fd], "\n\n");
		if (r == 0 || ft_strcmove(buf[fd], '\n', 0))
		{
			ft_strcmove(buf[fd], '\n', BUFFER_SIZE + 1);
			return (buf[fd][0] || r);
		}
		r = read(fd, buf[fd], BUFFER_SIZE);
		if (!*line || r < 0)
			return (-1);
		buf[fd][r] = '\0';
	}
}
