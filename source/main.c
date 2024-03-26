/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:18:47 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/24 15:36:01 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (0);
	if (!file_and_parse(av[1], &data.grid))
		return (0);
	if (!init_mlx(&data.mlx, &data.mlx.img))
		return (ft_printf("init failed\n"), 0);
	set_values(&data.grid);
	mlx_loop_hook(data.mlx.mlx_ptr, draw_frame, &data);
	handle_input(&data);
	mlx_loop(data.mlx.mlx_ptr);
	clear_all(&data.grid, &data.mlx);
	return (0);
}
