/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:47:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/26 14:18:48 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_quat	quat_init(double w, double x, double y, double z)
{
	t_quat q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;
	return q;
}

t_quat quat_multiply(t_quat q1, t_quat q2)
{
	t_quat result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    return (result);
}

t_quat quat_conjugate(t_quat q)
{
	t_quat	result;

	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return (result);
}

void	quat_rotate(t_quat q, t_pixel *pixel)
{
	t_quat p = {0, pixel->x[0], pixel->y[0], pixel->z[0]};
	t_quat result;

	result = quat_multiply(q, quat_multiply(p, quat_conjugate(q)));
	pixel->x[1] = result.x;
	pixel->y[1] = result.y;
	pixel->z[1] = result.z;
}

void	quat_rotate_2(t_quat q, t_pixel *pixel)
{
	t_quat p = {0, pixel->x[1], pixel->y[1], pixel->z[1]};
	t_quat result;

	result = quat_multiply(q, quat_multiply(p, quat_conjugate(q)));
	pixel->x[1] = result.x;
	pixel->y[1] = result.y;
	pixel->z[1] = result.z;
}

t_quat quat_rotate_x(double angle)
{
	double half_theta;

	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), sin(half_theta), 0, 0));
}

t_quat quat_rotate_y(double angle)
{
	double half_theta;
	
	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), 0, sin(half_theta), 0));
}

t_quat quat_rotate_z(double angle)
{
	double half_theta;

	half_theta = (angle * M_PI / 180) / 2;
	return (quat_init(cos(half_theta), 0, 0, sin(half_theta)));
}

t_quat quat_normalize(t_quat q)
{
	double range;

	range = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	q.w /= range;
	q.x /= range;
	q.y /= range;
	q.z /= range;
	return (q);
}

