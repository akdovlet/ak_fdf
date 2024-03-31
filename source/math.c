/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:24:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/30 19:34:29 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

double	gap_manager(t_grid *grid)
{
	float	ewidth;
	float	eheight;

	ewidth = grid->rows + (grid->rows - 1) * 2;
	eheight = grid->lines + (grid->lines - 1) * 2;
	grid->scaling = fminf((float)WIDTH / ewidth, (float)HEIGHT / eheight);
	return (grid->scaling);
}

void	centering(t_grid *grid, t_pixel **pixel)
{
	int	y;
	int	x;
	int	center_x;
	int	center_y;

	y = 0;
	center_x = (WIDTH - (pixel[grid->lines - 1][grid->rows - 1].x[1] \
		- pixel[0][0].x[1])) / 2;
	center_y = (HEIGHT - (pixel[grid->lines - 1][grid->rows - 1].y[1] \
		- pixel[0][0].y[1])) / 2;
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			pixel[y][x].x[1] += grid->x_offset + center_x;
			pixel[y][x].y[1] += grid->y_offset + center_y;
			x++;
		}
		y++;
	}
}

void	rotation_matrix(t_grid *grid, t_pixel **pixel)
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
			rotate_z(&pixel[y][x], angle_z);
			rotate_x(&pixel[y][x], angle_x, grid->z);
			rotate_y(&pixel[y][x], angle_y);
			pixel[y][x].x[1] *= grid->scaling;
			pixel[y][x].y[1] *= grid->scaling;
			x++;
		}
		y++;
	}
	centering(grid, grid->pixel);
}
