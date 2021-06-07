/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:45:56 by snara             #+#    #+#             */
/*   Updated: 2021/04/20 01:27:47 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char const *s, const char c)
{
	char	*d;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	d = (char *)malloc(sizeof(char) * (i + 1));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static void	*ft_free_all(char **d, int w)
{
	while (0 < w--)
	{
		free(d[w]);
		d[w] = NULL;
	}
	free(d);
	d = NULL;
	return (NULL);
}

size_t	ft_splitlen(char const *s, char c)
{
	size_t	w;
	int		i;

	w = 0;
	i = -1;
	while (s && s[++i])
		if ((w == 0 || s[i - 1] == c) && s[i] != c)
			w++;
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**d;
	int		w;

	if (!s)
		return (NULL);
	d = malloc(sizeof(char *) * (ft_splitlen(s, c) + 1));
	w = 0;
	while (d && *s)
	{
		if ((w == 0 || s[-1] == c) && *s != c)
		{
			d[w] = ft_strcdup(s, c);
			if (!d[w++])
				return (ft_free_all(d, w));
			d[w] = NULL;
		}
		s++;
	}
	return (d);
}

/*
**#include <stdio.h>
**int main(){char**d=ft_split("",0);for(;;){printf("%s",*d);if(!*d++)return 0;}}
*/
