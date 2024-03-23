/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:11:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/23 19:37:58 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "X11/keysym.h"

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		data->grid.scaling *= 1.3;
	}
	else if (button == 5)
	{
		if (data->grid.scaling > 0)
			data->grid.scaling /= 1.3;
		else
			return (0);
	}
	return (0);
}

void	handle_input(t_data *data)
{
	mlx_key_hook(data->mlx.win_ptr, key_hook, data);
	mlx_mouse_hook(data->mlx.win_ptr, mouse_hook, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, x_button, data);
}

int	key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx.mlx_ptr);
	else if (keysym == XK_Shift_L)
		data->grid.z += 0.1;
	else if (keysym == XK_Control_L)
		data->grid.z -= 0.1;
	else if (keysym == XK_Left)
		data->grid.x_offset -= 35;
	else if (keysym == XK_Right)
		data->grid.x_offset += 35;
	else if (keysym == XK_Up)
		data->grid.y_offset -= 35;
	else if (keysym == XK_Down)
		data->grid.y_offset += 35;
	else if (keysym == XK_a)
		data->grid.x_iso -= 5;
	else if (keysym == XK_d)
		data->grid.x_iso += 5;
	else if (keysym == XK_w)
		data->grid.y_iso -= 5;
	else if (keysym == XK_s)
		data->grid.y_iso += 5;
	else if (keysym == XK_r)
		set_values(&data->grid);
	else if (keysym == XK_k)
		data->grid.z_iso += 10;
	else if (keysym == XK_l)
		data->grid.z_iso -= 10;
	return (0);
}

int	x_button(t_data *data)
{
	mlx_loop_end(data->mlx.mlx_ptr);
	return (0);
}
