/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:42:09 by snara             #+#    #+#             */
/*   Updated: 2021/04/12 19:51:14 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	sublen(size_t i, unsigned int s, size_t l)
{
	if (i < s)
		return (0);
	else if (i - s < l)
		return (i - s);
	else
		return (l);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	d = (char *)malloc(sizeof(char) * (sublen(i, start, len) + 1));
	if (!s || !d)
		return (NULL);
	if (0 < sublen(i, start, len))
	{
		i = 0;
		s += start;
		while (s[i] && i < len)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	else
		d[0] = '\0';
	return (d);
}
