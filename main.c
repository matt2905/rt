/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/10 13:52:27 by mmartin           #+#    #+#             */
/*   Updated: 2014/02/16 09:55:51 by mmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <libft.h>
#include "ft_rtv1.h"

static int		ft_key_hook(int keycode)
{
	if (keycode == 65307)
		exit(EXIT_SUCCESS);
	return (1);
}

static int		ft_expose_hook(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (1);
}

static void		ft_get_data(t_data *d)
{
	int		bpp;
	int		sizeline;
	int		endian;

	d->data = mlx_get_data_addr(d->img, &bpp, &sizeline, &endian);
	d->bpp = bpp;
	d->sizeline = sizeline;
	d->endian = endian;
}

int				main(int argc, char **argv)
{
	t_data	d;
	t_file	*file;

	file = NULL;
	if (argc != 2)
		ft_putendl_fd("Usage: ./rt_v1 <scene>", 2);
	else
	{
		ft_init(&file, &d, argv[1]);
		ft_parsing(file, &d);
		ft_get_light(file, &d);
		if ((d.mlx = mlx_init()) == NULL)
			return (-1);
		if ((d.win = mlx_new_window(d.mlx, d.width, d.height, "RTv1")) == NULL)
			return (-1);
		if ((d.img = mlx_new_image(d.mlx, d.width, d.height)) == NULL)
			return (-1);
		ft_get_data(&d);
		ft_raytracing(&d);
		mlx_key_hook(d.win, &ft_key_hook, &d);
		mlx_expose_hook(d.win, &ft_expose_hook, &d);
		mlx_loop(d.mlx);
	}
	return (0);
}