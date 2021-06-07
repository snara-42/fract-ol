/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:09:54 by snara             #+#    #+#             */
/*   Updated: 2021/05/11 18:51:23 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	t_u		n;
	int		s;
	int		i;

	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	s = (str[i] == '-');
	i += (str[i] == '-' || str[i] == '+');
	n = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + str[i++] - '0';
		if ((unsigned int)(INT_MAX + s) < n)
			return (-!s);
	}
	return ((int)(n * (1 - 2 * s)));
}

/*
**#include <stdio.h>
**int main(void){const char *s =" \t\n\v\f\r -9223372036854775808";
**printf("%d %d\n",atoi(s),ft_atoi(s));return(0);}
*/
