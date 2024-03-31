/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:08:46 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/28 12:09:49 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_quat	quat_rotate_x(double angle)
{
	double	half_theta;

	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), sin(half_theta), 0, 0));
}

t_quat	quat_rotate_y(double angle)
{
	double	half_theta;

	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), 0, sin(half_theta), 0));
}

t_quat	quat_rotate_z(double angle)
{
	double	half_theta;

	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), 0, 0, sin(half_theta)));
}

t_quat	quat_normalize(t_quat q)
{
	double	range;

	range = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= range;
	q.x /= range;
	q.y /= range;
	q.z /= range;
	return (q);
}
