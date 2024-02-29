/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/02/29 20:23:34 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	centering(t_grid *grid)
{
	int	i;
	int	j;
	int	x_offset;
	int	y_offset;

	i = 0;
	x_offset = (WIDTH - (grid->pixel[grid->lines - 1][grid->rows - 1].x - grid->pixel[0][0].x)) / 2;
	y_offset = (HEIGHT - (grid->pixel[grid->lines - 1][grid->rows - 1].y - grid->pixel[0][0].y)) / 2;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			grid->pixel[i][j].x += x_offset;
			grid->pixel[i][j].y += y_offset;
			j++;
		}
		i++;
	}
}

void	iso_projo(t_grid *grid)
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
			grid->pixel[i][j].x *= grid->gap;
            grid->pixel[i][j].y *= grid->gap;
			grid->pixel[i][j].x = (int)((grid->pixel[i][j].x - grid->pixel[i][j].y) * isox);
			grid->pixel[i][j].y = (int)((grid->pixel[i][j].y + grid->pixel[i][j].x - 2
			 * grid->pixel[i][j].z) * isoy);
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

void	draw_function(t_mlx *mlx, t_img *img, t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	iso_projo(grid);
	centering(grid);
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			ak_mlx_pixel_put(img, grid->pixel[i][j].x, grid->pixel[i][j].y, grid->pixel[i][j].color);
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
	pixel_clear(grid->pixel, grid->rows);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		clear_all(&data->grid, &data->mlx);
		exit(0);
	}
	else if (keycode == 61)
	{
		printf("gap in main funct is: %d\n", data->grid.gap);
		data->grid.gap += 1;
		draw_function(&data->mlx, &data->mlx.img, &data->grid);
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
	file_and_parse(av[1], &data.grid);
	init_data(&data.mlx, &data.mlx.img);
	gap_manager(&data.grid);
	draw_function(&data.mlx, &data.mlx.img, &data.grid);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mlx.img.img_ptr, 0, 0);
	mlx_loop_hook(data.mlx.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.mlx.win_ptr, 2, 65307, key_hook, &data);
	printf("gap after hook is: %d\n", data.grid.gap);
	mlx_loop(data.mlx.mlx_ptr);
	// pixel_clear(data.grid.pixel, data.grid.rows);
	// mlx_destroy_image(data.mlx.mlx, data.mlx.img.img);
	// mlx_destroy_window(data.mlx.mlx, data.mlx.win);
	// mlx_destroy_display(data.mlx.mlx);
	return (0);
}
