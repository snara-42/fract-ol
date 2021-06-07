/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:45:14 by snara             #+#    #+#             */
/*   Updated: 2021/05/15 03:47:45 by snara            ###   ########.fr       */
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
