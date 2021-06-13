#include "fractol.h"

// z_0, c, [max_iter, hsv.h, mode]

int	c_man(t_vec z, t_vec c, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_jul(t_vec c, t_vec z, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_bur(t_vec z, t_vec c, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){-z.x * z.x + z.y * z.y + c.x, 2 * fabs(z.x * z.y) + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_tri(t_vec z, t_vec c, int p[2])
{
	int		i;

	i = 0;
	while (++i <= p[0] && z.x * z.x + z.y * z.y < 4)
		z = (t_vec){z.x * z.x - z.y * z.y + c.x, -2 * z.x * z.y + c.y, 0};
	if (i <= p[0])
		return (hsv_rgb((p[1] + i * 720 / p[0]) % 360, 100, 100));
	return (0x0);
}

int	c_spi(t_vec c, t_vec z, int p[2])
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
