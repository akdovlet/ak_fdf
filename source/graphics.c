/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/02/23 19:30:28 by akdovlet         ###   ########.fr       */
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

int	handle_no_event(t_mlx *mlx)
{
	return (0);
}

int handle_input(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	return (0);
}


void	init_data(t_mlx *mlx, t_img *img)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Fil de Fer");
	img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

int	file_and_parse(char *av, t_grid *grid)
{
	int	fd;
	t_list	*lst;

	*grid = (t_grid){};
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

//main to display window
int main(int ac, char **av)
{
	t_img	img;
	t_mlx	mlx;
	t_grid	grid;

	if (ac != 2)
		return (0);
	file_and_parse(av[1], &grid);
	init_data(&mlx, &img);
	gap_manager(&grid);
	draw_function(&mlx, &img, &grid);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop_hook(mlx.mlx, &handle_no_event, &mlx);
	mlx_key_hook(mlx.win, &handle_input, &mlx);
	// mlx_hook(mlx.win, 2, 65307, key_hook, &mlx);
	// mlx_key_hook(mlx.win, zoom, &mlx);
	// mlx_hook(mlx.win, 33, 1L<<9, close_window, &mlx);
	mlx_loop(mlx.mlx);
	mlx_loop_end(mlx.mlx);
	pixel_clear(grid.pixel, grid.rows);
	mlx_destroy_image(mlx.mlx, img.img);
	mlx_destroy_display(mlx.mlx);
	return (0);
}
