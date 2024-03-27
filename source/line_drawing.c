/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:47:41 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 19:06:54 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

double	ft_max(double n, double n2)
{
	if (n > n2)
		return (n);
	return (n2);
}

double	bigger(double n, double n2)
{
	if (n >= n2)
		return (1);
	return (-1);
}

void	draw_line(t_pixel p1, t_pixel p2, t_img *img)
{
	t_bres	math;
	int		i;
	int		len;

	i = 0;
	math.dx = fabs(p2.x[1] - p1.x[1]);
	math.dy = fabs(p2.y[1] - p1.y[1]);
	len = ft_max(math.dx, math.dy);
	math.sx = bigger(p2.x[1], p1.x[1]);
	math.sy = bigger(p2.y[1], p1.y[1]);
	math.err = math.dx - math.dy;
	while (i < len)
	{
		ak_mlx_pixel_put(img, p1.x[1], p1.y[1], \
			color_gradient(p1.color, p2.color, len, i));
		if (2 * math.err > -math.dy)
		{
			math.err -= math.dy;
			p1.x[1] += math.sx;
		}
		if (2 * math.err < math.dx)
		{
			math.err += math.dx;
			p1.y[1] += math.sy;
		}
		i++;
	}
}
