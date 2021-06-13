/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subaru <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:02:18 by subaru            #+#    #+#             */
/*   Updated: 2021/06/13 07:13:46 by snara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_ivec	ivec_add(t_ivec a, t_ivec b)
{
	const t_ivec	v = {a.x + b.x, a.y + b.y, a.z + b.z};

	return (v);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	const t_vec	v = {a.x + b.x, a.y + b.y, a.z + b.z};

	return (v);
}

t_ivec	ivec_mul(t_ivec a, int b)
{
	const t_ivec	v = {a.x * b, a.y * b, a.z * b};

	return (v);
}

t_vec	vec_mul(t_vec a, double b)
{
	const t_vec	v = {a.x * b, a.y * b, a.z * b};

	return (v);
}

t_vec	vec_scale(t_vec p, t_vec c)
{
	const t_vec	v = {p.x / c.z + c.x, p.y / c.z + c.y, p.z};

	return (v);
}
