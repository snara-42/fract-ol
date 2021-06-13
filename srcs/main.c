/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:54 by snara             #+#    #+#             */
/*   Updated: 2021/06/13 19:46:27 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	f_exit(t_all *d)
{
	mlx_destroy_image(d->mlx, d->img.img);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	d->mlx = NULL;
	if (errno)
		perror("ERROR\n");
	printf("%d %d: bye!\n", d->fl, errno);
	exit(0);
}

int	main(int ac, char **av)
{
	static t_all	d;
	const char		*s[] =
	{"0 ", "1 mandelbrot ", "2 julia ", "3 burning ", "4 spiral ", NULL};
	int				i;

	i = 0;
	while (ac >= 2 && s[++i])
		if (ft_strstart(s[i], av[1], ' '))
			d.fl = i;
	if (!d.fl || (ac != 2 && ac != 4) || (ac == 4 && ft_atoui_p(av[2], &d.s.x)
			+ ft_atoui_p(av[3], &d.s.y) + (d.s.x > 1920 || d.s.y > 1920)))
		return (printf("usage: %s %s\n", av[0], T_U1 T_U2) * 0);
	if (!init(ac, av, &d))
		f_exit(&d);
	mlx_hook(d.win, XE_KPRE, XM_KPRE, &f_kpre, &d);
	mlx_hook(d.win, XE_KREL, XM_KREL, &f_krel, &d);
	mlx_hook(d.win, XE_BPRE, XM_BPRE, &f_bpre, &d);
	mlx_hook(d.win, XE_BREL, XM_BREL, &f_brel, &d);
	mlx_hook(d.win, XE_DEST, XM_STRU, &f_exit, &d);
	mlx_loop(d.mlx);
	return (0);
}
