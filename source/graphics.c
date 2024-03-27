/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 20:51:04 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <X11/keysym.h>

void	set_values(t_grid *grid)
{
	grid->x_offset = 0;
	grid->y_offset = 0;
	grid->scaling = gap_manager(grid);
	grid->x_iso = 220;
	grid->y_iso = 160;
	grid->z_iso = 160;
	grid->z = 0.1;
}

void	iso_projo(t_grid *grid, t_pixel **pixel)
{
	int		y;
	int		x;
	double	angle_x;
	double	angle_y;
	double	angle_z;

	y = 0;
	angle_x = fmod(grid->x_iso, 360);
	angle_y = fmod(grid->y_iso, 360);
	angle_z = fmod(grid->z_iso, 360);
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			rotate_x(&pixel[y][x], angle_x, grid->z);
			rotate_y(&pixel[y][x], angle_y);
			rotate_z(&pixel[y][x], angle_z);
			pixel[y][x].x[1] *= grid->scaling;
			pixel[y][x].y[1] *= grid->scaling;
			x++;
		}
		y++;
	}
	centering(grid, grid->pixel);
}

// int	line_check(t_grid grid, t_pixel)

void	draw_function(t_img *img, t_grid *grid, t_pixel **pixel)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			ak_mlx_pixel_put(img, pixel[i][j].x[1], pixel[i][j].y[1], pixel[i][j].color);
			if (j + 1 < grid->rows && (is_within_bounds(pixel[i][j].x[1], pixel[i][j].y[1])
				|| is_within_bounds(pixel[i][j + 1].x[1], pixel[i][j + 1].y[1])))
				draw_line(pixel[i][j], pixel[i][j + 1], img);
			if (i + 1 < grid->lines && (is_within_bounds(pixel[i][j].x[1], pixel[i][j].y[1])
				|| is_within_bounds(pixel[i + 1][j].x[1], pixel[i + 1][j].y[1])))
				draw_line(pixel[i][j], pixel[i + 1][j], img);
			j++;
		}
		i++;
	}
}

int	draw_frame(t_data *data)
{
	background(&data->mlx.img);
	iso_projo(&data->grid, data->grid.pixel);
	draw_function(&data->mlx.img, &data->grid, data->grid.pixel);
	mlx_put_image_to_window(data->mlx.mlx_ptr, \
		data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	return (0);
}

void	background(t_img *img)
{
	double	i;
	double	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ak_mlx_pixel_put(img, j, i, 0);
			j++;
		}
		i++;
	}
}
