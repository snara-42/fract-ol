/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:54 by snara             #+#    #+#             */
/*   Updated: 2021/06/07 11:38:17 by subaru           ###   ########.fr       */
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
	printf("%d %d: bye!\n", d->flag, errno);
	exit(0);
}

int		f_bpre(int b, int x, int y, t_all *d)
{
	printf("bpre %d: %d,%d %f\n", b, x, y, d->c.z);
	if (b == B_L)
		d->mouse = (t_ivec){x, y, 0};
	else if (b == B_R || b == B_M)
		d->c = (t_vec){-x / d->c.z, -y / d->c.z , d->c.z};
	else if (b == B_SU)
		d->c = (t_vec){d->c.x + x / d->c.z / ZOOM, d->c.y + y / d->c.z / ZOOM, (d->c.z * ZOOM)};
	else if (b == B_SD && 1 < d->c.z)
		d->c = (t_vec){d->c.x - x / d->c.z, d->c.y - y / d->c.z, (d->c.z / ZOOM)};
	f_loop(d);
	return (0);
}

int		f_brel(int b, int x, int y, t_all *d)
{
	printf("brel %d: %d,%d %f,%f\n", b, x, y, d->c.x, d->c.y);
	if (b == B_L)
		d->c = (t_vec){d->c.x + (d->mouse.x - x) / d->c.z, d->c.y + (d->mouse.y - y) / d->c.z , d->c.z};
	f_loop(d);
	return (0);
}

int		f_kpre(int k, t_all *d)
{
	printf("kpre %d: %f %f\n", k, d->c.x, d->c.y);
	if (k == K_ESC)
		f_exit(d);
	else if (k == K_A_D)
		d->c.y += d->s.y / d->c.z / 8;
	else if (k == K_A_U)
		d->c.y -= d->s.y / d->c.z / 8;
	else if (k == K_A_R)
		d->c.x += d->s.x / d->c.z / 8;
	else if (k == K_A_L)
		d->c.x -= d->s.x / d->c.z / 8;
	else if (k == K_R)
		d->c = (t_vec){d->s.x / DEFAULT / -2, d->s.y / DEFAULT / -2, DEFAULT};
	else if (k == K_A)
		d->clr.x -= 30;
	else if (k == K_D)
		d->clr.x += 15;
	else if (k == K_W)
		d->c = (t_vec){d->c.x + d->s.x / d->c.z / ZOOM / 2, d->c.y + d->s.y / d->c.z / ZOOM / 2, (d->c.z * ZOOM)};
	else if (k == K_S && 1 < d->c.z)
		d->c = (t_vec){d->c.x - d->s.x / d->c.z / 2, d->c.y - d->s.y / d->c.z / 2, (d->c.z / ZOOM)};
	else if (k == K_H)
		d->ini.x -= 0.1;
	else if (k == K_L)
		d->ini.x += 0.01;
	else if (k == K_K)
		d->ini.y -= 0.1;
	else if (k == K_J)
		d->ini.y += 0.01;
	f_loop(d);
	return (0);
}

int		f_krel(int k, t_all *d)
{
	printf("krel %d: %f %f\n", k, d->c.x, d->c.y);
	if (k == K_ESC)
		f_exit(d);
	/*else if (key == K_A_U)
		d->i.y++;
	else if (key == K_A_D)
		d->i.y--;
	else if (key == K_A_R)
		d->i.x++;
	else if (key == K_A_L)
		d->i.x--;*/
	return (0);
}

t_vec	vec_scale(t_vec p, t_vec c)
{
	t_vec	v;

	v = (t_vec){p.x / c.z + c.x, p.y / c.z + c.y, p.z};
	return (v);
}

int	calc_color(t_vec z, t_vec c, int max_i, double h)
{
	int	i;
	int	clr;

	i = 0;
	while (++i < max_i && z.x * z.x + z.y * z.y <= 4)
	{
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, z.z};
	}
	if (i < max_i)
	{
		h = (int)(h + i * 1080 / max_i) % 360;
		clr = ((300 <= h || h < 60) * 0xff0000 + (60 <= h && h < 180) * 0xff00 + (180 <= h && h < 300) * 0xff)
			| ((int)(0xff * (1 - fabs(fmod(h / 60, 2) - 1))) << ((int)h / 60 + 1) % 3 * 8);
		return (clr);
	}
	return (0x0);
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
			if (!d->flag)
				(d->img.d)[y * d->img.s.x + x] = calc_color(d->ini, vec_scale((t_vec){x, y, 0}, d->c), 180, (int)d->clr.x);
			else
				(d->img.d)[y * d->img.s.x + x] = calc_color(vec_scale((t_vec){(double)x, (double)y, 0}, d->c), d->ini, 180, d->clr.x);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
	return (0);
}



int	init(int ac, char **av, t_all *d)
{
	errno = 0;
	d->flag = (av[1][0] != '0');
	d->ac = ac;
	d->mlx = mlx_init();
	d->s = (t_ivec){WIDTH, HEIGHT, 0};
	d->c = (t_vec){WIDTH / DEFAULT / -2, HEIGHT / DEFAULT / -2, DEFAULT};
	d->clr = (t_vec){0, 0, 0};
	d->ini = (t_vec){-0.8 * d->flag, 0.15 * d->flag, 0};
	d->img.s = (t_ivec){WIDTH, HEIGHT, 0};
	d->win = mlx_new_window(d->mlx, d->s.x, d->s.y, av[0]);
	d->img.img = mlx_new_image(d->mlx, d->s.x, d->s.y);
	d->img.d = (int *)mlx_get_data_addr(d->img.img, &d->img.bpp, &d->img.lsz, &d->img.end);
	f_loop(d);
	return (!!d->mlx);
}

int	main(int ac, char **av)
{
	static t_all	d;

	if (ac < 2 && ft_error("usage: ./fractol [julia | mandelbrot]", 0))
		return (0);
	if (!init(ac, av, &d))
		f_exit(&d);

	mlx_hook(d.win, XE_KPRE, XM_KPRE, &f_kpre, &d);
	mlx_hook(d.win, XE_KREL, XM_KREL, &f_krel, &d);
	mlx_hook(d.win, XE_BPRE, XM_BPRE, &f_bpre, &d);
	mlx_hook(d.win, XE_BREL, XM_BREL, &f_brel, &d);
	mlx_hook(d.win, XE_DEST, XM_STRU, &f_exit, &d);
	//mlx_loop_hook(d.mlx, &f_loop, &d);
	mlx_loop(d.mlx);
	return (0);
}
