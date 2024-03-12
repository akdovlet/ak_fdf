/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:47:17 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/12 20:45:36 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <X11/keysym.h>


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
	x_offset = (WIDTH - (pixel[grid->lines - 1][grid->rows - 1].x[1] - pixel[1][1].x[1])) / 2;
	y_offset = (HEIGHT - (pixel[grid->lines - 1][grid->rows - 1].y[1] - pixel[1][1].y[1])) / 2;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			pixel[i][j].x[1] += x_offset;
			pixel[i][j].y[1] += y_offset;
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
			pixel[i][j].x[1] = (int)((pixel[i][j].x[0] - pixel[i][j].y[0]) * isox);
			pixel[i][j].y[1] = (int)((pixel[i][j].y[0] + pixel[i][j].x[0] - 2
			 * pixel[i][j].z[0]) * isoy);
			pixel[i][j].x[1] = (pixel[i][j].x[1] * grid->scaling) + (1 * pixel[i][j].x[1]);
			pixel[i][j].y[1] = (pixel[i][j].y[1] * grid->scaling) + (1 * pixel[i][j].y[1]);
			j++;
		}
		i++;
	}
}

void	gap_manager(t_grid *grid)
{
	double	spacing;
	float ewidth;
	float eheight;

	ewidth = grid->rows + (grid->rows - 1) * 2;
	eheight = grid->lines + (grid->lines - 1) * 2;
	grid->scaling = fminf((float)WIDTH / ewidth, (float)HEIGHT / eheight);
}

void	draw_line(t_pixel p1, t_pixel p2, t_img *img)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(p2.x[1] - p1.x[1]);
	dy = abs(p2.y[1] - p1.y[1]);
	if (p1.x[1] < p2.x[1])
		sx = 1;
	else
		sx = -1;
	if (p1.y[1] < p2.y[1])
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (p1.x[1] != p2.x[1] || p1.y[1] != p2.y[1])
	{
		ak_mlx_pixel_put(img, p1.x[1], p1.y[1], p1.color);
		if (2 * err > -dy)
		{
			err -= dy;
			p1.x[1] += sx;
		}
		else
		{
			err += dx;
			p1.y[1] += sy;
		}
	}
}

void	draw_function(t_mlx *mlx, t_img *img, t_grid *grid, t_pixel **pixel)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->lines - 1)
	{
		j = 0;
		while (j < grid->rows - 1)
		{
			ak_mlx_pixel_put(img, pixel[i][j].x[1], pixel[i][j].y[1], pixel[i][j].color);
			draw_line(pixel[i][j], pixel[i][j + 1], img);
			draw_line(pixel[i][j], pixel[i + 1][j], img);
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
	grid->z = 0;
	return (1);
}

void	clear_all(t_grid *grid, t_mlx *mlx)
{
	pixel_clear(grid->pixel, grid->lines);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	ft_printf("AK out!\n");
}

void	draw_frame(t_data *data)
{
	iso_projo(&data->grid, data->grid.pixel);
	centering(&data->grid, data->grid.pixel);
	draw_function(&data->mlx, &data->mlx.img, &data->grid, data->grid.pixel);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
}

void	next_frame(t_mlx *mlx, t_img *img)
{
	mlx_destroy_image(mlx->mlx_ptr, img->img_ptr);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!img->img_ptr)
		return ;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	
}

void	set_zed(t_grid *grid, int z)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->lines)
	{
		j = 0;
		while (j < grid->rows)
		{
			grid->pixel[i][j].z[0] = grid->pixel[i][j].z[0] - z;
			j++;
		}
		i++;
	}
}

int	key_hook(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_loop_end(data->mlx.mlx_ptr);
		return (0);
	}
	else if (keysym == XK_F2)
		ft_printf("good day of work");
	else if (keysym == XK_z)
	{
		ft_printf("z");
		next_frame(&data->mlx, &data->mlx.img);
		data->grid.z += 1;
		set_zed(&data->grid, data->grid.z);
		draw_frame(data);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

int	x_button(t_data *data)
{
	mlx_loop_end(data->mlx.mlx_ptr);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		next_frame(&data->mlx, &data->mlx.img);
		data->grid.scaling += 1;
		draw_frame(data);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	}
	else if (button == 5)
	{
		if (data->grid.scaling > 0)
			data->grid.scaling -= 1;
		else
			return (0);
		next_frame(&data->mlx, &data->mlx.img);
		draw_frame(data);
		mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

void	handle_input(t_data *data)
{
	mlx_key_hook(data->mlx.win_ptr, key_hook, data);
	mlx_mouse_hook(data->mlx.win_ptr, mouse_hook, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, x_button, data);
}

//main to display window
int main(int ac, char **av)
{
	t_data data;
	int		err;

	if (ac != 2)
		return (0);
	if (file_and_parse(av[1], &data.grid) <= 0)
		return (0);
	init_data(&data.mlx, &data.mlx.img);
	gap_manager(&data.grid);
	draw_frame(&data);
	handle_input(&data);
	mlx_loop(data.mlx.mlx_ptr);
	clear_all(&data.grid, &data.mlx);
	return (0);
}
