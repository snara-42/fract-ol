/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:49:40 by snara             #+#    #+#             */
/*   Updated: 2021/04/12 16:36:14 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (write(fd, s, i));
}

int	ft_putstrcat_fd(char *s1, char *s2, int fd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	return ((s1 && write(fd, s1, i)) + (s2 && write(fd, s2, j)));
}

int	ft_putstr_n(char *s, int n, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if (i < n || n < 0)
		return (write(fd, s, i));
	return (write(fd, s, n));
}

/*
**int main(){char s[]="4Tt ";ft_putstr_fd(s,1);return 0;}
*/
