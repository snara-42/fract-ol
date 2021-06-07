/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:47:28 by snara             #+#    #+#             */
/*   Updated: 2021/04/12 18:30:43 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*d;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (!(malloc_(&d, sizeof(char) * (i + 1))))
		return (NULL);
	d[i] = '\0';
	i = 0;
	while (s[i])
	{
		d[i] = f(i, s[i]);
		i++;
	}
	return (d);
}
