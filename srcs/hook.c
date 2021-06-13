/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 07:04:09 by snara             #+#    #+#             */
/*   Updated: 2021/06/13 07:07:00 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	f_kpre(int k, t_all *d)
{
	if (int_find(k, (int []){K_LSH, K_RSH}, 2) >= 0)
		d->key.x = (double []){0.1, 10}[(k == K_RSH)];
	else if (int_find(k, (int []){K_A_D, K_A_U, K_A_R, K_A_L}, 4) >= 0)
		d->c = vec_add(d->c, vec_mul((t_vec)
				{(k == K_A_R) - (k == K_A_L), (k == K_A_D) - (k == K_A_U), 0},
					fmin(d->s.x, d->s.y) * d->key.x / d->c.z / 8));
	else if (k == K_A || k == K_D)
		d->clr.x = (int)(d->clr.x + ((k == K_A) - (k == K_D)) * d->key.x
				* 10 + 360) % 360;
	else if (k == K_W)
		d->c = (t_vec){d->c.x + d->s.x / d->c.z / 2 / ZOOM,
			d->c.y + d->s.y / d->c.z / ZOOM / 2, d->c.z * ZOOM};
	else if (k == K_S && 1 < d->c.z)
		d->c = (t_vec){d->c.x - d->s.x / d->c.z / 2,
			d->c.y - d->s.y / d->c.z / 2, d->c.z / ZOOM};
	else if (int_find(k, (int []){K_H, K_L, K_K, K_J, K_I, K_U}, 6) >= 0)
		d->n = vec_add(vec_mul((t_vec){((k == K_L) - (k == K_H)) * 0.0001,
					((k == K_J) - (k == K_K)) * 0.0001,
					(k == K_I) - (k == K_U)}, d->key.x * 10), d->n);
	else if (d->key.x == 1 && k == K_R)
		d->c = (t_vec){d->s.x / DEFAULT / -2, d->s.y / DEFAULT / -2, DEFAULT};
	else if (d->key.x == 0.1 && k == K_R)
		d->n = d->ini;
	return (printf("p %d:%f,%f %f%+fi %f\n", k, d->c.x, d->c.y, d->n.x, d->n.y,
			d->n.z) && f_loop(d));
}

int	f_krel(int k, t_all *d)
{
	printf("r %d:%f %f %f\n", k, d->c.x, d->c.y, d->key.x);
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
			(d->img.d)[y * d->img.s.x + x] = d->func(d->n, vec_scale(
						(t_vec){x, y, 0}, d->c), (int []){d->n.z, d->clr.x});
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img.img, 0, 0);
	return (0);
}
