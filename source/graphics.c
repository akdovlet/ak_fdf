/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/15 20:26:32 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <X11/keysym.h>

void    ak_mlx_pixel_put(t_img *data, int x, int y, unsigned int color)
{
    char    *dst;

    if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
double	gap_manager(t_grid *grid)
{
	float ewidth;
	float eheight;

	ewidth = grid->rows + (grid->rows - 1) * 2;
	eheight = grid->lines + (grid->lines - 1) * 2;
	grid->scaling = fminf((float)WIDTH / ewidth, (float)HEIGHT / eheight);
	return (grid->scaling);
}

void	centering(t_grid *grid, t_pixel **pixel)
{
	int	y;
	int	x;

	y = 0;
	grid->x_offset = (WIDTH - (pixel[grid->lines - 1][grid->rows - 1].x[1] - pixel[0][0].x[1])) / 2;
	grid->y_offset = (HEIGHT - (pixel[grid->lines - 1][grid->rows - 1].y[1] - pixel[0][0].y[1])) / 2;
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			pixel[y][x].x[1] += grid->x_offset;
			pixel[y][x].y[1] += grid->y_offset;
			x++;
		}
		y++;
	}
}

void	set_values(t_grid *grid)
{
	grid->scaling = gap_manager(grid);
	grid->x_iso = 1;
	grid->y_iso = 1;
	grid->z = 1;
}


void	iso_projo(t_grid *grid, t_pixel **pixel)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			pixel[y][x].x[1] = grid->scaling * ((x - y) * (cos(M_PI / 6)));
			pixel[y][x].y[1] = grid->scaling *((x + y) * (grid->y_iso * sin(M_PI / 6)) - (pixel[y][x].z[0] * grid->z));
			x++;
		}
		y++;
	}
	centering(grid, grid->pixel);
}


void    draw_line2(t_pixel p1, t_pixel p2, t_img *img)
{

    int dx = abs((int)p2.x[1] - (int)p1.x[1]);
    int dy = abs((int)p2.y[1] - (int)p1.y[1]);
    int sx = ((int)p2.x[1] >= (int)p1.x[1]) ? 1 : -1;
    int sy = ((int)p2.y[1] >= (int)p1.y[1]) ? 1 : -1;
    int err = dx - dy;
	int i = 0;
	int len = (dx > dy) ? dx : dy;

    while (i < len)
	{
        ak_mlx_pixel_put(img, (int)p1.x[1], (int)p1.y[1], p1.color);
        if (2 * err > -dy) {
            err -= dy;
            p1.x[1] += sx;
        }
        if (2 * err < dx) {
            err += dx;
            p1.y[1] += sy;
        }
		i++;
    }
}


void	draw_function(t_mlx *mlx, t_img *img, t_grid *grid, t_pixel **pixel)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			ak_mlx_pixel_put(img, pixel[i][j].x[1], pixel[i][j].y[1], pixel[i][j].color);
			if (j +1 < grid->rows)
				draw_line2(pixel[i][j], pixel[i][j + 1], img);
			if (i + 1 < grid->lines)
				draw_line2(pixel[i][j], pixel[i + 1][j], img);
			j++;
		}
		i++;
	}
}

void	init_data(t_mlx *mlx, t_img *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return ;
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fil de Fer");
	if (!mlx->win_ptr)
		return ;
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return ;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
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

int	draw_frame(t_data *data)
{
	background(&data->mlx.img);
	iso_projo(&data->grid, data->grid.pixel);
	draw_function(&data->mlx, &data->mlx.img, &data->grid, data->grid.pixel);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	return (0);
}

void	background(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ak_mlx_pixel_put(img, j, i, 0);
			j++;
		}
		i++;
	}
}
