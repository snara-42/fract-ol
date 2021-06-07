/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:26:23 by snara             #+#    #+#             */
/*   Updated: 2021/03/06 18:23:59 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (1)
	{
		j = 0;
		while (str[i + j] == find[j] && i + j < n && find[j] != '\0')
			j++;
		if (find[j] == '\0')
			return ((char *)&str[i]);
		else if (i + j == n || str[i] == '\0')
			return (NULL);
		i++;
	}
}
