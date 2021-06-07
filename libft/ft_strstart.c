/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:24:56 by subaru            #+#    #+#             */
/*   Updated: 2021/04/12 19:48:48 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strend(const char *pf, const char *str, char c)
{
	int	i;
	int	j;
	int	s;

	s = 0;
	while (str && str[s])
		s++;
	i = 0;
	while (pf && str)
	{
		while (pf[i] && pf[i] == c)
			i++;
		while (pf[i] && pf[i] != c)
			i++;
		j = 0;
		while (j < s && j < i && pf[i - j - 1] == str[s - j - 1]
			&& pf[i - j - 1] != c)
			j++;
		if (j && (i == j || pf[i - j - 1] == c) && pf[i - j] == str[s - j])
			return ((char *)&pf[i - j]);
		if (pf[i] == '\0')
			return (NULL);
	}
	return (NULL);
}
