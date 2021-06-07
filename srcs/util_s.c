/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:57:38 by subaru            #+#    #+#             */
/*   Updated: 2021/06/07 12:41:35 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

char	*ft_strstart(const char *pf, const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (pf && str)
	{
		while (pf[i] && pf[i] == c)
			i++;
		j = 0;
		while (str[j] && pf[i + j] && pf[i + j] == str[j] && pf[i + j] != c)
			j++;
		if (j && pf[i + j] == c && pf[i + j - 1] == str[j - 1])
			return ((char *)&pf[i]);
		if (pf[i] == '\0')
			return (NULL);
		while (pf[i] && pf[i] != c)
			i++;
	}
	return (NULL);
}
