/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:43:35 by snara             #+#    #+#             */
/*   Updated: 2021/04/12 18:14:11 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	if (!(malloc_(&d, sizeof(char) * (i + j + 1))))
		return (NULL);
	d[i + j] = '\0';
	while (s2 && 0 < j--)
		d[i + j] = s2[j];
	while (s1 && 0 < i--)
		d[i] = s1[i];
	return (d);
}
