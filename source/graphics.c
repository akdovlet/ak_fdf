/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/23 19:46:48 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <X11/keysym.h>


int	is_within_bounds(int x, int y)
{
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
        return (0);
	return (1);
}

void    ak_mlx_pixel_put(t_img *data, double dx, double dy, unsigned int color)
{
    char    *dst;
	int		x;
	int		y;
	
	x = (int)round(dx);
	y = (int)round(dy);
    if (!is_within_bounds(x, y))
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
	int	center_x;
	int	center_y;

	y = 0;
	center_x = (WIDTH - (pixel[grid->lines - 1][grid->rows - 1].x[1] - pixel[0][0].x[1])) / 2;
	center_y = (HEIGHT - (pixel[grid->lines - 1][grid->rows - 1].y[1] - pixel[0][0].y[1])) / 2;
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			pixel[y][x].x[1] += grid->x_offset + center_x;
			pixel[y][x].y[1] += grid->y_offset + center_y;
			x++;
		}
		y++;
	}
}

void	set_values(t_grid *grid)
{
	grid->x_offset = 0;
	grid->y_offset = 0;
	grid->scaling = gap_manager(grid);
	grid->x_iso = 1;
	grid->y_iso = 1;
	grid->z_iso = 1;
	grid->z = 1;
}

void	iso_projo(t_grid *grid, t_pixel **pixel)
{
	int		y;
	int		x;
	double angle_x;
	double angle_y;
	double angle_z;

	y = 0;
	angle_x = fmod(grid->x_iso, 360);
	angle_y = fmod(grid->y_iso, 360);
	angle_z = fmod(grid->z_iso, 360);
	while (y < grid->lines)
	{
		x = 0;
		while (x < grid->rows)
		{
			// pixel[y][x].x[1] = grid->scaling * ((x - y) * (cos(angle_x * M_PI / 180)));
			// pixel[y][x].y[1] = grid->scaling * (((x + y) * (sin(angle_y * M_PI / 180))) - (pixel[y][x].z[0] * grid->z));
			rotate_x(&pixel[y][x], angle_y * M_PI / (double)180,grid->z);
			rotate_y(&pixel[y][x], angle_x * M_PI/ (double)180);
			rotate_z(&pixel[y][x], angle_z * M_PI / (double)180);
			pixel[y][x].x[1] *= grid->scaling;
			pixel[y][x].y[1] *= grid->scaling;
			x++;
		}
		y++;
	}
	centering(grid, grid->pixel);
}

double	ft_max(double n, double n2)
{
	if (n > n2)
		return (n);
	return (n2);
}
double	bigger(double n, double n2)
{
	if (n >= n2)
		return (1);
	return (-1);
}
void    draw_line2(t_pixel p1, t_pixel p2, t_img *img)
{
	t_bres	math;
	int	i;
	int	len;
	int	distance;
	int	pixel;
	i = 0;
    math.dx = fabs(p2.x[1] - p1.x[1]);
    math.dy = fabs(p2.y[1] - p1.y[1]);
	len = ft_max(math.dx, math.dy);
	// distance = sqrt((math.dx * math.dx) + (math.dy * math.dy));
	// pixel = distance;
    math.sx = bigger(p2.x[1], p1.x[1]);
    math.sy = bigger(p2.y[1], p1.y[1]);
    math.err = math.dx - math.dy;
	// printf("color of p1 is: %#x\n", p1.color);
	// printf("color of p2 is: %#x\n", p2.color);
    while (i < len)
	{
        ak_mlx_pixel_put(img, p1.x[1], p1.y[1], color_gradient(p1, p2, len, i));
        if (2 * math.err > -math.dy) {
            math.err -= math.dy;
            p1.x[1] += math.sx;
        }
        if (2 * math.err < math.dx) {
            math.err += math.dx;
            p1.y[1] += math.sy;
        }
		i++;
    }
}
#include <stdio.h>
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
			if (j + 1 < grid->rows && (is_within_bounds(pixel[i][j].x[1], pixel[i][j].y[1])
				|| is_within_bounds(pixel[i][j + 1].x[1], pixel[i][j + 1].y[1])))
				draw_line2(pixel[i][j], pixel[i][j + 1], img);
			if (i + 1 < grid->lines && (is_within_bounds(pixel[i][j].x[1], pixel[i][j].y[1])
				|| is_within_bounds(pixel[i + 1][j].x[1], pixel[i + 1][j].y[1])))
				draw_line2(pixel[i][j], pixel[i + 1][j], img);
			j++;
		}
		i++;
	}
}

int	init_mlx(t_mlx *mlx, t_img *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (ft_printf("Failed mlx init"), 0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Fil de Fer");
	if (!mlx->win_ptr)
		return (ft_printf("Failed win creation"), 0);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return (ft_printf("Failed img creation"), 0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (ft_printf("Failed img adress init"), 0);
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
	double	i;
	double	j;

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
