/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:56:52 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/31 15:22:12 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	matrix_x(double rotation[3][3], double angle)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(angle * M_PI / 180);
	sin_theta = sin(angle * M_PI / 180);
	rotation[0][0] = 1;
	rotation[0][1] = 0;
	rotation[0][2] = 0;
	rotation[1][0] = 0;
	rotation[1][1] = cos_theta;
	rotation[1][2] = -sin_theta;
	rotation[2][0] = 0;
	rotation[2][1] = sin_theta;
	rotation[2][2] = cos_theta;
}

void	matrix_y(double rotation[3][3], double angle)
{
	double	cos_theta;
	double	sin_theta;

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
}

void	matrix_z(double rotation[3][3], double angle)
{
	double	cos_theta;
	double	sin_theta;

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
}
