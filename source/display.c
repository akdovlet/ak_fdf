/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:57 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 19:13:33 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

int	is_within_bounds(int x, int y)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return (0);
	return (1);
}

void	ak_mlx_pixel_put(t_img *data, double dx, double dy, unsigned int color)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)round(dx);
	y = (int)round(dy);
	if (!is_within_bounds(x, y))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
