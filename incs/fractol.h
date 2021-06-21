#ifndef FRACTOL_H
# define FRACTOL_H

//# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx.h"

# define XE_KPRE	2
# define XE_KREL	3
# define XE_BPRE	4
# define XE_BREL	5
# define XE_MOTI	6
# define XE_ENTER	7
# define XE_LEAVE	8
# define XE_FOCI	9
# define XE_FOCO	10
# define XE_DEST	17
# define XE_CLIE	33

# define XM_KPRE	0x1
# define XM_KREL	0x2
# define XM_BPRE	0x4
# define XM_BREL	0x8
# define XM_ENTER	0x10
# define XM_LEAVE	0x20
# define XM_MOTI	0x40
# define XM_MOTH	0x80
# define XM_EXPO	0x8000
# define XM_VISI	0x10000
# define XM_STRU	0x20000
# define XM_ALL		0xfffffff

# if __linux__
#  define B_L	1
#  define B_R	2
#  define B_M	3
#  define B_SD	4
#  define B_SU	5
#  define B_SL	6
#  define B_SR	7
#  define K_SP	32
#  define K_ENT	65293
#  define K_LSH	65505
#  define K_RSH	65506
#  define K_ESC	65307
#  define K_A_L	65361
#  define K_A_U	65362
#  define K_A_R	65363
#  define K_A_D	65364
#  define K_0	48
#  define K_1	49
#  define K_2	50
#  define K_3	51
#  define K_4	52
#  define K_5	53
#  define K_6	54
#  define K_7	55
#  define K_8	56
#  define K_9	57
#  define K_A	97
#  define K_B	98
#  define K_C	99
#  define K_D	100
#  define K_E	101
#  define K_F	102
#  define K_G	103
#  define K_H	104
#  define K_I	105
#  define K_J	106
#  define K_K	107
#  define K_L	108
#  define K_M	109
#  define K_N	110
#  define K_O	111
#  define K_P	112
#  define K_Q	113
#  define K_R	114
#  define K_S	115
#  define K_T	116
#  define K_U	117
#  define K_V	118
#  define K_W	119
#  define K_X	120
#  define K_Y	121
#  define K_Z	122

# elif __APPLE__
#  define B_L	1
#  define B_R	2
#  define B_M	3
#  define B_SD	4
#  define B_SU	5
#  define B_SL	6
#  define B_SR	7
#  define K_A_L	123
#  define K_A_R	124
#  define K_A_D	125
#  define K_A_U	126
#  define K_A 0
#  define K_B 11
#  define K_C 8
#  define K_D 2
#  define K_E 14
#  define K_F 3
#  define K_G 5
#  define K_H 4
#  define K_I 34
#  define K_J 38
#  define K_K 40
#  define K_L 37
#  define K_M 46
#  define K_N 45
#  define K_O 31
#  define K_P 35
#  define K_Q 12
#  define K_R 15
#  define K_S 1
#  define K_T 17
#  define K_U 32
#  define K_V 9
#  define K_W 13
#  define K_X 7
#  define K_Y 16
#  define K_Z 6
#  define K_SP	49
#  define K_ENT	52
#  define K_LSH	56
#  define K_RSH	60
#  define K_ESC	53

# endif

# define WIDTH	512
# define HEIGHT	512
# define MOVE 16
# define DEFAULT 128
# define ZOOM 2
# define T_H1 "\e[92mspace: help\narrow: move\nSW: zoom\nAD: color shift\n"
# define T_H2 "UI: iteration max\nHL: real part\nJK: imaginary part\e[0m\n"
# define T_U1 "[mandelbrot | julia | burningship | tricorn | spiral] "
# define T_U2 "[width height (<=1920)]\n"

typedef int	(*t_func)();

typedef struct s_ivec{
	int		x;
	int		y;
	int		z;
}			t_ivec;

typedef struct s_vec{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_im{
	void	*im;
	int		*d;
	t_ivec	s;
	int		b;
	int		l;
	int		e;
}	t_im;

typedef struct s_all{
	void	*mlx;
	void	*win;
	t_im	im;
	t_ivec	i;
	t_ivec	s;
	t_ivec	mouse;
	t_vec	c;
	t_vec	clr;
	t_vec	key;
	t_vec	ini;
	t_vec	n;
	t_func	func;
	int		fl;
	int		ac;
	int		e;
}			t_all;

typedef enum e_fractol{
	undefined,
	mandelbrot,
	julia,
	burning,
	tricorn,
	spiral
}	t_e_fractol;

t_ivec	ivec_add(t_ivec a, t_ivec b);
t_ivec	ifvec_add(t_ivec a, t_vec b);
t_vec	vec_add(t_vec a, t_vec b);
t_ivec	ivec_mul(t_ivec a, int b);
t_vec	vec_mul(t_vec a, double b);
t_vec	vec_scale(t_vec p, t_vec c);

char	*ft_strchr(const char *s, int c);
char	*ft_strstart(const char *pf, const char *str, char c);
char	*ft_strchr(const char *s, int c);
int		ft_atoui_p(char *s, int *n);
int		int_find(int n, int *a, int s);
int		hsv_rgb(int h, int s, int v);

int		f_loop(t_all *d);
int		f_kpre(int k, t_all *d);
int		f_krel(int k, t_all *d);
int		f_bpre(int b, int x, int y, t_all *d);
int		f_brel(int b, int x, int y, t_all *d);
int		f_moti(int x, int y, t_all *d);
int		f_exit(t_all *d);
int		init(int ac, char **av, t_all *d);
int		c_man(t_vec z, t_vec c, int p[2]);
int		c_jul(t_vec c, t_vec z, int p[2]);
int		c_bur(t_vec z, t_vec c, int p[2]);
int		c_tri(t_vec z, t_vec c, int p[2]);
int		c_spi(t_vec c, t_vec z, int p[2]);

#endif
