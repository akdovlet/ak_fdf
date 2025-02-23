/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:11:44 by akdovlet          #+#    #+#             */
/*   Updated: 2025/02/23 01:02:19 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "X11/keysym.h"
#include "X11/X.h"

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->grid.scaling *= 1.2;
	else if (button == 5)
	{
		if (data->grid.scaling > 0)
			data->grid.scaling /= 1.2;
		else
			return (0);
	}
	return (0);
}

void	handle_input(t_data *data)
{
	// mlx_key_hook(data->mlx.win_ptr, key_hook, data);
	mlx_mouse_hook(data->mlx.win_ptr, mouse_hook, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, x_button, data);
	mlx_hook(data->mlx.win_ptr, KeyPress, KeyPressMask, key_hook, data);
}

void	controller_one(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx.mlx_ptr);
	else if (keysym == XK_Shift_L)
		data->grid.z += 0.1;
	else if (keysym == XK_Control_L)
		data->grid.z -= 0.1;
	else if (keysym == XK_Left)
		data->grid.x_offset -= 10;
	else if (keysym == XK_Right)
		data->grid.x_offset += 10;
	else if (keysym == XK_Up)
		data->grid.y_offset -= 10;
	else if (keysym == XK_Down)
		data->grid.y_offset += 10;
}

int	key_hook(int keysym, t_data *data)
{
	controller_one(keysym, data);
	if (keysym == XK_a)
		data->grid.y_iso -= 10;
	else if (keysym == XK_d)
		data->grid.y_iso += 10;
	else if (keysym == XK_w)
		data->grid.x_iso += 10;
	else if (keysym == XK_s)
		data->grid.x_iso -= 10;
	else if (keysym == XK_k)
		data->grid.z_iso += 10;
	else if (keysym == XK_l)
		data->grid.z_iso -= 10;
	else if (keysym == XK_r)
		set_values(&data->grid);
	else if (keysym == XK_f)
		flat_values(&data->grid);
	return (0);
}

int	x_button(t_data *data)
{
	mlx_loop_end(data->mlx.mlx_ptr);
	return (0);
}
