/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <snara@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:54 by snara             #+#    #+#             */
/*   Updated: 2021/06/01 01:23:08 by subaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 600
#define HEIGHT 600
#define MOVE 16
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
	int	i;

	mlx_destroy_window(d->mlx, d->win);
	mlx_destroy_image(d->mlx, d->img.img);
	free(d->mlx);
	i = 0;
	if (errno)
		perror("ERROR\n");
	printf("%d %d: bye!\n", d->flag, errno);
	exit(0);
}

int		f_bpre(int b, int x, int y, t_all *d)
{
	printf("bpre %d: %d,%d %f\n", b, x, y, d->c.z);
	if (b == B_L)
		d->c = (t_vec){x, y, d->c.z};
	else if (b == B_R)
		d->c = (t_vec){WIDTH / 2, HEIGHT / 2, 128};
	else if (b == B_SU)
		d->c = (t_vec){d->c.x, d->c.y, (d->c.z * ZOOM)};
	else if (b == B_SD)
		d->c = (t_vec){d->c.x, d->c.y, (d->c.z <= 1) + (d->c.z / ZOOM)};
	f_loop(d);
	return (0);
}

int		f_brel(int b, int x, int y, t_all *d)
{
	f_loop(d);
	printf("brel %d: %d,%d\n", b, x, y);
	return (0);
}

int		f_kpre(int key, t_all *d)
{
	printf("kpre %d: %f %f\n", key, d->c.x, d->c.y);
	if (key == K_ESC)
		f_exit(d);
	else if (key == K_A_U)
		d->c.y += MOVE;
	else if (key == K_A_D)
		d->c.y -= MOVE;
	else if (key == K_A_R)
		d->c.x -= MOVE;
	else if (key == K_A_L)
		d->c.x += MOVE;
	f_loop(d);
	return (0);
}

int		f_krel(int key, t_all *d)
{
	printf("krel %d: %f %f\n", key, d->c.x, d->c.y);
	if (key == K_ESC)
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

	v = (t_vec){(p.x - c.x) / c.z, (p.y - c.y) / c.z, p.z};
	return (v);
}

int	calc_color(t_vec z, t_vec c, int max_i)
{
	int	i;

	i = 0;
	while (++i < max_i && z.x * z.x + z.y * z.y <= 4)
	{
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, z.z};
	}
	if (i < max_i)
		return (1 * (max_i - i));
	return (0x0);
}

int	f_loop(t_all *d)
{
	int		x;
	int		y;

	y = -1;
	while (++y < d->img.s.y)
	{
		x = -1;
		while (++x < d->img.s.x)
		{
			if (1)
				(d->img.d)[y * d->img.s.x + x] = calc_color((t_vec){0, 0, 0}, vec_scale((t_vec){(double)x, (double)y, 0}, d->c), 128);
			else
				(d->img.d)[y * d->img.s.x + x] = calc_color(vec_scale((t_vec){(double)x, (double)y, 0}, d->c), (t_vec){-0.8, 0.156, 0}, 128);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
	return (0);
}



int	init(int ac, char **av, t_all *d)
{
	const t_ivec	zi = {0, 0, 0};
	int				fd;

	errno = 0;
	d->ac = ac;
	d->mlx = mlx_init();
	d->s = (t_ivec){WIDTH, HEIGHT, 0};
	d->c = (t_vec){WIDTH / 2, HEIGHT / 2, 128};
	d->clr = (t_vec){0, 0, 0};
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
