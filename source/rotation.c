/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:01:12 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 13:41:26 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// double	**matrix_x(double *angle)
// {
// 	double	rotation[3][3];
// 	double cos_theta;
// 	double sin_theta;

// 	cos_theta = cos(angle * M_PI / 180);
// 	sin_theta = sin(angle * M_PI / 180);
// 	rotation[0][0] = 1;
// 	rotation[0][1] = 0;
// 	rotation[0][2] = 0;
// 	rotation[1][0] = 0;
// 	rotation[1][1] = cos_theta;
// 	rotation[1][2] = -sin_theta;
// 	rotation[2][0] = 0;
// 	rotation[2][1] = sin_theta;
// 	rotation[2][2] = cos_theta;
// 	return (rotation);
// }

void	rotate_x(t_pixel *pixel, double angle, double z_scale)
{
	double	rotation[3][3];
	double n_p[3];
	double point[3];
	double cos_theta;
	double sin_theta;
	int	i;
	int	j;

	i = 0;
	point[0] = pixel->x[0];
	point[1] = pixel->y[0];
	point[2] = pixel->z[0] * z_scale;
	cos_theta = cos(angle * M_PI / (double)180);
	sin_theta = sin(angle * M_PI / (double)180);
	rotation[0][0] = 1;
	rotation[0][1] = 0;
	rotation[0][2] = 0;
	rotation[1][0] = 0;
	rotation[1][1] = cos_theta;
	rotation[1][2] = -sin_theta;
	rotation[2][0] = 0;
	rotation[2][1] = sin_theta;
	rotation[2][2] = cos_theta;
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
	double n_p[3];
	double point[3];
	double cos_theta;
	double sin_theta;
	int	i;
	int	j;

	i = 0;
	point[0] = pixel->x[1];
	point[1] = pixel->y[1];
	point[2] = pixel->z[1];
	cos_theta = cos(angle * M_PI / (double)180);
	sin_theta = sin(angle * M_PI / (double)180);
	rotation[0][0] = cos_theta;
	rotation[0][1] = 0;
	rotation[0][2] = sin_theta;
	rotation[1][0] = 0;
	rotation[1][1] = 1;
	rotation[1][2] = 0;
	rotation[2][0] = -sin_theta;
	rotation[2][1] = 0;
	rotation[2][2] = cos_theta;
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
	double	cos_theta;
	double	sin_theta;
	int	i;
	int	j;

	i = 0;
	point[0] = pixel->x[1];
	point[1] = pixel->y[1];
	point[2] = pixel->z[1];
	cos_theta = cos(angle * M_PI / (double)180);
	sin_theta = sin(angle * M_PI / (double)180);
	rotation[0][0] = cos_theta;
	rotation[0][1] = -sin_theta;
	rotation[0][2] = 0;
	rotation[1][0] = sin_theta;
	rotation[1][1] = cos_theta;
	rotation[1][2] = 0;
	rotation[2][0] = 0;
	rotation[2][1] = 0;
	rotation[2][2] = 1;
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
