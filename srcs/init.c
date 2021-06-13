#include "fractol.h"

// z_0, c, [max_iter, hsv.h, mode]

int	c_mandelbrot(t_vec z, t_vec c, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_julia(t_vec c, t_vec z, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_burning(t_vec z, t_vec c, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){-z.x * z.x + z.y * z.y + c.x, 2 * fabs(z.x * z.y) + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_spiral(t_vec c, t_vec z, int p[2])
{
	double	th;
	double	t;
	double	r;

	r = hypot(z.y, z.x);
	t = atan2(z.y, z.x) + M_PI;
	th = fmod(log(r * exp(c.y * 100)) / c.x, M_PI * 2) + M_PI * 2;
	return (hsv_rgb((int)(fmod(p[1] + t + th, M_PI * 2) * 180 / M_PI)
		% 360, 100, 100));
}

int	init(int ac, char **av, t_all *d)
{
	errno = 0;
	d->func = (t_func[]){c_mandelbrot, c_julia, c_burning, c_spiral}[d->fl - 1];
	d->ac = ac;
	if (ac == 2)
		d->s = (t_ivec){WIDTH, HEIGHT, 0};
	d->img.s = d->s;
	d->c = (t_vec){d->s.x / -2. / DEFAULT, d->s.y / -2. / DEFAULT, DEFAULT};
	d->clr = (t_vec){0, 0, 0};
	d->key = (t_vec){1, 0, 0};
	d->ini = (t_vec){-0.8 * (d->fl == julia) + 0.1 * (d->fl == spiral),
		0.15 * (d->fl == julia) + 0.1 * (d->fl == spiral), DEFAULT};
	d->n = d->ini;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->s.x, d->s.y, av[0]);
	d->img.img = mlx_new_image(d->mlx, d->img.s.x, d->img.s.y);
	d->img.d = (int *)mlx_get_data_addr(d->img.img, &d->img.bpp, &d->img.lsz,
			&d->img.end);
	printf(T_H1 T_H2);
	f_loop(d);
	return (!!d->mlx);
}
