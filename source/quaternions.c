/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:47:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/29 13:04:24 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_quat	quat_init(double w, double x, double y, double z)
{
	t_quat	q;

	q.w = w;
	q.x = x;
	q.y = y;
	q.z = z;
	return (q);
}

t_quat	quat_multiply(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (result);
}

t_quat	quat_conjugate(t_quat q)
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
	t_quat	p;
	t_quat	result;

	p.w = 0;
	p.x = pixel->x[0];
	p.y = pixel->y[0];
	p.z = pixel->z[0];
	result = quat_multiply(q, quat_multiply(p, quat_conjugate(q)));
	pixel->x[1] = result.x;
	pixel->y[1] = result.y;
	pixel->z[1] = result.z;
}

void	quat_rotate_2(t_quat q, t_pixel *pixel)
{
	t_quat	p;
	t_quat	result;

	p.w = 0;
	p.x = pixel->x[1];
	p.y = pixel->y[1];
	p.z = pixel->z[1];
	result = quat_multiply(q, quat_multiply(p, quat_conjugate(q)));
	pixel->x[1] = result.x;
	pixel->y[1] = result.y;
	pixel->z[1] = result.z;
}
