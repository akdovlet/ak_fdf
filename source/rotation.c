/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:01:12 by akdovlet          #+#    #+#             */
/*   Updated: 2025/02/23 01:36:57 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_pixel *pixel, double angle, double z_scale)
{
	pixel->z[1] *= z_scale;
	pixel->x[1] = pixel->x[1];
	pixel->y[1] = (pixel->y[1] * cos(angle)) + (pixel->z[1] * -sin(angle));
	pixel->z[1] = (pixel->y[1] * sin(angle)) + (pixel->z[1] * cos(angle));
}

void	rotate_y(t_pixel *pixel, double angle)
{
	pixel->x[1] = (pixel->x[1] * cos(angle)) + (pixel->z[1] * sin(angle));
	pixel->y[1] = pixel->y[1];
	pixel->z[1] = (pixel->x[1] * -sin(angle)) + (pixel->z[1] * cos(angle));
}

void	rotate_z(t_pixel *pixel, double angle)
{
	pixel->x[1] = (pixel->x[0] * cos(angle)) + (pixel->y[0] * -sin(angle));
	pixel->y[1] = (pixel->x[0] * sin(angle)) + (pixel->y[0] * cos(angle));
	pixel->z[1] = pixel->z[0];
}
