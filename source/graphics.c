/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/05 18:26:39 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// void	ak_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
// {
// 	char	*dst;
// 	size_t	y_offset;
// 	size_t	x_offset;

// 	if (x < 0 || y < 0)
// 		return ;
// 	y_offset = y * img->line_length;
// 	x_offset = x * (img->bits_per_pixel / 8);
// 	dst = &img->addr[y_offset + x_offset];
// 	*(unsigned int*)dst = color;
// }

void    ak_mlx_pixel_put(t_img *data, int x, int y, unsigned int color)
{
    char    *dst;

    if (x > WIDTH || y > HEIGHT || x <= 0 || y <= 0)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	centering(t_grid *grid, t_pixel **pixel)
{
	int	i;
	int	j;
	int	x_offset;
	int	y_offset;

	i = 0;
	x_offset = (WIDTH - (pixel[grid->lines - 1][grid->rows - 1].x - pixel[0][0].x)) / 2;
	y_offset = (HEIGHT - (pixel[grid->lines - 1][grid->rows - 1].y - pixel[0][0].y)) / 2;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			pixel[i][j].x += x_offset;
			pixel[i][j].y += y_offset;
			j++;
		}
		i++;
	}
}

void	iso_projo(t_grid *grid, t_pixel **pixel)
{
	int		i;
	int		j;
	float	isox;
	float	isoy;
	float	angle = 0;

	i = 0;
	isox = (M_PI / 4) + angle;
	isoy = (M_PI / 4) - angle;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			pixel[i][j].x *= grid->gap;
			pixel[i][j].y *= grid->gap;
			pixel[i][j].x = (int)((pixel[i][j].x - pixel[i][j].y) * isox);
			pixel[i][j].y = (int)((pixel[i][j].y + pixel[i][j].x - 2
			 * pixel[i][j].z) * isoy);
			j++;
		}
		i++;
	}
}

void	gap_manager(t_grid *grid)
{
	int	spacing;
	int	maxgap;

	spacing = (WIDTH + HEIGHT) / (grid->lines + grid->rows);
	if (WIDTH < HEIGHT)
		maxgap = WIDTH / 5;
	else
		maxgap = HEIGHT / 5;
	grid->gap = spacing / 2;
	if (grid->gap < 1)
		grid->gap = 1;
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
			ak_mlx_pixel_put(img, pixel[i][j].x, pixel[i][j].y, pixel[i][j].color);
			j++;
		}
		i++;
	}
}

void	hook_manager(t_img *img, t_mlx *mlx)
{
	// mlx_hook(mlx->win, 2, 65307, key_hook, mlx);
	// mlx_hook(mlx->win, 33, 1L<<9, close_window, mlx);
}

int	handle_no_event(t_data *data)
{
	return (0);
}

t_pixel **copy_pixel(t_pixel **pixel, t_grid *grid)
{
	int	i;
	int	j;
	t_pixel **copy;

	i = 0;
	copy = malloc(sizeof(t_pixel *) * grid->lines);
	if (!copy)
		return (NULL);
	while (i < grid->lines)
	{
		j = 0;
		copy[i] = malloc(sizeof(t_pixel) * grid->rows);
		if (!copy[i])
			return (pixel_clear(copy, i), NULL);		
		while (j < grid->rows)
		{
			copy[i][j].x = pixel[i][j].x;
			copy[i][j].y = pixel[i][j].y;
			copy[i][j].z = pixel[i][j].z;
			copy[i][j].color = pixel[i][j].color;
			j++;
		}
		i++;
	}
	return (copy);
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

int	file_and_parse(char *av, t_grid *grid)
{
	int		fd;
	t_list	*lst;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (-1);
	lst = get_file(fd);
	if (!lst)
		return (-2);
	close(fd);
	if (ak_superlen(lst, &grid->lines, &grid->rows) == -1)
		return (ft_lstclear(&lst, free), ft_printf("Wrong map"), 0);
	grid->pixel = data_parser(lst, grid->lines, grid->rows);
	if (!grid->pixel)
		return (ft_printf("failed grid malloc"), -3);
	ft_lstclear(&lst, free);
	return (1);
}

// typedef struct s_data {
// 	t_mlx	mlx;
// 	t_grid	grid;
// }	t_data;

void	clear_all(t_grid *grid, t_mlx *mlx)
{
	pixel_clear(grid->pixel, grid->lines);
	pixel_clear(grid->copy, grid->lines);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
}

void	clear_image(t_mlx *mlx, t_img *img, t_grid *grid, t_pixel **pixel)
{
	if (!pixel)
		return ;
	int	i;
	int	j;
	
	i = 0;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			ak_mlx_pixel_put(img, pixel[i][j].x, pixel[i][j].y, 0);
			j++;
		}
		i++;
	}
}

void	draw_frame(t_data *data)
{
	data->grid.copy = copy_pixel(data->grid.pixel, &data->grid);
	iso_projo(&data->grid, data->grid.copy);
	centering(&data->grid, data->grid.copy);
	draw_function(&data->mlx, &data->mlx.img, &data->grid, data->grid.copy);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		clear_all(&data->grid, &data->mlx);
		exit(0);
	}
	if (keycode == 61)
	{
		clear_image(&data->mlx, &data->mlx.img, &data->grid, data->grid.copy);
		data->grid.gap += 1;
		draw_frame(data);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

//main to display window
int main(int ac, char **av)
{
	t_data data;
	if (ac != 2)
		return (0);
	if (file_and_parse(av[1], &data.grid) <= 0)
		return (0);
	init_data(&data.mlx, &data.mlx.img);
	gap_manager(&data.grid);
	draw_frame(&data);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mlx.img.img_ptr, 0, 0);
	mlx_loop_hook(data.mlx.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.mlx.win_ptr, 2, 65307, key_hook, &data);
	mlx_loop(data.mlx.mlx_ptr);
	// pixel_clear(data.grid.pixel, data.grid.rows);
	// mlx_destroy_image(data.mlx.mlx, data.mlx.img.img);
	// mlx_destroy_window(data.mlx.mlx, data.mlx.win);
	// mlx_destroy_display(data.mlx.mlx);
	return (0);
}
