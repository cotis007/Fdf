/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:46:30 by cotis             #+#    #+#             */
/*   Updated: 2020/03/03 12:54:25 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"




int			keys(int key, data *a)
{
	int		bpp;
	int		sl;
	int		end;

	if (key == 53)
		exit(0);
	if (key == 126)
		a->shift_y -= 10;
	if (key == 125)
		a->shift_y += 10;
	if (key == 123)
		a->shift_x -= 10;
	if (key == 124)
		a->shift_x += 10;
	if (key == 27)
		a->zoom -= 0.5;
	if (key == 24)
		a->zoom += 0.5;
	a->img_ptr = mlx_new_image(a->mlx_ptr, 1920, 1080);
	if ((a->str = (int*)mlx_get_data_addr(a->img_ptr, &bpp, &sl, &end)) == NULL)
		errors (-2);
	draw(a);
	mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0);
	mlx_destroy_image(a->mlx_ptr, a->img_ptr);
	return(key);
}

int			image(data *a)
{
	int		bpp;
	int		sl;
	int		end;

	a->shift_x = 960;
	a->shift_y = 540;
	a->zoom = 1;
	if ((a->mlx_ptr = mlx_init()) == NULL)
		errors(-2);
	if ((a->win_ptr = mlx_new_window(a->mlx_ptr, 1920, 1080, "Love")) == NULL)
		errors (-2);
	if ((a->img_ptr = mlx_new_image(a->mlx_ptr, 1920, 1080)) == NULL)
		errors (-2);
	if ((a->str = (int *)mlx_get_data_addr(a->img_ptr, &bpp, &sl, &end)) == NULL)
		errors (-2);
	draw(a);
	if (mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0) == NULL)
		errors (-2);
	mlx_hook(a->win_ptr, 3, 0, keys, a); 
	mlx_loop(a->mlx_ptr);
	return (0);
}

void		draw(data *a)
{
	int		x;
	int		y;

	y = 0;
	while (y < a->y_max)
	{
		x = 0;
		while (x < a->x_max)
		{
			if (x < a->x_max - 1)
				algoritm(x, y, x + 1, y, a->str, a);
			if (y < a->y_max - 1)
				algoritm(x, y, x, y + 1, a->str, a);
			x++;
		}
		y++;
	}
}

static void			iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}


void		algoritm(int x1, int y1, int x2, int y2, int *str, data *a)
{
    t_put   fdf;

	fdf.z1 = a->z_list[(int)y1][(int)x1];
	fdf.z2 = a->z_list[(int)y2][(int)x2];

	x1 *= a->zoom;
	y1 *= a->zoom;
	x2 *= a->zoom;
	y2 *= a->zoom;
	
	a->color = (fdf.z1) ?  0xFFFFFF : 0xFF0000;

	iso(&x1, &y1, fdf.z1);
	iso(&x2, &y2, fdf.z2);

	x1 += a->shift_x;
	y1 += a->shift_y;
	x2 += a->shift_x;
	y2 += a->shift_y;

	fdf.deltaX = abs(x2 - x1);
	fdf.deltaY = abs(y2 - y1);
	fdf.signX = x1 < x2 ? 1 : -1;
	fdf.signY = y1 < y2 ? 1 : -1;
	fdf.error = fdf.deltaX - fdf.deltaY;

	str[x2 + y2 * 1920] = a->color;
	while(x1 != x2 || y1 != y2)
	{
		str[x1 + y1 * 1920] = a->color;
		fdf.error2 = fdf.error * 2;
		if(fdf.error2 > -(fdf.deltaY))
		{
			fdf.error -= fdf.deltaY;
			x1 += fdf.signX;
		}
		if(fdf.error2 < fdf.deltaX)
		{
			fdf.error += fdf.deltaX;
			y1 += fdf.signY;
		}
	}
}
