/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:24:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 18:37:36 by akdovlet         ###   ########.fr       */
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
