/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:54 by snara             #+#    #+#             */
/*   Updated: 2021/06/07 12:50:10 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 512
#define HEIGHT 512
#define MOVE 16
#define	DEFAULT 128
#define ZOOM 2

int	f_loop(t_all *d);

int	ft_error(char *s, int e)
{
	int	r;

	r = printf("ERROR\n");
	if (errno || e)
		perror(strerror(e));
	return (r + printf("%s\n", s));
}

int	f_exit(t_all *d)
{
	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img.img);
	free(d->mlx);
	if (errno)
		perror("ERROR\n");
	printf("%d %d: bye!\n", d->fl, errno);
	exit(0);
}

int	f_kpre(int k, t_all *d)
{
	printf("kpre %d: %f,%f %f%+fi %f\n", k, d->c.x, d->c.y, d->ini.x, d->ini.y, d->ini.z);
	if (k == K_ESC)
		f_exit(d);
	else if (int_find(k, (int []){K_LSH, K_RSH}, 2) >= 0)
		d->key.x = (double []){0.1, 10}[(k == K_RSH)];
	else if (int_find(k, (int []){K_A_D, K_A_U, K_A_R, K_A_L}, 4) >= 0)
		d->c = vec_add(d->c, vec_mul((t_vec)
				{(k == K_A_R) - (k == K_A_L), (k == K_A_D) - (k == K_A_U), 0},
					fmin(d->s.x, d->s.y) * d->key.x / d->c.z / 8));
	else if (k == K_A || k == K_D)
		d->clr.x = (int)(d->clr.x + ((k == K_A) - (k == K_D)) * d->key.x * 10 + 360) % 360;
	else if (k == K_W)
		d->c = (t_vec){d->c.x + d->s.x / d->c.z / 2 / ZOOM,
			d->c.y + d->s.y / d->c.z / ZOOM / 2, d->c.z * ZOOM};
	else if (k == K_S && 1 < d->c.z)
		d->c = (t_vec){d->c.x - d->s.x / d->c.z / 2,
			d->c.y - d->s.y / d->c.z / 2, d->c.z / ZOOM};
	else if (int_find(k, (int []){K_H, K_L, K_K, K_J, K_I, K_U}, 6) >= 0)
		d->ini = vec_add(vec_mul((t_vec){((k == K_L) - (k == K_H)) * 0.0001,
					((k == K_J) - (k == K_K)) * 0.0001, (k == K_I) - (k == K_U)},
					d->key.x * 10), d->ini);
	else if (k == K_R)
	{
		d->c = (t_vec){d->s.x / DEFAULT / -2, d->s.y / DEFAULT / -2, DEFAULT};
		d->ini = (t_vec){-0.8 * (d->fl == 2), 0.15 * (d->fl == 2), DEFAULT};
	}
	f_loop(d);
	return (0);
}

int	f_krel(int k, t_all *d)
{
	printf("krel %d: %f %f %f\n", k, d->c.x, d->c.y, d->key.x);
	if (k == K_ESC)
		f_exit(d);
	else if (k == K_LSH || k == K_RSH)
		d->key.x = 1.0;
	return (0);
}

int	f_bpre(int b, int x, int y, t_all *d)
{
	printf("bpre %d: %d,%d %f\n", b, x, y, d->c.z);
	if (b == B_L)
		d->mouse = (t_ivec){x, y, 0};
	else if (b == B_R || b == B_M)
		d->c = (t_vec){-x / d->c.z, -y / d->c.z, d->c.z};
	else if (b == B_SU)
		d->c = (t_vec){d->c.x + x / d->c.z / ZOOM,
			d->c.y + y / d->c.z / ZOOM, (d->c.z * ZOOM)};
	else if (b == B_SD && 1 < d->c.z)
		d->c = (t_vec){d->c.x - x / d->c.z, d->c.y - y / d->c.z, d->c.z / ZOOM};
	f_loop(d);
	return (0);
}

int	f_brel(int b, int x, int y, t_all *d)
{
	printf("brel %d: %d,%d %f,%f\n", b, x, y, d->c.x, d->c.y);
	if (b == B_L)
		d->c = (t_vec){d->c.x + (d->mouse.x - x) / d->c.z,
			d->c.y + (d->mouse.y - y) / d->c.z, d->c.z};
	f_loop(d);
	return (0);
}

t_vec	vec_scale(t_vec p, t_vec c)
{
	t_vec	v;

	v = (t_vec){p.x / c.z + c.x, p.y / c.z + c.y, p.z};
	return (v);
}

int	hsv_rgb(int h, int s, int v)
{
	int			c;
	const int	h_ = (h % 360 + 360) % 360 / 60;

	c = ((0xff << ((2 - (h_ + 1) % 6 / 2) * 8))
			| ((int)(0xff * (1 - fabs(fmod(h / 60.0, 2) - 1))) << (h_ + 1) % 3 * 8))
		+ 0x010101 * (s - v);
	return (c);
}

// z_0, c, [max_iter, hsv.h, mode]

int	calc_color(t_vec z, t_vec c, int p[3])
{
	int		i;

	i = 0;
	while (!p[2] && ++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, 0};
	while (p[2] == 1 && ++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){-z.x * z.x + z.y * z.y + c.x, 2 * fabs(z.x * z.y) + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 360 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	calc_spiral(t_vec z, t_vec c, int p[3])
{
	double	th;
	double	t;
	double	r;

	r = hypot(z.y, z.x);
	t = atan2(z.y, z.x) + M_PI;
	th = fmod(log(r * exp(c.y * 100)) / (c.x + 1), M_PI * 2) + M_PI * 2;
	return (hsv_rgb((int)(fmod(p[1] + t + th, M_PI * 2) * 180 / M_PI)
		% 360, 100, 100));
}

int	f_loop(t_all *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < d->img.s.y)
	{
		x = -1;
		while (++x < d->img.s.x)
		{
			if (d->fl == mandelbrot)
				(d->img.d)[y * d->img.s.x + x] = calc_color(d->ini, vec_scale((t_vec){x, y, 0}, d->c), (int[]){d->ini.z, d->clr.x, 0});
			else if (d->fl == julia)
				(d->img.d)[y * d->img.s.x + x] = calc_color(vec_scale((t_vec){x, y, 0}, d->c), d->ini, (int[]){d->ini.z, d->clr.x, 0});
			else if (d->fl == burning)
				(d->img.d)[y * d->img.s.x + x] = calc_color(d->ini, vec_scale((t_vec){x, y, 0}, d->c), (int[]){d->ini.z, d->clr.x, 1});
			else if (d->fl == spiral)
				(d->img.d)[y * d->img.s.x + x] = calc_spiral(vec_scale((t_vec){x, y, 0}, d->c), d->ini, (int[]){d->ini.z, d->clr.x, 0});
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
	return (0);
}

int	init(int ac, char **av, t_all *d)
{
	errno = 0;
	d->ac = ac;
	d->mlx = mlx_init();
	d->s = (t_ivec){WIDTH, HEIGHT, 0};
	d->c = (t_vec){WIDTH / DEFAULT / -2, HEIGHT / DEFAULT / -2, DEFAULT};
	d->clr = (t_vec){0, 0, 0};
	d->key = (t_vec){1, 0, 0};
	d->ini = (t_vec){-0.8 * (d->fl == julia), 0.2 * (d->fl == julia), DEFAULT};
	d->img.s = (t_ivec){WIDTH, HEIGHT, 0};
	d->win = mlx_new_window(d->mlx, d->s.x, d->s.y, av[0]);
	d->img.img = mlx_new_image(d->mlx, d->s.x, d->s.y);
	d->img.d = (int *)mlx_get_data_addr(d->img.img, &d->img.bpp,
			&d->img.lsz, &d->img.end);
	f_loop(d);
	return (!!d->mlx);
}

int	main(int ac, char **av)
{
	static t_all	d;
	const char		*s[] = {
		"0 ", "1 mandelbrot ", "2 julia ", "3 burning ", "4 spiral ", NULL};
	int				i;

	i = 0;
	while (ac >= 2 && s[++i])
		if (ft_strstart(s[i], av[1], ' '))
			d.fl = i;
	if ((!d.fl) && printf("usage: %s %s\n",
			av[0], "[mandelbrot | julia | burningship | spiral]"))
		return (0);
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
