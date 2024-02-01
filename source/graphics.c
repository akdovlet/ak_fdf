/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/02/01 16:12:28 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_mlx *mlx, t_data *img)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		printf("Over\n");
		exit(1);
	}
	else
		printf("keycode is: %d\n", keycode);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(1);
	return (0);
}

// void	my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
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

void    my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
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
			grid->pixel[i][j].x = (int)((grid->pixel[i][j].x - grid->pixel[i][j].y) * isox);
			grid->pixel[i][j].y = (int)((grid->pixel[i][j].y + grid->pixel[i][j].x - 2
			 * grid->pixel[i][j].z) * isoy);
			grid->pixel[i][j].x += grid->gap * j;
            grid->pixel[i][j].y += grid->gap * i;
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
		maxgap = WIDTH / 10;
	else
		maxgap = HEIGHT / 10;
	grid->gap = spacing / 3;
	if (grid->gap < 1)
		grid->gap = 1;
}

void	draw_function(t_mlx *mlx, t_data *img, t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	gap_manager(grid);
	printf("grid gap is: %d\n", grid->gap);
	iso_projo(grid);
	centering(grid);
	while (i < grid->lines)
	{
		j = 0;
		while (j > grid->rows)
		{
			my_mlx_pixel_put(img, grid->pixel[i][j].x, grid->pixel[i][j].y, grid->pixel[i][j].color);
			// my_mlx_pixel_put(img, j, i, 0xffffffff);
			j++;
		}
		i++;
	}
}

// void	zoom(t_mlx *mlx, t_data *img, t_grid *grid)
// {
// 	static int gap;
	
// 	gap += 1;

// }

void	hook_manager(t_data *img, t_mlx *mlx, t_grid *grid)
{
	draw_function(mlx, img, grid);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
	mlx_hook(mlx->win, 33, 1L<<9, close_window, mlx);
	mlx_hook(mlx->win, 2, 65307, key_hook, mlx);
	// mlx_hook(mlx->win, 2, 61, zoom(), mlx);
}


// void	fdf(void)

//main to display window
int main(int ac, char **av)
{
	t_data	img;
	t_mlx	mlx;
	int		x;
	int		y;
	int		fd;
	t_list	*lst;
	t_grid	grid;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	lst = get_file(fd);
	if (ak_superlen(lst, &grid.lines, &grid.rows) == -1)
		return (0);
	// printf("lines is: %d\nrows is: %d\n", grid.lines, grid.rows);
	grid.pixel = data_parser(lst, grid.lines, grid.rows);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Fil de Fer 2: le retour");
	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	//mlx_key_hook(mlx.win, key_hook, &mlx);
	hook_manager(&img, &mlx, &grid);
	// mlx_destroy_image(mlx.mlx, mlx.win);
	mlx_loop(mlx.mlx);
	return (0);
}
