/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/14 19:39:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

void	ft_print_array(char **strs);

int ft_strchr_hex(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i] != (char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}

int	ft_ato_hexa(char *str)
{
	int				i;
	unsigned int	res;
	int				power;
	char			*hexa;
	char			*prefix;
	// char			*prefix2;

	hexa = "0123456789abcdef";
	prefix = "0x";
	// prefix2 = "0X";
	i = 0;
	res = 0;
	power = 1;
	str = ft_strnstr(str, prefix, 2);
	if (!str)
		return (0);
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		res += ft_strchr_hex(hexa, str[i]) * power;
		power *= 16;
		i--;
	}
	return (res);
}

int	count_line(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	ak_superlen(char **strs)
{
	int	i;
	int	superlen;

	i = 0;
	superlen = 0;
	while (strs[i])
	{
		if (superlen != superlen * i)
			return (-1);
		superlen += ft_strlen(strs[i]);
		printf("superlen is: %d\n", superlen);
		printf("strlen is: %zu\n", ft_strlen(strs[i]));
		printf("str[%d] is: %s\n", i, strs[i]);
		i++;
	}
	return (superlen);
}

// t_pixel	**data_parsing(int fd)
// {
// 	char	*file;
// 	char	**strs;
// 	t_pixel	**data;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	file = get_file(fd);
// 	strs = ft_multi_split(file, " ");
// 	int lcount = count_line
// 	int elemcount = count_elem;
// 	// data = malloc(sizeof(t_pixel *) * count_line));

// 	return (data);
// }

void	ft_print_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_printf("|%s|", strs[i]);
		i++;
	}
}

// int main()
// {
// 	int fd;
// 	t_pixel *data;


// 	while (data)
// 	{
// 		printf("%d %d %d %d\n", data->x, data->y, data->z, data->color);
// 		data = data->next;
// 	}
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	size_t	y_offset;
	size_t	x_offset;

	y_offset = y * data->line_length;
	x_offset = x * (data->bits_per_pixel / 8);
	dst = &data->addr[y_offset + x_offset];
	*(unsigned int*)dst = color;
}

// void	render_map(void *mlx, void *win, t_data *img, int x, int y, t_pixel *pixel)
// {
// 	while (pixel)
// 	{
// 		int x1;
// 		int y1;

// 		x1 += 100;
// 		my_mlx_pixel_put(img, x1 + pixel->x, y + pixel->y, 0x00FF0000);
// 		if (x == 960)
// 			x1 = 0;
// 		pixel = pixel->next;
// 	}
// }

// int main(int ac, char **av)
// {
// 	void *mlx;
// 	void *win;
// 	int fd;
// 	t_pixel	*data;
// 	t_data	img;

// 	fd = open("/home/akdovlet/cursus_42/fdf/maps/test_maps/10-2.fdf", O_RDONLY);
// 	unsigned int color = 0;
// 	data = data_parsing(fd);
// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 1920, 1080, "Fil de Fer");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	render_map(mlx, win, &img, 960, 540, data);
// 	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	close(fd);
// 	return (0);
// }

int main(int ac, char **av)
{
	int fd;
	char *file;
	char **strs;
	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	file = get_file(fd);
	if (!file)
		return (0);
	strs = ft_multi_split(file, " ");
	if (!strs)
		return (free(file), 0);
	ft_print_array(strs);
	int	i = ak_superlen(strs);
	printf("superlen is: %d\n", i);
	free_array(strs, i);
	free(file);
	close(fd);
	return (0);
}

