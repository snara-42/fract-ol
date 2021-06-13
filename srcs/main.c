/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:54 by snara             #+#    #+#             */
/*   Updated: 2021/06/14 03:05:50 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	f_exit(t_all *d)
{
	mlx_destroy_image(d->mlx, d->im.im);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	d->mlx = NULL;
	if (errno)
		perror("ERROR\n");
	printf("%d %d: bye!\n", d->fl, errno);
	exit(0);
}

int	f_loop(t_all *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < d->im.s.y)
	{
		x = -1;
		while (++x < d->im.s.x)
		{
			(d->im.d)[y * d->im.s.x + x] = d->func(d->n, vec_scale(
						(t_vec){x, y, 0}, d->c), (int []){d->n.z, d->clr.x});
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->im.im, 0, 0);
	return (0);
}

int	init(int ac, char **av, t_all *d)
{
	char const	*arr[] =
	{"0 ", "1 man ", "2 jul ", "3 bur ", "4 tri ", "5 spi ", NULL};
	int			i;

	i = 0;
	d->s = (t_ivec){WIDTH, HEIGHT, 0};
	while ((ac == 2 || ac == 4) && arr[++i])
		if (ft_strstart(arr[i], av[1], ' '))
			d->fl = i;
	if (!d->fl || (ac == 4 && ft_atoui_p(av[2], &d->s.x)
			+ ft_atoui_p(av[3], &d->s.y) + (d->s.x > 1920 || d->s.y > 1920)))
		exit(printf("usage: %s %s\n", av[0], T_U1 T_U2) * 0);
	d->func = (t_func[]){NULL, c_man, c_jul, c_bur, c_tri, c_spi}[d->fl];
	d->im.s = d->s;
	d->c = (t_vec){d->s.x / -2. / DEFAULT, d->s.y / -2. / DEFAULT, DEFAULT};
	d->clr = (t_vec){0, 0, 0};
	d->key = (t_vec){1, 0, 0};
	d->ini = (t_vec){-0.8 * (d->fl == julia) + 0.1 * (d->fl == spiral),
		0.15 * (d->fl == julia) + 0.1 * (d->fl == spiral), DEFAULT};
	d->n = d->ini;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->s.x, d->s.y, av[0]);
	d->im.im = mlx_new_image(d->mlx, d->im.s.x, d->im.s.y);
	d->im.d = (int *)mlx_get_data_addr(d->im.im, &d->im.b, &d->im.l, &d->im.e);
	return (d->mlx && printf(T_H1 T_H2) + f_loop(d));
}

int	main(int ac, char **av)
{
	static t_all	d;

	errno = 0;
	if (!init(ac, av, &d))
		f_exit(&d);
	mlx_hook(d.win, XE_KPRE, XM_KPRE, &f_kpre, &d);
	mlx_hook(d.win, XE_KREL, XM_KREL, &f_krel, &d);
	mlx_hook(d.win, XE_BPRE, XM_BPRE, &f_bpre, &d);
	mlx_hook(d.win, XE_BREL, XM_BREL, &f_brel, &d);
	mlx_hook(d.win, XE_DEST, XM_STRU, &f_exit, &d);
	mlx_hook(d.win, XE_MOTI, XM_MOTI, &f_moti, &d);
	mlx_expose_hook(d.win, &f_loop, &d);
	mlx_loop(d.mlx);
	return (0);
}
