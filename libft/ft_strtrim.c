/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:45:14 by snara             #+#    #+#             */
/*   Updated: 2021/06/07 12:22:55 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strc(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		else if (!*s)
			return (NULL);
		s++;
	}
}

size_t	ft_trimlen(char const *s, char const *set)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s && ft_strchr(set, *s))
		s++;
	while (s[i])
		i++;
	while (0 < i && ft_strchr(set, s[i - 1]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*d;
	size_t	i;

	if (!s || !set)
		return (NULL);
	i = 0;
	while (*s && ft_strc(set, *s))
		s++;
	while (s[i])
		i++;
	while (0 < i && ft_strc(set, s[i - 1]))
		i--;
	d = (char *)malloc(sizeof(char) * (i + 1));
	if (!d)
		return (NULL);
	d[i] = '\0';
	while (0 < i--)
		d[i] = s[i];
	return (d);
}
