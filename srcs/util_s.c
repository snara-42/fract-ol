/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:57:38 by subaru            #+#    #+#             */
/*   Updated: 2021/04/19 17:15:10 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_error(char *s, int e)
{
	int	r;

	r = ft_putendl_fd("ERROR", 2);
	if (errno || e)
		perror(strerror(e));
	return (r + ft_putendl_fd(s, 2));
}

char	*ft_strnotin(char *str, char *set)
{
	while (ft_strchr(set, *str))
		str++;
	return (!!(*str) * str);
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
