/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:01:12 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/30 19:10:15 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_pixel *pixel, double angle, double z_scale)
{
	double	rotation[3][3];
	double	n_p[3];
	double	point[3];
	int		i;
	int		j;

	i = 0;
	point[0] = pixel->x[1];
	point[1] = pixel->y[1];
	point[2] = pixel->z[1] * z_scale;
	matrix_x(rotation, angle);
	while (i < 3)
	{
		n_p[i] = 0;
		j = 0;
		while (j < 3)
		{
			n_p[i] += (rotation[i][j] * point[j]);
			j++;
		}
		i++;
	}
	pixel->x[1] = n_p[0];
	pixel->y[1] = n_p[1];
	pixel->z[1] = n_p[2];
}

void	rotate_y(t_pixel *pixel, double angle)
{
	double	rotation[3][3];
	double	n_p[3];
	double	point[3];
	int		i;
	int		j;

	i = 0;
	point[0] = pixel->x[1];
	point[1] = pixel->y[1];
	point[2] = pixel->z[1];
	matrix_y(rotation, angle);
	while (i < 3)
	{
		n_p[i] = 0;
		j = 0;
		while (j < 3)
		{
			n_p[i] += rotation[i][j] * point[j];
			j++;
		}
		i++;
	}
	pixel->x[1] = n_p[0];
	pixel->y[1] = n_p[1];
	pixel->z[1] = n_p[2];
}

void	rotate_z(t_pixel *pixel, double angle)
{
	double	rotation[3][3];
	double	n_p[3];
	double	point[3];
	int		i;
	int		j;

	i = 0;
	point[0] = pixel->x[0];
	point[1] = pixel->y[0];
	point[2] = pixel->z[0];
	matrix_z(rotation, angle);
	while (i < 3)
	{
		n_p[i] = 0;
		j = 0;
		while (j < 3)
		{
			n_p[i] += rotation[i][j] * point[j];
			j++;
		}
		i++;
	}
	pixel->x[1] = n_p[0];
	pixel->y[1] = n_p[1];
	pixel->z[1] = n_p[2];
}
