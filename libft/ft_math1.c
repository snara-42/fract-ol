/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:07:15 by subaru            #+#    #+#             */
/*   Updated: 2021/04/12 18:07:17 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bitr(int n)
{
	int	i;

	i = 0;
	while (n && !(n & 1 << i))
		i++;
	return (!!n * ++i);
}

int	ft_bitl(int n)
{
	int	i;

	i = 0;
	while (n >> i)
		i++;
	return (!!n * ++i);
}

int	ft_min(int x, int y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

int	ft_max(int x, int y)
{
	if (x < y)
		return (y);
	else
		return (x);
}

int	ft_mid(int x, int y, int z)
{
	return (ft_max(ft_min(ft_max(x, z), y), ft_min(x, z)));
}

/*
**#include <stdio.h>
**int	main(){printf("%d",ft_bitr(8));return (0);}
*/
