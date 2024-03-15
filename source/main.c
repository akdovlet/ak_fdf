/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:47 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/15 17:20:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int ac, char **av)
{
	t_data data;
	int		err;

	if (ac != 2)
		return (0);
	if (file_and_parse(av[1], &data.grid) <= 0)
		return (0);
	init_data(&data.mlx, &data.mlx.img);
	set_values(&data.grid);
	// draw_frame(&data);
	mlx_loop_hook(data.mlx.mlx_ptr, draw_frame, &data);
	handle_input(&data);
	mlx_loop(data.mlx.mlx_ptr);
	clear_all(&data.grid, &data.mlx);
	return (0);
}
