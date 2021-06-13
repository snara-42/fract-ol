/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:50:25 by subaru            #+#    #+#             */
/*   Updated: 2021/06/13 07:58:08 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fractol.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>

char	*ft_strchr(const char *s, int c)
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

int	ft_atoi_p(char *s, int *n)
{
	int			m;
	const int	b = 10;
	const char	d[] = "013456789";

	*n = 0;
	while (ft_strchr("\t\n\v\f\r ",*s))
		s++;
	m = (*s == '-');
	s += (*s == '+' || *s =='-');
	while (*s)
	{
		if (!ft_strchr(d, *s) || (*n > INT_MAX / b)
			|| (*n == INT_MAX / b && (ft_strchr(d, *s) - d) > INT_MAX % b + m))
			return (1);
		*n = *n * b + (ft_strchr(d, *s++) - d);
	}
	*n *= 1 + (m * -2);
	return (0);
}

int	int_find(int n, int *a, int s)
{
	int	i;

	i = 0;
	while (i < s && a && a[i] != n)
		++i;
	if (i == s || !a)
		return (-1);
	return (i);
}

int	hsv_rgb(int h, int s, int v)
{
	int	c;
	int	h_;

	h = (h % 360 + 360) % 360;
	h_ = h / 60;
	c = ((0xff << ((2 - (h_ + 1) % 6 / 2) * 8)) | (int)
			(0xff * (1 - fabs(fmod(h / 60.0, 2) - 1))) << (h_ + 1) % 3 * 8)
		+ 0x010101 * (s - v);
	return (c);
}
