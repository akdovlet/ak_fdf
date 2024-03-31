/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:50:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/29 13:07:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parsing.h"

int	domino_1(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

int	domino_2(void *mlx, void *win)
{
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

int	domino_3(void *mlx, void *img, void *win)
{
	mlx_destroy_image(mlx, img);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

int	init_mlx(t_mlx *mlx, t_img *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (ft_printf("Failed mlx init\n"), 0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fil de Fer");
	if (!mlx->win_ptr)
		return (domino_1(mlx->mlx_ptr));
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return (domino_2(mlx->mlx_ptr, mlx->win_ptr));
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	if (!img->addr)
		return (domino_3(mlx->mlx_ptr, img->img_ptr, mlx->win_ptr));
	return (1);
}

void	clear_all(t_grid *grid, t_mlx *mlx)
{
	pixel_clear(grid->pixel, grid->lines);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	ft_printf("AK out!\n");
}
