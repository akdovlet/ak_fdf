/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/30 20:49:55 by akdovlet         ###   ########.fr       */
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
	int		gap;

	gap = 10;
    if (x > 1080 || y > 720 || x <= 0 || y <= 0)
        return ;
	while (x * gap > 1080 || y * gap > 720)
		gap--;
	x *= gap;
	y *= gap;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	iso_projo(t_pixel **data, t_limits *limits)
{
	int	i;
	int	j;

	i = 0;
	while (i < limits->lines)
	{
		j = 0;
		while (j < limits->lines)
		{
			data[i][j].x = ((data[i][j].x - data[i][j].z) / sqrt(2));
			data[i][j].y = ((data[i][j].x + 2*data[i][j].y + data[i][j].z) / sqrt(6));
			// my_mlx_pixel_put(img, j, i, 0xffffffff);
			j++;
		}
		i++;
	}
}

void	draw_function(t_mlx *mlx, t_data *img, t_pixel	**data, t_limits *limits)
{
	int	i;
	int	j;

	i = 0;
	iso_projo(data, limits);
	while (i < limits->lines)
	{
		j = 0;
		while (j < limits->lines)
		{
			my_mlx_pixel_put(img, data[i][j].x, data[i][j].y, data[i][j].color);
			// my_mlx_pixel_put(img, j, i, 0xffffffff);
			j++;
		}
		i++;
	}
}

//main to display window
int main(int ac, char **av)
{
	t_data	img;
	t_mlx	mlx;
	int		x;
	int		y;
	int		fd;
	t_list	*lst;
	t_pixel	**pixel;
	t_limits	limits;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	lst = get_file(fd);
	limits.points_count = ak_superlen(lst, &limits.lines, &limits.rows);
	printf("lines is: %d\nrows is: %d\n", limits.lines, limits.rows);
	pixel = data_parser(lst, limits.points_count, limits.lines, limits.rows);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1080, 720, "Fil de Fer");
	img.img = mlx_new_image(mlx.mlx, 1080, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 250, 250);
	//mlx_key_hook(mlx.win, key_hook, &mlx);
	draw_function(&mlx, &img, pixel, &limits);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 33, 1L<<9, close_window, &mlx);
	mlx_hook(mlx.win, 2, 65307, key_hook, &mlx);
	// mlx_destroy_image(mlx.mlx, mlx.win);
	mlx_loop(mlx.mlx);
	return (0);
}
