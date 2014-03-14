/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 09:43:42 by mmartin           #+#    #+#             */
/*   Updated: 2014/03/14 19:50:52 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include "ft_rt.h"

static t_vector		ft_get_normal(t_object obj, t_vector inter)
{
	t_vector	normal;

	if (!ft_strcmp(obj.type, "sphere"))
		normal = ft_vector_sub(inter, obj.pos);
	else if (!ft_strcmp(obj.type, "cylinder"))
		normal = ft_get_normal_cylinder(obj, inter);
	else if (!ft_strcmp(obj.type, "cone"))
		normal = ft_get_normal_cone(obj, inter);
	else
		normal = ft_vector_neg(obj.axe);
	normal = ft_vector_normalize(normal);
	return (normal);
}

static void			ft_get_color(t_object obj, t_data *d, int i, t_vector n)
{
	double			alpha;

	alpha = ft_vector_dot(d->lights[i].dir, n);
	d->r += obj.material.r * alpha * d->lights[i].coef;
	if (d->r < 0)
		d->r = 0;
	if (d->r > 255)
		d->r = 255;
	d->g += obj.material.g * alpha * d->lights[i].coef;
	if (d->g < 0)
		d->g = 0;
	if (d->g > 255)
		d->g = 255;
	d->b += obj.material.b * alpha * d->lights[i].coef;
	if (d->b < 0)
		d->b = 0;
	if (d->b > 255)
		d->b = 255;
}

static int			ft_search_inter(t_data *d, int i, double alpha_i, int obj)
{
	extern t_tab_obj	g_obj[5];
	int					k;
	int					j;
	double				alpha;
	t_vector			v;

	j = -1;
	v = d->lights[i].dir;
	while (++j < d->nb_objects)
	{
		k = -1;
		if (j != obj)
		{
			while (g_obj[++k].type != NULL)
			{
				if (ft_strcmp(d->objects[j].type, g_obj[k].type) == 0)
				{
					alpha = g_obj[k].func(d->objects[j], v, d->lights[i].pos);
					if (alpha > 0.02 && alpha < alpha_i)
						return (1);
				}
			}
		}
	}
	return (0);
}

static void			ft_get_shadow(t_data *d)
{
	d->r -= d->r * 0.3;
	d->g -= d->g * 0.3;
	d->b -= d->b * 0.3;
}

void				ft_find_color(double alpha, t_data *d, int obj)
{
	int				i;
	t_vector		inter;
	t_vector		normal;
	double			alpha_inter;

	i = -1;
	d->r = d->objects[obj].material.r;
	d->g = d->objects[obj].material.g;
	d->b = d->objects[obj].material.b;
	inter = ft_vector_intercept(d->cam.dir, d->cam.pos, alpha);
	normal = ft_get_normal(d->objects[obj], inter);
	while (++i < d->nb_lights)
	{
		d->lights[i].dir = ft_vector_sub(d->lights[i].pos, inter);
		d->lights[i].dir = ft_vector_normalize(d->lights[i].dir);
		alpha_inter = ft_find_alpha(d->lights[i].pos, inter);
		if (!ft_search_inter(d, i, alpha_inter, obj))
			ft_get_color(d->objects[obj], d, i, normal);
		else
			ft_get_shadow(d);
	}
}
